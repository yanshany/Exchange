#include "order.hpp"
#include "trade.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

vector<shared_ptr<Trade>> generateTrade(Order newOrder, vector<shared_ptr<Order>> &openOrder, vector<shared_ptr<Trade>> myTrade);