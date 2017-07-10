#include "order.hpp"

order::order(){};

order::order(const std::string _name, const std::string _instrument, int _quantity, double _price)
{
    name(_name);
    instrument(_instrument);
    quantity(_quantity);
    price(_price);
}

std::ostream& operator<<(std::ostream& os, const order& order)
{
    os << order.m_name << ":" << order.m_instrument << ":" << order.m_quantity << ":" << order.m_price;
    return os;
}

