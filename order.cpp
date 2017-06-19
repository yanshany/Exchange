#include "order.hpp"
#include <iostream>
#include <string>
using std::string;
using std::cout;

Order::Order() {};

Order::Order(int _id, string _name, string _instrument, int _quantity, double _price)
{
id = _id;
name = _name;
instrument = _instrument;
quantity = _quantity;
price = _price;
}

void Order::print() const
{
cout  << name << ":" <<  instrument << ":" << quantity << ":" << price << std::endl;
}

