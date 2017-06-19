#ifndef Trade_HPP
#define Trade_HPP
#include <string>
using std::string;

class Trade 
{
public:
	string name1;
	string name2;
	string instrument;
	int quantity;
	double price;	
public: 
	Trade();
	Trade(string name1, string name2, string instrument, int quantity, double price);
	void print() const;

};

#endif
