
CXX=g++
CFLAGS=-I. -I/usr/local/include -std=c++14 -O3
DEPS =
OBJS = order.o trade.o generateTrade.o parseLineToOrder.o
LIBS = -lboost_unit_test_framework

%.o:	%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

default:	test_order test_trade test_parseLineToOrder Exchange

all:	test_order test_trade test_parseLineToOrder Exchange

clean:
	@rm -f *.o test_order test_trade test_parseLineToOrder Exchange
        
Exchange:	main.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

test_order:	test_order.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

test_trade:	test_trade.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

test_parseLineToOrder:	test_parseLineToOrder.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)
