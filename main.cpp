
#include <iostream>
#include <stdio.h>
#include <bitset>
#include "PageTableEntry.hpp"
#include "PagingSimulator.hpp"

int main(int argc, const char * argv[]) {
    
    std::string filename;
    
    if(argc > 2){ //Usage Error
        
        std::cerr << "Usage: ./Project8 <filename>" << std::endl;
        return 1;
    }
    
    if(argc < 2){ //Usage Error
        
        std::cerr << "Usage: ./Project8 <filename>" << std::endl;
        return 1;
    }
    
    else{
        
        filename = argv[1];
    }
    
    PagingSimulator p(filename);
    p.run();
    
    return 0;
}
