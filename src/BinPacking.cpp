#include "BinPacking.hpp"

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
    // 

}


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

    for (size_t i = 0; i < bins.size(); ++i)
    {
        std::cout << "b" << (i + 1) << ": ";
        for (const auto& item : bins[i])
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "num bins: " << bins.size() << std::endl;
    
    return bins;
}
