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
	order newOrder;
	std::vector<trade> myTrade;
	std::vector<std::shared_ptr<order>> openOrder;

	std::getline(std::cin,s);
	openOrder.push_back(std::make_shared<order>(parseLineToOrder(s, delimiter)));

	while (std::getline(std::cin,s))
	{
		newOrder = parseLineToOrder(s, delimiter);
		generateTrade(newOrder,openOrder,myTrade);
	}

	for (std::vector<trade>::iterator i = myTrade.begin(); i != myTrade.end(); i++)
	{
		(*i).print();
	}

}
