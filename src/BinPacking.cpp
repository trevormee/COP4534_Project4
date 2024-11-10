/***************************************************************
  Student Name: Trevor Mee
  File Name: BinPacking.cpp
  Project 4

  @brief Contains function definitions for solving the Bin 
         Packing Problem using on-line algorithm approaches
         (First Fit, Next Fit, Best Fit), off-line algorithm
         approaches (First Fit, Best Fit), and using a brute
         force permutation approach
***************************************************************/

#include "BinPacking.hpp"

/*
    @brief Reads in a text file and populates a vector containing item weights
    @param(s) fileName: text file to read in items from
              weights: vector to hold the weights associated with each item in the text file
*/
void BinPacking::ReadFileAndPopulate(const std::string &fileName, std::vector<float> &weights)
{
    std::ifstream fileRead(fileName);
    
    if(!fileRead)
    {
        std::cerr << "Could not open " << fileName << std::endl;
        return;
    }

    fileRead >> numItems;
    float weight;
    for(int i = 0; i < numItems; ++i)
    {
        fileRead >> weight;
        if(weight < 0 || weight >= 1)
        {
            std::cerr << "Invalid item weight value of " << weight << ", skipping & trashing..." << std::endl;
        }
        else
        {
            weights.push_back(weight);
        }
    }

    fileRead.close();
}


/*
    @brief Computes and Solves the Bin Packing Problem by using the On-line
           First Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
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
    
    return bins;
}


/*
    @brief Computes and Solves the Bin Packing Problem by using the On-line
           Next Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
std::vector<std::vector<float>> BinPacking::OnlineNextFit(const std::vector<float>& weights)
{
    std::vector<std::vector<float>> bins;
    std::vector<float> currBin;
    float remainingBinWeight = BIN_CAPACITY;

    for(size_t i = 0; i < weights.size(); i++)
    {        
        if(weights[i] > remainingBinWeight)
        {
            bins.push_back(currBin);
            currBin = {weights[i]};
            remainingBinWeight = BIN_CAPACITY - weights[i];
        }
        else
        {
            currBin.push_back(weights[i]);
            remainingBinWeight -= weights[i];
        }
    }

    if(currBin.size() != 0)
    {
        bins.push_back(currBin);
    }

    return bins;
}


/*
    @brief Computes and Solves the Bin Packing Problem by using the On-line
           Best Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
std::vector<std::vector<float>> BinPacking::OnlineBestFit(const std::vector<float>& weights)
{
    std::vector<std::vector<float>> bins;
    std::vector<float> remainingBinWeight;
    timespec start, stop;
   // clock_gettime(CLOCK_REALTIME, &start);
    for(size_t i = 0; i < weights.size(); i++)
    {
        float min = BIN_CAPACITY + 1;
        int bestBin = -1;

        for(size_t j = 0; j < remainingBinWeight.size(); j++)
        {
            if(remainingBinWeight[j] >= weights[i] && (remainingBinWeight[j] - weights[i] < min))
            {
                bestBin = j;
                min = remainingBinWeight[j] - weights[i];
            }
        }

        if(bestBin == -1)
        {
            bins.push_back({weights[i]});
            remainingBinWeight.push_back(BIN_CAPACITY - weights[i]);
        }
        else
        {
            bins[bestBin].push_back(weights[i]);
            remainingBinWeight[bestBin] -= weights[i];
        }
    }
     /*
     clock_gettime(CLOCK_REALTIME, &stop);
     double BFseconds = stop.tv_sec - start.tv_sec;
     double BFnanoSeconds = stop.tv_nsec - start.tv_nsec;
     double BFtotalTime = BFseconds + BFnanoSeconds / 1e9;
     std::cout << "Total Run-Time: " << BFtotalTime << std::endl;
    */
    return bins;
}


