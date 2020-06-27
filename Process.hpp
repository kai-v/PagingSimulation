

#ifndef Process_hpp
#define Process_hpp

#include <stdio.h>
#include "Counter.hpp"
#include "PageTableEntry.hpp"
#include <vector>

class Process{
    
public:

    friend class PagingSimulator;
    Process(int num_pages,int num_frames);
   
private:

    std::vector<PageTableEntry> entries;
    std::vector<Counter> counters;
   
};
#endif /* Process_hpp */
