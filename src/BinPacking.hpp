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
#include <algorithm>

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

        // Reads in a text file and populates our weights vector
        void ReadFileAndPopulate(const std::string &fileName, std::vector<float> &weights);

        // Computes the optimal solution for the Bin Packing problem
        std::vector<std::vector<float>> OptimalSolution(const std::vector<float>& weights);

        // Computes the online first fit algorithm for the Bin Packing problem
        std::vector<std::vector<float>> OnlineFirstFit(const std::vector<float>& weights);

        // Computes the online next fit algorithm for the Bin Packing problem
        std::vector<std::vector<float>> OnlineNextFit(const std::vector<float>& weights);

        // Computes the online best fit algorithm for the Bin Packing problem
        std::vector<std::vector<float>> OnlineBestFit(const std::vector<float>& weights);

        // Computes the offline first fit algorithm for the Bin Packing problem
        std::vector<std::vector<float>> OfflineFirstFit(const std::vector<float>& weights);

        // Computes the offline first fit algorithm for the Bin Packing problem
        std::vector<std::vector<float>> OfflineBestFit(const std::vector<float>& weights);
};
#endif