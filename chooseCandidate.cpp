#include "chooseCandidate.hpp"
#include "order.hpp"
#include <vector>
#include <algorithm>
using namespace std;

int chooseCandidate(Order newOrder, vector<Order> candidate)
{
// choose the best order in the candidate orders by finding the best price, retune the index
	vector<double> price;
	int ind;
// get a vector of prices from candidate orders
	for (int i = 0; i != candidate.size() ; ++i){
		price.push_back(candidate[i].price);
	}

	if (newOrder.quantity > 0)
		ind = distance(price.begin(), min_element(price.begin(),price.end()));
	else
		ind = distance(price.begin(), max_element(price.begin(),price.end()));

	return ind;
};
