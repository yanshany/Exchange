#include "trade.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;
int main()
{
string name1 ("A");
string name2 ("B");
string instrument ("AUDUSD");
int quantity = 100;
double price = 0.7838;
Trade myTrade(name1,name2,instrument,quantity,price);
myTrade.print();
return 0;
}
