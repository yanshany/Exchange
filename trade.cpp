#include "trade.hpp"
#include <iostream>

trade::trade(){};

trade::trade(std::string _name1, std::string _name2, std::string _instrument, int _quantity, double _price)
{
    m_name1 = _name1;
    m_name2 = _name2;
    m_instrument = _instrument;
    m_quantity = _quantity;
    m_price = _price;
}

std::ostream& operator<<(std::ostream& os, const trade& trade)
{
    os << trade.m_name1 << ":" << trade.m_name2 << ":" << trade.m_instrument << ":" << trade.m_quantity << ":" << trade.m_price << std::endl;
    return os;
}