/*
    @brief Computes and Solves the Bin Packing Problem by using the Off-line
           First Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
std::vector<std::vector<float>> BinPacking::OfflineFirstFit(const std::vector<float>& weights)
{
    std::vector<float> sortedWeights = weights;
     
    Sort(sortedWeights);
    
    return OnlineFirstFit(sortedWeights);
}


/*
    @brief Computes and Solves the Bin Packing Problem by using the Off-line
           Best Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
std::vector<std::vector<float>> BinPacking::OfflineBestFit(const std::vector<float>& weights)
{
    std::vector<float> sortedWeights = weights;

    Sort(sortedWeights);

    return OnlineBestFit(sortedWeights);
}


/*
    @brief Helper function for off-line algorithms to sort item weights
           in descending order. This function uses a version of the 
           bubble sort algorithm to solve this
    @param numbers: vector of weights to sort through
*/
void BinPacking::Sort(std::vector<float>& numbers)
{
    int n = numbers.size();
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(numbers[j] < numbers[j+1])
            {
                Swap(numbers[j], numbers[j+1]);
            }
        }
    }
}

void BinPacking::SortAscending(std::vector<float>& numbers)
{
    int n = numbers.size();
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(numbers[j] > numbers[j+1])
            {
                Swap(numbers[j], numbers[j+1]);
            }
        }
    }
}


/*
    @brief Helper function for Sort() that swaps the values of two
           variables

    @param(s) a: Reference to the first variable
              b: Reference to the second variable
*/
template <typename T>
void BinPacking::Swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}


/*
    @brief Helper function for OptimalSolution() to permutate through (n-1)! 
           potential solutions
    @param s: vector to permutate through
*/
void BinPacking::perm1(std::vector<float>& s)
{
    int m, k, p, q;

    m = numItems - 2;

    while(m >= 0 && s[m] > s[m + 1])
    {
        m = m - 1;
    }
    
    if(m < 0)
    {
        std::cout << "m < 0" << std::endl;
        for(auto& w : s)
        {
            std::cout << w << " ";
        }
        std::cout << std::endl;
        std::reverse(s.begin(), s.end());
        std::cout << "reversal" << std::endl;
        for(auto& w : s)
        {
            std::cout << w << " ";
        }
        return;
    }
    

    k = numItems - 1;
    while(s[m] > s[k])
    {
        k = k - 1;
    }

    Swap(s[m],s[k]);

    p = m + 1;
    q = numItems - 1;
    while (p < q)
    {
        Swap(s[p], s[q]);
        p++;
        q--;
    }

    
}


/*
    @brief Helper function for OptimalSolution() to compute how many
           permutations we will have to go through to obtain the most 
           optimal solution
    @param n: value to compute (n-1)! for 

    @return total number of permutations to go through
*/
int BinPacking::Factorial(int n)
{
    int numPermutations = 1;
    for(int i = 1; i <= n; ++i)
    {
        numPermutations *= i;
    }

    return numPermutations;   
}


/*
    @brief Computes the optimal solution of the Bin Packing Problem in a "brute force" way 
           by going through (numItems - 1)! permutations and keeping the best bin
           layout
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*
std::vector<std::vector<float>> BinPacking::OptimalSolution(const std::vector<float>& weights)
{
     std::vector<std::vector<float>> bestBins;
     int minBins = numItems;

     std::vector<float> firstPermutation, lastPermutation;
     bool isFirst = true;

     std::vector<float> sortedWeights = weights;
     SortAscending(sortedWeights);
     //sortedWeights.push_back(0.0);

     for(const auto& w : sortedWeights)
     {
        std::cout << w << " ";
     }
     std::cout << std::endl;

     int numPermutations = Factorial(numItems);

     int count = 0;
     timespec start, stop;
     clock_gettime(CLOCK_REALTIME, &start);

     for(int i = 0; i < numPermutations; ++i)
     {
        /*
        if(isFirst){
            firstPermutation = sortedWeights;
            isFirst = false;

        }
        *
        
        std::vector<std::vector<float>> currentBins = OnlineNextFit(sortedWeights);
        int currentBinCount = currentBins.size();

        // Check if the current permutation uses fewer bins
        if (currentBinCount < minBins)
        {
            minBins = currentBinCount;
            bestBins = currentBins;
        }
        perm1(sortedWeights);
        count++;

        /*
        if (i == numPermutations - 1)
        {
            lastPermutation = sortedWeights;
        }
        *
     }

     clock_gettime(CLOCK_REALTIME, &stop);
     
     double BFseconds = stop.tv_sec - start.tv_sec;
     double BFnanoSeconds = stop.tv_nsec - start.tv_nsec;
     double BFtotalTime = BFseconds + BFnanoSeconds / 1e9;
     std::cout << "Total Permutation Run-Time: " << BFtotalTime << std::endl;
     std::cout << "Count = " << count << std::endl;
    /*
     std::cout << "First permutation: ";
    for (const auto &weight : firstPermutation) {
        std::cout << weight << " ";
    }
    std::cout << std::endl;

    std::cout << "Last permutation: ";
    for (const auto &weight : lastPermutation) {
        std::cout << weight << " ";
    }   
    std::cout << std::endl;
    *

    /*
     int numPermutations = Factorial(numItems - 1);

     for(int i = 0; i < numPermutations; ++i)
     {
        std::vector<std::vector<float>> currBinPermuatation = OnlineBestFit(sortedWeights);
        int currNumOfBins = currBinPermuatation.size();
        
        if(currNumOfBins < minBins)
        {
            minBins = currBinPermuatation.size();
            bins = currBinPermuatation;
        }

        perm1(sortedWeights);
     }
     *
    
    return bestBins;
}
*/

