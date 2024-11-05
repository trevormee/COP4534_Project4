
#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    //std::string ITEMS_TXT = "../items.txt";
    std::string ITEMS_TXT = "../fakeItems.txt";
    bp.ReadFileAndPopulate(ITEMS_TXT, bp.weights);

    /*
    std::cout << "Online First Fit ->" << std::endl;
    bp.OnlineFirstFit(bp.weights);
    
    std::cout << "Online Next Fit ->" << std::endl;
    bp.OnlineNextFit(bp.weights);
    
    std::cout << "Online Best Fit ->" << std::endl;
    bp.OnlineBestFit(bp.weights);

    std::cout << "Offline First Fit -->" << std::endl;
    bp.OfflineFirstFit(bp.weights);
    */
    //std::cout << "Offline Best Fit -->" << std::endl;
    //bp.OfflineBestFit(bp.weights);

    

    std::cout << "Optimal -->" << std::endl;
    bp.OptimalSolution(bp.weights);

    return 0;
}

/*

std::vector<std::vector<float>> BinPacking::OptimalSolution(const std::vector<float>& weights)
{
    std::vector<std::vector<float>> bestBins;
    int minBins = std::numeric_limits<int>::max();

    // Start with an initial copy of weights to permute
    std::vector<float> permutedWeights = weights;
    Sort(permutedWeights);

    // Compute the total number of permutations
    int totalPermutations = Factorial(weights.size());
    std::cout << "Num Perms to Go thru -> "<< totalPermutations << std::endl;
    // Generate and test each permutation
    for (int i = 0; i < totalPermutations; ++i)
    {
        // Perform bin packing on the current permutation
        std::vector<std::vector<float>> bins = OnlineBestFit(permutedWeights);
        
        // Check if this permutation uses fewer bins
        if (bins.size() < minBins)
        {
            minBins = bins.size();
            bestBins = bins; // Store this as the best configuration
        }

        // Generate the next permutation using perm1
        perm1(permutedWeights);
    }
   
    std::cout << "Number of bins needed: " << bestBins.size() << std::endl;
    for (size_t i = 0; i < bestBins.size(); ++i)
    {
        std::cout << "b" << (i + 1) << ": ";
        for (const auto& weight : bestBins[i])
        {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }

    // Return the best packing configuration
    return bestBins;
}

*/