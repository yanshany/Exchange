#include "order.hpp"
#include "chooseCandidate.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
vector<Order> allOrder;

Order newOrder = Order("A","AUDUSD",100,1.8);

allOrder.push_back(Order("A","AUDUSD",100,1.7));
allOrder.push_back(Order("A","AUDUSD",100,1.5));
allOrder.push_back(Order("A","AUDUSD",100,1.4));

int a = chooseCandidate(newOrder, allOrder);
cout << a;
return 0;
}
