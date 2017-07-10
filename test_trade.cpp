#include "trade.hpp"
#include <cassert>
#include <iostream>

int main()
{
    std::string name1("A");
    std::string name2("B");
    std::string instrument("AUDUSD");
    int quantity = 100;
    double price = 0.7838;
    trade myTrade(name1, name2, instrument, quantity, price);
    assert(myTrade.name1() == name1);
    assert(myTrade.name2() == name2);
    assert(myTrade.instrument() == instrument);
    assert(myTrade.quantity() == quantity);
    assert(myTrade.price() == price);
    std::cout << myTrade;
    return 0;
}
