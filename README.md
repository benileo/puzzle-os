puzzle-os
=========
The puzzle solver.
The objective of this program is to solve the puzzle as fast as possible using the POSIX library. 


Using the generate executable(found in the crate directory) you can generate puzzles. Here is a sample command:

./generate 100 100 32 > ten_thousand

**This generates a puzzle 100 columns by 100 rows with a seed value of 32 and writes it to a file called ten_thousand**



make

./jigsaw < crate/ten_thousand 

** ^^ solves with a single thread ^^ **

./jigsaw 3 < crate/ten_thousand

** ^^ creates 3 threads to solve ^^ **
