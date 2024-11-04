
#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    std::string ITEMS_TXT = "../items.txt";

    bp.ReadFileAndPopulate(ITEMS_TXT, bp.weights);
    bp.OnlineFirstFit(bp.weights);
    std::cout << std::endl;
    bp.OnlineNextFit(bp.weights);
    std::cout << std::endl;
    bp.OnlineBestFit(bp.weights);

    return 0;
}

/**

// C++ program to find number 
// of bins required using
// Best fit algorithm.
#include <bits/stdc++.h>
using namespace std;

// Returns number of bins required using best fit
// online algorithm
int bestFit(int weight[], int n, int c)
{
	// Initialize result (Count of bins)
	int res = 0;

	// Create an array to store 
	// remaining space in bins
	// there can be at most n bins
	int bin_rem[n];

	// Place items one by one
	for (int i = 0; i < n; i++) {
	
		// Find the best bin that can accommodate
		// weight[i]
		int j;

		// Initialize minimum space left and index
		// of best bin
		int min = c + 1, bi = 0;

		for (j = 0; j < res; j++) {
			if (bin_rem[j] >= weight[i] && bin_rem[j] - 
									weight[i] < min) {
				bi = j;
				min = bin_rem[j] - weight[i];
			}
		}

		// If no bin could accommodate weight[i],
		// create a new bin
		if (min == c + 1) {
			bin_rem[res] = c - weight[i];
			res++;
		}
		else // Assign the item to best bin
			bin_rem[bi] -= weight[i];
	}
	return res;
}

// Driver program
int main()
{
	int weight[] = { 2, 5, 4, 7, 1, 3, 8 };
	int c = 10;
	int n = sizeof(weight) / sizeof(weight[0]);
	cout << "Number of bins required in Best Fit : "
		<< bestFit(weight, n, c);
	return 0;
}
//////////





// MINE!!!!!!
std::vector<std::vector<float>> BinPacking::OnlineFirstFit(const std::vector<float>& weights)
{
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
}


* */