#include "order.hpp"
#include "orderBook.hpp"
#include "trade.hpp"
#include "parseLineToOrder.hpp"
#include "generateTrade.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

int main()
{
	std::string s;
	const std::string delimiter = ":";
	std::vector<trade> myTrade;
	std::map<std::string, orderBook> wholeBook;

	while (std::getline(std::cin,s))
	{
		order newOrder = parseLineToOrder(s, delimiter);
		generateTrade(newOrder,wholeBook,myTrade);
	}

	for (std::vector<trade>::iterator i = myTrade.begin(); i != myTrade.end(); i++)
	{
        std::cout << *i;
	}

}
