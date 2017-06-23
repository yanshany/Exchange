#ifndef Order_HPP
#define Order_HPP
#include <string>

class Order
{
private:
	std::string m_name;
	std::string m_instrument;
	int m_quantity;
	double m_price;

public:
	Order();

	Order(const std::string _name, const std::string _instrument, int _quantity, double _price);

	const std::string name() const { return m_name; }
	void name(const std::string value) { m_name = value; }

	const std::string instrument() const { return m_instrument; }
	void instrument(const std::string value) { m_instrument = value; }

	int quantity() const { return m_quantity; }
	void quantity(int value) { m_quantity = value; }

	double price() const { return m_price; }
	void price(double value) { m_price = value; }

	void print() const;
};

#endif
