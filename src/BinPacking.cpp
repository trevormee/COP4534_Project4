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

    // Delete at submission - only used for testing! 
    std::cout << "Final weights vector contents: ";
    for (const auto& w : weights)
    {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    // DELETE!

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


/*
    @brief Computes and Solves the Bin Packing Problem by using the On-line
           Next Fit algorithm
    @param weights: vector of item weights to iterate and pack through

    @return bins with populated item weights in each bin
*/
std::vector<std::vector<float>> BinPacking::OnlineNextFit(const std::vector<float>& weights)
{
    std::vector<std::vector<float>> bins;
    //std::vector<float> remainingBinWeight;
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