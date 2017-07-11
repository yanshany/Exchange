#include "orderBook.hpp"
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

std::ostream& operator<<(std::ostream& os, const orderBook& orderBook)
{
    os << "ask" << std::endl;
    for (std::vector<order>::const_iterator it = orderBook.ask.begin(); it != orderBook.ask.end(); ++it)
    {
        os << *it <<std::endl;
    }
    os << "bid" << std::endl;
    for (std::vector<order>::const_iterator it = orderBook.bid.begin(); it != orderBook.bid.end(); ++it)
    {
        os << *it << std::endl;
    }
    return os;
}
