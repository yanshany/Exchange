#include "trade.hpp"
#include <cassert>

int main()
{
    std::string name1("A");
    std::string name2("B");
    std::string instrument("AUDUSD");
    int quantity = 100;
    double price = 0.7838;
    Trade myTrade(name1, name2, instrument, quantity, price);
    myTrade.print();
    assert(myTrade.name1() == name1);
    assert(myTrade.name2() == name2);
    assert(myTrade.instrument() == instrument);
    assert(myTrade.quantity() == quantity);
    assert(myTrade.price() == price);
    return 0;
}
