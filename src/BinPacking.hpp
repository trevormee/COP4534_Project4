/***************************************************************
  Student Name: Trevor Mee
  File Name: BinPacking.hpp
  Project 4

  @brief Contains function declarations for solving the Bin 
         Packing Problem using on-line algorithm approaches
         (First Fit, Next Fit, Best Fit), off-line algorithm
         approaches (First Fit, Best Fit), and using a brute
         force permutation approach
***************************************************************/

#ifndef BINPACKING_HPP
#define BINPACKING_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>

class BinPacking
{
    private:
        // Private Instance Variables
        const int BIN_CAPACITY = 1;
        const std::string ITEMS_TXT = "../items.txt";
        int numItems;

        // Helper function for offline algorithms to sort item weights
        void Sort(std::vector<float>& numbers);

        // Helper function for Sort() to swap two weights if conditions are met
        template <typename T>
        void Swap(T& a, T& b);

        // Helper function to generate the optimal solution
        void perm1(std::vector<float>& s);

        // Helper function to determine how many permutations we loop thru for optimal solution
        int Factorial(int n);

        // Helper function to print bin packing algorithm results in a readable way
        void PrintBins(std::vector<std::vector<float>> algorithm);
       
    public:
        // Public Instance Variables
        std::vector<float> weights;

        // Reads in a text file and populates our weights vector
        void ReadFileAndPopulate(const std::string &fileName, std::vector<float> &weights);

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

        // Computes the optimal solution for the Bin Packing problem
        std::vector<std::vector<float>> OptimalSolution(const std::vector<float>& weights);

        // Solves the Bin Packing Problem and displays the results
        void SolveBinPacking();
};
#endif