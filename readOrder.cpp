#include "order.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main () {

string s;
string delimiter = ":";

vector<Order> myOrder;
int i = 0;
while(getline(cin,s)){
//	cout << s << endl;
	myOrder.push_back(parseLineToOrder(s, delimiter));
	myOrder[i].print();
	i++;
}

vector<Trade> myTrade;
vector<Order> openOrder;
openOrder.push_back(myOrder[0]);

for (int i = 1; i != myOrder.size(); ++i ){
	for (int j = 0; j != openOrder.size(); ++j) {
		if(myOrder[i].instrument == openOrder[j].instrument && myOrder[i].quantity*openOrder[j].quantity < 0)
		{
			if(myOrder[i].quantity > 0 && myOrder[i].price > openOrder[j].price)
			{
				myTrade.push_back(Trade(myOrder[i].name, openOrder[j].name, myOrder[i].instrument,min(myOrder[i].quantity,-1*openOrder[j].quantity), openOrder[j].price));				
				if(myOrder[i].quantity < -1*openOrder[j].quantity) openOrder[j].quantity += myOrder[i].quantity;
				if(myOrder[i].quantity == -1*openOrder[j].quantity) openOrder.erase(openOrder.begin()+j);
				if(myOrder[i].quantity > -1*openOrder[j].quantity) 
				{
					openOrder.erase(openOrder.begin()+j);
					openOrder.push_back(Order(myOrder[i].name,myOrder[i].instrument,myOrder[i].quantity + openOrder[j].quantity, myOrder[i].price));
				}

			}				
			else if (myOrder[i].quantity < 0 && myOrder[i].price < openOrder[j].price)
			{
				myTrade.push_back(Trade(openOrder[j].name, myOrder[i].name, myOrder[i].instrument,min(-1*myOrder[i].quantity,openOrder[j].quantity), openOrder[j].price));				
				if(-1*myOrder[i].quantity < openOrder[j].quantity) openOrder[j].quantity += myOrder[i].quantity;
				if(-1*myOrder[i].quantity == openOrder[j].quantity) openOrder.erase(openOrder.begin()+j);
				if(-1*myOrder[i].quantity > openOrder[j].quantity) 
				{
					openOrder.erase(openOrder.begin()+j);
					openOrder.push_back(Order(myOrder[i].name,myOrder[i].instrument,myOrder[i].quantity + openOrder[j].quantity, myOrder[i].price));
				}
			}
			else
				openOrder.push_back(myOrder[i]);
					
		}
		else
			openOrder.push_back(myOrder[i]);

	}
}


for (int i = 0; i != myTrade.size() ; ++i){
	myTrade[i].print();
}

for (int i = 0; i != openOrder.size() ; ++i){
	openOrder[i].print();
}


}
