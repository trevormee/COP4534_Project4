/***************************************************************
  Student Name: Trevor Mee
  File Name: main.cpp
  Project 4

  @brief Contains main function of the program that creates an 
         instance of the "BinPacking" class and calls 
         SolveBinPacking() to solve and display the results of 
         computing the Bin Packing Problem using on-line,
         off-line, and a brute force algorithm
***************************************************************/

#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    bp.SolveBinPacking();

    return 0;
}