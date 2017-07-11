#include "order.hpp"
#include "orderBook.hpp"
#include "trade.hpp"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <cassert>

int main()
{
    order order1 = order("A","AUDUSD",100,1.7);
    order order2 = order("B","AUDUSD",-100,1.7);
    order order3 = order("C","AUDUSD",100,1.6);

    orderBook orderBookEachMarket = orderBook();

    orderBookEachMarket.addAnOrder(order1);
    orderBookEachMarket.addAnOrder(order2);
    orderBookEachMarket.addAnOrder(order3);
    std::cout << orderBookEachMarket;
    
    assert(orderBookEachMarket.bid[0].name() == order1.name());
    assert(orderBookEachMarket.bid[0].instrument() == order1.instrument());
    assert(orderBookEachMarket.bid[0].quantity() == order1.quantity());
    assert(orderBookEachMarket.bid[0].price() == order1.price());

    assert(orderBookEachMarket.ask[0].name() == order2.name());
    assert(orderBookEachMarket.ask[0].instrument() == order2.instrument());
    assert(orderBookEachMarket.ask[0].quantity() == order2.quantity());
    assert(orderBookEachMarket.ask[0].price() == order2.price());

    assert(orderBookEachMarket.bid[1].name() == order3.name());
    assert(orderBookEachMarket.bid[1].instrument() == order3.instrument());
    assert(orderBookEachMarket.bid[1].quantity() == order3.quantity());
    assert(orderBookEachMarket.bid[1].price() == order3.price());

    std::map<std::string, orderBook> wholeBook;
    wholeBook["AUDUSD"] = orderBookEachMarket;
    
    std::cout << wholeBook["AUDUSD"];
    return 0;
 
}
