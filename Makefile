
CXX=g++
CFLAGS=-I. -I/usr/local/include -std=c++11
DEPS =
OBJS = order.o trade.o chooseCandidate.o updateOpenOrder.o parseLineToOrder.o
LIBS = -lboost_unit_test_framework

%.o:	%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

default:	test_order test_trade Exchange

all:	test_order test_trade Exchange

clean:
	@rm -f *.o test_order test_trade Exchange
        
Exchange:	readOrder.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

test_order:	test_order.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)

test_trade:	test_trade.o $(OBJS)
	$(CXX) -o $@ $^ $(CFLAGS)