std::vector<std::vector<float>> BinPacking::OptimalSolution(const std::vector<float>& weights)
{
     std::vector<std::vector<float>> bins;
     int minBins = numItems;

     std::vector<float> sortedWeights = weights;
     SortAscending(sortedWeights);
     //Sort(sortedWeights);

     int numPermutations = Factorial(numItems);

     timespec start, stop, start2, stop2;
     clock_gettime(CLOCK_REALTIME, &start);
     int count = 0;
     for(size_t i = 0; i < numPermutations; ++i)
     {
        perm1(sortedWeights);
        count++;
     }

     clock_gettime(CLOCK_REALTIME, &stop);
     double BFseconds = stop.tv_sec - start.tv_sec;
     double BFnanoSeconds = stop.tv_nsec - start.tv_nsec;
     double BFtotalTime = BFseconds + BFnanoSeconds / 1e9;
     std::cout << "Total Permutation Run-Time: " << BFtotalTime << std::endl;
     std::cout << "count = " << count << std::endl;

     clock_gettime(CLOCK_REALTIME, &start2);

     //int i = permuationPopulation.size() - 1; i >= 0; --i
     for()
     {
        std::vector<std::vector<float>> currBinPermuatation = OnlineBestFit(sortedWeights);
        int currNumOfBins = currBinPermuatation.size();
        
        if(currNumOfBins < minBins)
        {
            minBins = currBinPermuatation.size();
            bins = currBinPermuatation;
        }

        if(minBins == 6)
        {
            std::cout << "hit break" << std::endl;
            break;
        }
     }
     clock_gettime(CLOCK_REALTIME, &stop2);
     double seconds = stop2.tv_sec - start2.tv_sec;
     double nanoSeconds = stop2.tv_nsec - start2.tv_nsec;
     double totalTime = seconds + nanoSeconds / 1e9;
     std::cout << "Total Packing Run-Time: " << totalTime << std::endl;

    return bins;
}

/*
std::vector<std::vector<float>> BinPacking::OptimalSolution(const std::vector<float>& weights) {
    std::vector<std::vector<float>> bestBins;
    int minBins = numItems;
    int count = 0;

    std::vector<float> sortedWeights = weights;
    SortAscending(sortedWeights);

    int numPermutations = Factorial(numItems);

    timespec start, current;
    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < numPermutations; ++i) {
        // Pack the current permutation
        std::vector<std::vector<float>> currentBins = OnlineNextFit(sortedWeights);
        int currentBinCount = currentBins.size();

        // Check if this packing is better
        if (currentBinCount < minBins) {
            minBins = currentBinCount;
            bestBins = currentBins;
        }

        // Generate next permutation
        perm1(sortedWeights);
        count++;

        // Check elapsed time
        clock_gettime(CLOCK_REALTIME, &current);
        double secondsElapsed = current.tv_sec - start.tv_sec + (current.tv_nsec - start.tv_nsec) / 1e9;
        
        if (secondsElapsed > 30.0) {
            std::cout << "Exceeded 30 seconds. Permutations attempted: " << count << std::endl;
            break;
        }
        
    }

    std::cout << "Total Permutation Run-Time: " << " seconds" << std::endl;
    std::cout << "Count = " << count << std::endl;

    return bestBins;
}

*/


