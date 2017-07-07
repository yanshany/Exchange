#include "parseLineToOrder.hpp"
#include "order.hpp"

int main()
{
    std::string s = "A:AUDUSD:100:1.47";
    std::string delimiter = ":";
    order myOrder = parseLineToOrder(s, delimiter);
    myOrder.print();
    return 0;
}
