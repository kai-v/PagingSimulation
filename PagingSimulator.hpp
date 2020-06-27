

#ifndef PagingSimulator_hpp
#define PagingSimulator_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include "Process.hpp"
#include "PageTableEntry.hpp"
#include <iomanip>

class PagingSimulator{
    
    friend class Process;
    
public:
    
    PagingSimulator(std::string filename);
    void run();
    int get_num_frames();
    int get_page_size();
    int get_num_pages();
    
private:
    
    // Struct to hold in data we read from the file
    struct read_type{
       
        int process_number;
        std::string action;
        uint32_t memory_location;
    };
    
    // Queue that holds the data from the file
    std::queue<read_type> input_data;
    
    void Paging_Simulation(); // Runs the simulation
    int determine_page(uint32_t location); // Determines which virtual page is referenced 
    int page_size;
    int num_frames;
    int num_pages;
    int num_processes;
    std::vector<Process> processes;
    void print_page_table(Process p,int name);
    void age_process_counters(Process &p);
    int *smallest_page_counter(std::vector<Process> p); // finds the page with the smallest counter
    
};
#endif /* PagingSimulator_hpp */
