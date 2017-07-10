#ifndef orderBook_HPP
#define orderBook_HPP
#include <string>
#include <vector>
#include <iostream>
#include "order.hpp"

class orderBook
{
public:
    std::vector<order> ask;
    std::vector<order> bid;
    
    orderBook();
    
    void addAnOrder(order& newOrder);
    
    friend std::ostream& operator<<(std::ostream& os, const orderBook& orderBook);

};

#endif
