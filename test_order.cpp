#include "order.hpp"
#include <iostream>
#include <string>
#include <cassert>
using std::string;
using std::cout;
int main()
{
string name ("A");
string instrument ("AUDUSD");
int quantity = 100;
double price = 0.7838;
Order myOrder(name,instrument,quantity,price);
myOrder.print();
assert(myOrder.quantity == 100);
return 0;
}
