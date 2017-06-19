# include "parseLineToOrder.hpp"
# include "order.hpp"
# include <string>


int main()
{
std::string s = "A:AUDUSD:100:1.47";
std::string delimiter = ":";
Order myOrder = parseLineToOrder(s,delimiter);

myOrder.print();
return 0;
}
