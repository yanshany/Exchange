#include "parseLineToOrder.hpp"
#include "order.hpp"
#include <string>
#include <sstream>

order parseLineToOrder(std::string& s, char delimiter)
{
    std::string name, instrument;
    int quantity;
    double price;

    auto stream = std::istringstream(s);
    std::getline(stream,name,delimiter);
    std::getline(stream,instrument,delimiter);
    stream >> quantity;
    stream.get();
    stream >> price;
    order myOrder(name, instrument, quantity, price);

    return myOrder;
};
