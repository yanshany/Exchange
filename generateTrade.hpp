#ifndef GenerateTrade_HPP
#define GenerateTrade_HPP
#include "order.hpp"
#include "orderBook.hpp"
#include "trade.hpp"
#include <vector>
#include <map>
#include <memory>
//#include <algorithm>
void generateTrade(order& newOrder, std::map<std::string, orderBook>& wholeBook, std::vector<trade>& myTrade);
#endif
