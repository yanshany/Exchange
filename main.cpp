#include "order.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include "generateTrade.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main()
{
	std::string s;
	const std::string delimiter = ":";
	Order newOrder;
	std::vector<Trade> myTrade;
	std::vector<std::shared_ptr<Order>> openOrder;

	std::getline(std::cin,s);
	openOrder.push_back(std::make_shared<Order>(parseLineToOrder(s, delimiter)));

	while (std::getline(std::cin,s))
	{
		newOrder = parseLineToOrder(s, delimiter);
		generateTrade(newOrder,openOrder,myTrade);
	}

	for (std::vector<Trade>::iterator i = myTrade.begin(); i != myTrade.end(); i++)
	{
		(*i).print();
	}

}
