#include "parseLineToOrder.hpp"
#include "order.hpp"
#include <iostream>

int main()
{
    std::string s = "A:AUDUSD:100:1.47";
    std::string delimiter = ":";
    order myOrder = parseLineToOrder(s, delimiter);
    std::cout << myOrder;
    return 0;
}
