#include "combinationLock.h"
#include <iostream>
#include <cstdlib>

int main( int argc, char* argv[]){
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " N(from 1 to 8)" << std::endl;
        exit(EXIT_FAILURE);
    }

    unsigned int numberOfButtons = atoi(argv[1]);
    if (numberOfButtons<1 || numberOfButtons >8) {
        std::cerr << "Input must be an integer from 1 to 8" << std::endl;
        exit(EXIT_FAILURE);
    }

    CombinationLock combinationLock = CombinationLock(numberOfButtons);
    combinationLock.printAllCombinations();

    return 0;
}
