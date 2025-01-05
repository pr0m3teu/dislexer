# Dislexer
## Simple lexer written in C.
I started this small project in order to test my understandment of memory managment and string manipulations in C. 

## Memory 
### The Problem
I've tried to make it 'memory safe' by making it not leak any memory (I don't, as of right now, know if 'memory safe' is the right term here). 
There are, I believe, too many heap allocations and I'm trying to lower their number.   
I have tried to be carefull and deallocate everything properly but,I have checked with [valgrind](https://valgrind.org/) and there seems to be 
a massive memory leak, especially when trying to lex huge files. It seems that somewhere inside the program I am missing a 'free' or maybe I
am not freeing things in the right order.

### The Solution
I have solved this problem by implementing this [lallocs](https://github.com/pr0m3teu/lallocs) library that 
keeps a linked-list with all the allocations so that they can easily be freed at the end of the program.  
I have also tried solving this by using my [snur](https://github.com/pr0m3teu/snur) library instead of cstr's but without succes. Maybe I will integrate
with the project some day.
