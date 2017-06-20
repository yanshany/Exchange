#include "chooseCandidate.hpp"
#include "order.hpp"
#include <vector>
#include <algorithm>
using namespace std;

int chooseCandidate(Order newOrder, vector<Order> candidate)
{
	vector<double> price;
	int ind;
	for (int i = 0; i != candidate.size() ; ++i){
		price.push_back(candidate[i].price);
	}

	if (newOrder.quantity > 0)
		ind = distance(price.begin(), min_element(price.begin(),price.end()));
	else
		ind = distance(price.begin(), max_element(price.begin(),price.end()));

	return ind;
};
