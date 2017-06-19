#ifndef Order_HPP
#define Order_HPP
#include <string>
using std::string;

class Order 
{
public:
	int id;
	string name;
	string instrument;
	int quantity;
	double price;	
public: 
	Order();
	Order(int id, string name, string instrument, int quantity, double price);
	void print() const;

};

#endif
