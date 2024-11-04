
#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    std::string ITEMS_TXT = "../items.txt";

    bp.ReadFileAndPopulate(ITEMS_TXT, bp.weights);
    bp.OnlineFirstFit(bp.weights);
    bp.OnlineNextFit(bp.weights);

    return 0;
}
/*

// C++ program to find number of bins required using
// next fit algorithm.
#include <bits/stdc++.h>
using namespace std;

// Returns number of bins required using next fit
// online algorithm
int nextFit(int weight[], int n, int c)
{
	// Initialize result (Count of bins) and remaining
	// capacity in current bin.
	int res = 0, bin_rem = c;

	// Place items one by one
	for (int i = 0; i < n; i++) {
		// If this item can't fit in current bin
		if (weight[i] > bin_rem) {
			res++; // Use a new bin
			bin_rem = c - weight[i];
		}
		else
			bin_rem -= weight[i];
	}
	return res;
}

// ONLINE FIRST FIT
    std::vector<std::vector<float>> bins;
    std::vector<float> remainingBinWeight;

    for(size_t i = 0; i < weights.size(); i++)
    {
        bool placed = false;

        for(size_t j = 0; j < bins.size(); j++)
        {
            if(remainingBinWeight[j] >= weights[i])
            {
                bins[j].push_back(weights[i]);
                remainingBinWeight[j] -= weights[i];
                placed = true;
                break;
            }
        }

        if(!placed)
        {
            bins.push_back({weights[i]});
            remainingBinWeight.push_back(BIN_CAPACITY - weights[i]);
        }
    }

    std::cout << "Number of Bins Needed: " << bins.size() << std::endl;
    for (size_t i = 0; i < bins.size(); ++i)
    {
        std::cout << "b" << (i + 1) << ": ";
        for (const auto& weight : bins[i])
        {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }
    
    return bins;

*/