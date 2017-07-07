#include "parseLineToOrder.hpp"
#include "order.hpp"
#include <string>
#include <sstream>

order parseLineToOrder(std::string& s, std::string delimiter)
{
    size_t pos;
    std::string name, instrument;
    int quantity;
    double price;

    pos = s.find(delimiter);
    name = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());

    pos = s.find(delimiter);
    instrument = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());

    pos = s.find(delimiter);
    std::istringstream(s.substr(0, pos)) >> quantity;
    s.erase(0, pos + delimiter.length());

    std::istringstream(s) >> price;

    order myOrder(name, instrument, quantity, price);

    return myOrder;
};
