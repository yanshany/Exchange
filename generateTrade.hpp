#ifndef GenerateTrade_HPP
#define GenerateTrade_HPP
#include "order.hpp"
#include "trade.hpp"
#include <vector>
#include <memory>
void generateTrade(order& newOrder, std::vector<std::shared_ptr<order>>& openOrder, std::vector<trade>& myTrade);
#endif
