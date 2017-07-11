Instruction:

1 use Makefile to compile:

make clean
make

2 three orders files to be processed: orders_1.txt, orders_2.txt, and orders_100K.txt:

cat orders_1.txt | ./Exchange > trades_1.txt
cat orders_2.txt | ./Exchange > trades_2.txt
cat orders_100K.txt | ./Exchange > trades_100K.txt

3 shows run time

time cat orders_100K.txt | ./Exchange > trades_100K.txt

run previous command three time, we get results:

real	0m1.773s
user	0m1.764s
sys	0m0.024s

real	0m1.739s
user	0m1.732s
sys	0m0.020s

real	0m1.745s
user	0m1.732s
sys	0m0.028s
