
#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    std::string ITEMS_TXT = "../items.txt";

    bp.ReadFileAndPopulate(ITEMS_TXT, bp.weights);
    std::cout << "Online First Fit ->" << std::endl;
    bp.OnlineFirstFit(bp.weights);
    
    std::cout << "Online Next Fit ->" << std::endl;
    bp.OnlineNextFit(bp.weights);
    
    std::cout << "Online Best Fit ->" << std::endl;
    bp.OnlineBestFit(bp.weights);

    std::cout << "Offline First Fit -->" << std::endl;
    bp.OfflineFirstFit(bp.weights);

    std::cout << "Offline Best Fit -->" << std::endl;
    bp.OfflineBestFit(bp.weights);

    return 0;
}