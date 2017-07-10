#ifndef trade_HPP
#define trade_HPP
#include <string>

class trade
{
  private:
	std::string m_name1;
	std::string m_name2;
	std::string m_instrument;
	int m_quantity;
	double m_price;

  public:
	trade();

	trade(std::string _name1, std::string _name2, std::string _instrument, int _quantity, double _price);

	const std::string name1() const { return m_name1; }

	const std::string name2() const { return m_name2; }

	const std::string instrument() const { return m_instrument; }

	int quantity() const { return m_quantity; }

	double price() const { return m_price; }

    friend std::ostream& operator<<(std::ostream& os, const trade& trade);
};

#endif
