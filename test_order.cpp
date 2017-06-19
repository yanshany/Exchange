#include "order.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;
int main()
{
int id = 1;
string name ("A");
string instrument ("AUDUSD");
int quantity = 100;
double price = 0.7838;
Order myOrder(id,name,instrument,quantity,price);
myOrder.print();
return 0;
}
