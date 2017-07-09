#include "orderBook.h"
#include "order.hpp"
#include <iostream>
orderBook::orderBook(){};

void orderBook::addAnOrder(order& newOrder)
{
    if (newOrder.quantity() > 0)
    {
        std::vector<order>::iterator it;
        
        for (it = bid.begin(); it != bid.end(); ++it)
        {
            if (it->price() < newOrder.price())
                break;
        }
        
        bid.insert(it, newOrder);
    }
    else
    {
        std::vector<order>::iterator it;
        
        for (it = ask.begin(); it != ask.end(); ++it)
        {
            if (it->price() > newOrder.price())
                break;
        }
        
        ask.insert(it, newOrder);
    }
}

void orderBook::print()
{
    std::cout << "ask" << std::endl;
    
    std::vector<order>::iterator it;
    
    for (it = ask.begin(); it != ask.end(); ++it)
    {
        it->print();
    }
    std::cout << "bid" << std::endl;
    
    for (it = bid.begin(); it != bid.end(); ++it)
    {
        it->print();
    }
}