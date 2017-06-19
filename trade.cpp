#include "trade.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;

Trade::Trade() {};

Trade::Trade(string _name1, string _name2, string _instrument, int _quantity, double _price)
{
name1 = _name1;
name2 = _name2;
instrument = _instrument;
quantity = _quantity;
price = _price;
}

void Trade::print() const
{
cout <<  name1 <<  ":" << name2 << ":" <<  instrument << ":" << quantity << ":" << price << std::endl;
}

