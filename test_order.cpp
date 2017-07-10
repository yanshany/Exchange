#include "order.hpp"
#include <cassert>
#include <iostream>

int main()
{
    std::string name("A");
    std::string instrument("AUDUSD");
    int quantity = 100;
    double price = 0.7838;
    order myOrder(name, instrument, quantity, price);
    assert(myOrder.name() == name);
    assert(myOrder.instrument() == instrument);
    assert(myOrder.quantity() == quantity);
    assert(myOrder.price() == price);
    std::cout << myOrder << std::endl;
    return 0;

}
