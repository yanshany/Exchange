# include "parseLineToOrder.hpp"
# include "order.hpp"
# include <string>
# include <sstream>
using namespace std;

Order parseLineToOrder(string s, string delimiter)
{

size_t pos;
string name,instrument;
int quantity;
double price;

pos = s.find(delimiter);
name = s.substr(0, pos);
s.erase(0, pos + delimiter.length());

pos = s.find(delimiter);
instrument = s.substr(0, pos);
s.erase(0, pos + delimiter.length());

pos = s.find(delimiter);
istringstream(s.substr(0, pos)) >> quantity;
s.erase(0, pos + delimiter.length());

istringstream(s) >> price;

Order myOrder(1,name,instrument,quantity,price);
//myOrder.print();

return myOrder;

};

