#include "order.hpp"
#include <iostream>

Order::Order(){};

Order::Order(const std::string _name, const std::string _instrument, int _quantity, double _price)
{
    name(_name);
    instrument(_instrument);
    quantity(_quantity);
    price(_price);
}

void Order::print() const
{
    std::cout << m_name << ":" << m_instrument << ":" << m_quantity << ":" << m_price << std::endl;
}
