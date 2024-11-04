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

    std::cout << "Final weights vector contents: ";
    for (const auto& w : weights)
    {
        std::cout << w << " ";
    }
    std::cout << std::endl;

}
