#ifndef GenerateTrade_HPP
#define GenerateTrade_HPP
#include "order.hpp"
#include "trade.hpp"
#include <vector>
#include <memory>
void generateTrade(Order &newOrder, std::vector<std::shared_ptr<Order>> &openOrder, std::vector<std::shared_ptr<Trade>> &myTrade);
#endif
