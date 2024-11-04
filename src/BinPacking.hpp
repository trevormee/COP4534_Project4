/***************************************************************
  Student Name: Trevor Mee
  File Name: AdjacencyMatrix.hpp
  Project 4

  @brief 
***************************************************************/

#ifndef BINPACKING_HPP
#define BINPACKING_HPP

#include <iostream>
#include <vector>
#include <fstream>

class BinPacking
{
    private:
        // Private Instance Variables
        const int BIN_CAPACITY = 1;
        int numItems;

        // Helper function to generate the optimal solution
        void perm1(std::vector<float>& weights);
       
    public:
        // Public Instance Variables
        std::vector<float> weights;

        void ReadFileAndPopulate(const std::string &fileName, std::vector<float> &weights);

        std::vector<std::vector<float>> OptimalSolution(const std::vector<float>& weights);

        std::vector<std::vector<float>> OnlineFirstFit(const std::vector<float>& weights);

        void displayVector();

};
#endif