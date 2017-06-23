#include "trade.hpp"
#include <iostream>

Trade::Trade(){};

Trade::Trade(std::string _name1, std::string _name2, std::string _instrument, int _quantity, double _price)
{
    m_name1 = _name1;
    m_name2 = _name2;
    m_instrument = _instrument;
    m_quantity = _quantity;
    m_price = _price;
}

void Trade::print() const
{
    std::cout << m_name1 << ":" << m_name2 << ":" << m_instrument << ":" << m_quantity << ":" << m_price << std::endl;
}
