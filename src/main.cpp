
#include <iostream>
#include "BinPacking.hpp"

int main()
{
    BinPacking bp;
    std::string ITEMS_TXT = "../items.txt";

    bp.ReadFileAndPopulate(ITEMS_TXT, bp.weights);
    bp.OnlineFirstFit(bp.weights);

    return 0;
}