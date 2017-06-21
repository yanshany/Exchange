#include "order.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include "chooseCandidate.hpp"
#include "updateOpenOrder.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main () {

int indBestCandidate;
string s;
string delimiter = ":";
Order newOrder = Order();
vector<Order> allOrder;
vector<Trade> myTrade;
vector<int> ind;
vector<Order> openOrder, openOrderCopy, candidate;


// read in orders from cin
while(getline(cin,s)){
	allOrder.push_back(parseLineToOrder(s, delimiter));
	allOrder.back().print();
}

openOrder.push_back(allOrder[0]);
openOrderCopy = openOrder;

for (int i = 1; i != allOrder.size(); ++i ){
	newOrder = allOrder[i];
	if (newOrder.quantity > 0)
	{
		for (int j = 0; j != openOrderCopy.size(); ++j){
			if(newOrder.instrument == openOrder[j].instrument && openOrder[j].quantity < 0 && openOrder[j].price <= newOrder.price)
			{
				ind.push_back(j);
				candidate.push_back(openOrder[j]);
			}								
		}

		if (ind.size() == 0)
			openOrder.push_back(newOrder);

		if (ind.size() == 1)
		{
			myTrade.push_back(Trade(newOrder.name, candidate[0].name, newOrder.instrument,min(newOrder.quantity,-1*candidate[0].quantity), candidate[0].price));				
			openOrder = updateOpenOrder(newOrder,openOrder,ind[0]);	
		}

		if (ind.size() > 1)
		{
			indBestCandidate = chooseCandidate(newOrder,candidate);
			myTrade.push_back(Trade(newOrder.name, openOrder[ind[indBestCandidate]].name, newOrder.instrument,min(newOrder.quantity,-1*openOrder[ind[indBestCandidate]].quantity), openOrder[ind[indBestCandidate]].price));				
			openOrder = updateOpenOrder(newOrder,openOrder,ind[indBestCandidate]);
		}
		
		ind.clear(); 
		candidate.clear();
	}
	if (newOrder.quantity < 0)
	{
		for (int j = 0; j != openOrderCopy.size(); ++j){
			if(newOrder.instrument == openOrder[j].instrument && openOrder[j].quantity > 0 && openOrder[j].price >= newOrder.price)
			{
				ind.push_back(j);
				candidate.push_back(openOrder[j]);
			}								
		}

		if (ind.size() == 0 )
			openOrder.push_back(newOrder); 

		if (ind.size() == 1)
		{
			myTrade.push_back(Trade(openOrder[ind[0]].name,newOrder.name, newOrder.instrument,min(-1*newOrder.quantity,openOrder[ind[0]].quantity), openOrder[ind[0]].price));				
			openOrder = updateOpenOrder(newOrder,openOrder,ind[0]);		
		}

		if (ind.size() > 1)
		{
			indBestCandidate = chooseCandidate(newOrder,candidate);
			myTrade.push_back(Trade(openOrder[ind[indBestCandidate]].name, newOrder.name, newOrder.instrument,min(-1*newOrder.quantity,openOrder[ind[indBestCandidate]].quantity), openOrder[ind[indBestCandidate]].price));				
			openOrder = updateOpenOrder(newOrder,openOrder,ind[indBestCandidate]);
		}

		ind.clear(); 
		candidate.clear();
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