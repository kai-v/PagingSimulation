

#include "Process.hpp"
#include <vector>
#include <math.h>


Process::Process(int num_pages,int num_frames){
    
    int bits = log2(num_frames);
    
    for(int i = 0 ; i < num_pages ; i++){
        // initiliase to zero
        this->entries.push_back(bits);
        this->counters.resize(num_pages);

    }
}


