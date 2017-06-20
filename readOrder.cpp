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

vector<Order> allOrder;
int i = 0;
while(getline(cin,s)){
//	cout << s << endl;
	allOrder.push_back(parseLineToOrder(s, delimiter));
	allOrder[i].print();
	i++;
}

Order newOrder = Order();
vector<Trade> myTrade;
vector<Order> openOrder,openOrderCopy;
openOrder.push_back(allOrder[0]);
openOrderCopy = openOrder;

for (int i = 1; i != allOrder.size(); ++i ){
	newOrder = allOrder[i];
	for (int j = 0; j != openOrderCopy.size(); ++j) {

		if(newOrder.instrument == openOrder[j].instrument && newOrder.quantity*openOrder[j].quantity < 0)
		{
			if(newOrder.quantity > 0 && newOrder.price >= openOrder[j].price)
			{
				myTrade.push_back(Trade(newOrder.name, openOrder[j].name, newOrder.instrument,min(newOrder.quantity,-1*openOrder[j].quantity), openOrder[j].price));				
				if(newOrder.quantity < -1*openOrder[j].quantity)
					 openOrder[j].quantity += newOrder.quantity;
				else if (newOrder.quantity > -1*openOrder[j].quantity) 
				{
					openOrder.push_back(Order(newOrder.name,newOrder.instrument,newOrder.quantity + openOrder[j].quantity, newOrder.price));
					openOrder.erase(openOrder.begin()+j);
				}
				else 
					openOrder.erase(openOrder.begin()+j);
				

			}				
			else if (newOrder.quantity < 0 && newOrder.price <= openOrder[j].price)
			{
				myTrade.push_back(Trade(openOrder[j].name, newOrder.name, newOrder.instrument,min(-1*newOrder.quantity,openOrder[j].quantity), openOrder[j].price));				
				if(-1*newOrder.quantity < openOrder[j].quantity) 
					openOrder[j].quantity += newOrder.quantity;
				else if(-1*newOrder.quantity > openOrder[j].quantity) 
				{
					openOrder.push_back(Order(newOrder.name,newOrder.instrument,newOrder.quantity + openOrder[j].quantity, newOrder.price));
					openOrder.erase(openOrder.begin()+j);
				}
				else
					openOrder.erase(openOrder.begin()+j);

			}
			else
				openOrder.push_back(newOrder);
					
		}
		else
			openOrder.push_back(newOrder);

	}
	openOrderCopy = openOrder;
}

cout << "trade:\n";
for (int i = 0; i != myTrade.size() ; ++i){
	myTrade[i].print();
}
cout << "open order:\n";
for (int i = 0; i != openOrder.size() ; ++i){
	openOrder[i].print();
}


}
