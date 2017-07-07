#include "order.hpp"
#include <iostream>

order::order(){};

order::order(const std::string _name, const std::string _instrument, int _quantity, double _price)
{
    name(_name);
    instrument(_instrument);
    quantity(_quantity);
    price(_price);
}

void order::print() const
{
    std::cout << m_name << ":" << m_instrument << ":" << m_quantity << ":" << m_price << std::endl;
}

/* ostream& operator<<(ostream& os, const order& order)
{
    os << m_name << ":" << m_instrument << ":" << m_quantity << ":" << m_price;
    return os;
}


cerr << order << std::endl;

cout << "order: " << order << std::endl;
*/
