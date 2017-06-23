#include "order.hpp"
#include <cassert>

int main()
{
    std::string name("A");
    std::string instrument("AUDUSD");
    int quantity = 100;
    double price = 0.7838;
    Order myOrder(name, instrument, quantity, price);
    myOrder.print();
    assert(myOrder.name() == name);
    assert(myOrder.instrument() == instrument);
    assert(myOrder.quantity() == quantity);
    assert(myOrder.price() == price);
    return 0;
}