/*
    @brief Helper function for SolveBinPacking() to print each algorithms
           bin setup after completing said algorithm
    @param algorithm: vector of a vector of floats to loop through
*/
void BinPacking::PrintBins(std::vector<std::vector<float>> algorithm)
{
    for (size_t i = 0; i < algorithm.size(); ++i)
    {
        std::cout << "b" << (i + 1) << ": ";
        for (const auto& weight : algorithm[i])
        {
            std::cout << weight << " ";
        }
        std::cout << std::endl;
    }
}

/*
    @brief Runs each bin packing solution algorithm and prints
           out results in a readable format
*/
void BinPacking::SolveBinPacking()
{
    // Read in file and populate item weights vector
    ReadFileAndPopulate(ITEMS_TXT, weights);

    int colWidth = 20;

    std::cout << std::left << std::setw(colWidth) << "Policy" << std::setw(colWidth) << "Total Bins Used" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    // Optimal Solution
    std::vector<std::vector<float>> optimalSolution = OptimalSolution(weights);
    int numBinsOptimalSolution = optimalSolution.size();
    std::cout << std::left << std::setw(colWidth) << "Optimal Solution" << std::setw(colWidth) << numBinsOptimalSolution << std::endl;
    std::cout << std::string(16, '-') << std::endl;

    std::cout << std::left << std::setw(colWidth) << "Online Algorithm" << std::endl;
    std::cout << std::string(16, '-') << std::endl;

    // Online First Fit
    std::vector<std::vector<float>> onlineFirstFit = OnlineFirstFit(weights);
    int numBinsOnlineFirstFit = onlineFirstFit.size();
    std::cout << std::left << std::setw(colWidth) << "First Fit" << std::setw(colWidth) << numBinsOnlineFirstFit << std::endl;
    
    // Online Next Fit
    std::vector<std::vector<float>> onlineNextFit = OnlineNextFit(weights);
    int numBinsOnlineNextFit = onlineNextFit.size();
    std::cout << std::left << std::setw(colWidth) << "Next Fit" << std::setw(colWidth) << numBinsOnlineNextFit << std::endl;
    
    // Online Best Fit
    std::vector<std::vector<float>> onlineBestFit = OnlineBestFit(weights);
    int numBinsOnlineBestFit = onlineBestFit.size();
    std::cout << std::left << std::setw(colWidth) << "Best Fit" << std::setw(colWidth) << numBinsOnlineBestFit << std::endl;

    std::cout << std::left << std::setw(colWidth) << "Offline Algorithm" << std::endl;
    std::cout << std::string(17, '-') << std::endl;

    // Offline First Fit
    std::vector<std::vector<float>> offlineFirstFit = OfflineFirstFit(weights);
    int numBinsOfflineFirstFit = offlineFirstFit.size();
    std::cout << std::left << std::setw(colWidth) << "First Fit" << std::setw(colWidth) << numBinsOfflineFirstFit << std::endl;

    // Offline Best Fit
    std::vector<std::vector<float>> offlineBestFit = OfflineBestFit(weights);
    int numBinsOfflineBestFit = offlineBestFit.size();
    std::cout << std::left << std::setw(colWidth) << "Best Fit" << std::setw(colWidth) << numBinsOfflineBestFit << std::endl;

    // Print each bin packing solution
    std::cout << "\nOptimal Solution:" << std::endl;
    PrintBins(optimalSolution);
    std::cout << "\nOnline First Fit:" << std::endl;
    PrintBins(onlineFirstFit);
    std::cout << "\nOnline Next Fit:" << std::endl;
    PrintBins(onlineNextFit);
    std::cout << "\nOnline Best Fit:" << std::endl;
    PrintBins(onlineBestFit);
    std::cout << "\nOffline First Fit:" << std::endl;
    PrintBins(offlineFirstFit);
    std::cout << "\nOffline Best Fit:" << std::endl;
    PrintBins(offlineBestFit);
 }