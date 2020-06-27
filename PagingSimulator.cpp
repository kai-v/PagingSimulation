
#include "PagingSimulator.hpp"
#include <iostream>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <iomanip>

PagingSimulator::PagingSimulator(std::string filename){
    
    /* We load every word from the file into a queue and sequentially access it */
    
    std::queue<std::string> store; //  queue to hold all the words
    std::ifstream read_file(filename);
    std::string input;
    
    // FILE I/0
    if (!(read_file.is_open())){  // If file cannot open then throw and error.
        std::cerr << "Could not open file" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::string line;
    while (getline (read_file, line)) { // Reading the line
        
        std::istringstream stream(line);
        std::string word;
        
        while (stream >> word){ // Reading each word in the line
            store.push(word); // push each word into the queue
        }
    }
    
    num_pages = stoi(store.front());
    store.pop();
    
    num_frames = stoi(store.front());
    store.pop();
    
    page_size = stoi(store.front());
    store.pop();
    
    num_processes = stoi(store.front());
    store.pop();
    
    std::cout << "INITIAL TABLE SETUP:" << std::endl;
    std::cout << "Virtual Memory size: " << num_pages * page_size << std::endl;
    std::cout << "Physical Memory size: " << page_size * num_frames << std::endl;
    std::cout << "Page size: " << page_size << std::endl;
    std::cout << "Number of Processes: " << num_processes << std::endl;
    std::cout << "Number of Pages: " << num_pages << std::endl;
    std::cout << "Number of frames: " << num_frames << std::endl;
    
    // Create the queue with data from the file
    while(!store.empty()){
        
        int process_name = stoi(store.front());
        store.pop();
        
        std::string action = store.front();
        store.pop();
        
        uint32_t location = stoi(store.front());
        store.pop();
        
        read_type r = {process_name,action,location};
        
        input_data.push(r);
        
    }
    
    // create our processes
    for(int i = 0 ; i < num_processes; i++){
        
        processes.push_back({num_pages,num_frames});
    }
    
}

void PagingSimulator::run(){
    
    Paging_Simulation();
}

int PagingSimulator::get_num_frames(){
    
    return num_frames;
}

int PagingSimulator::get_page_size(){
    
    return page_size;
}

int PagingSimulator::get_num_pages(){
    
    return num_pages;
}

// Determines which virtual page is referenced
int PagingSimulator::determine_page(uint32_t location){
    
    return location/page_size;
}

// Prints the page table for a process
void PagingSimulator::print_page_table(Process p, int name){
    
    std::cout << "Process " << name << std::endl;
    std::cout << std::setw(10) << std::left << "page# " << std::setw(10) << std::left << "R" <<  std::setw(10) << "M" << std::setw(10) << "P" << std::setw(15) << "frame#" << std::setw(20) << "aging" << std::endl;
    
    for(int i = 0; i < num_pages; i++){
        
        // If the presnt bit is not set , then we dont print the counter
        if(p.entries.at(i).get_present_bit() == 0){
            
            std::cout << std::setw(10) << std::left << i << std::setw(10) << p.entries.at(i).get_reference_bit() <<  std::setw(10) << p.entries.at(i).get_modify_bit() << std::setw(10) << p.entries.at(i).get_present_bit() << std::setw(15) << p.entries.at(i).get_frame_number() << std::setw(20) << " " << std::endl;
        }
        
        else{
            std::cout << std::setw(10) << std::left << i  << std::setw(10) << p.entries.at(i).get_reference_bit() <<  std::setw(10) << p.entries.at(i).get_modify_bit() << std::setw(10) << p.entries.at(i).get_present_bit() << std::setw(15) << p.entries.at(i).get_frame_number() << std::setw(20) << std::bitset<8>(p.counters.at(i).get_counter()) << std::endl;
        }
        
    }
}

// Ages all the counters for a given process
void PagingSimulator::age_process_counters(Process &p){
    
    for(int i = 0; i < num_pages; i++){
        
        p.counters.at(i).age_counter(p.entries.at(i).get_reference_bit());
        p.entries.at(i).clear_reference_bit();
        
    }
}

// Returns the process and page with the smallest counter
int * PagingSimulator::smallest_page_counter(std::vector<Process> p){
    
    uint8_t smallest = INT8_MAX;
    static int r[2]; // return type
    
    for(int i = 0; i < num_processes; i++){
        for(int j = 0; j < num_pages; j++ ){
            
            if(p.at(i).entries.at(j).get_present_bit() == 1){ // we only check the ones whos presnt bit is set
                
                if(p.at(i).counters.at(j).get_counter() < smallest){
                    
                    smallest = p.at(i).counters.at(j).get_counter();
                    r[0] = i;
                    r[1] = j;
                    
                }
            }
        }
        
    }
    
    return r;
}

// Runs the paging simulation
void PagingSimulator::Paging_Simulation(){
    
    int frame_number = 0;
    int instruction_count = 0;
    bool all_frames_used = false; // Tells us whether or not all frames are occupied
    
    // Print Initial Processes
    std::cout << "Page Tables (with aging status) " << std::endl;
    for(int i = 0 ; i < num_processes; i++){
        
        print_page_table(processes.at(i),i);
    }
    
    while(!input_data.empty()){
        
        int current_process_name = input_data.front().process_number;
        std::string action_type = input_data.front().action;
        uint32_t location_requested = input_data.front().memory_location;
        int page = determine_page(location_requested);
        
        Process &current_process =  processes.at(current_process_name);
        PageTableEntry &current_entry = current_process.entries.at(page);
        
        // If all frames are occupied
        if(frame_number == num_frames){
            
            all_frames_used = true;
        }
        
        std::cout << "Process " << current_process_name << " requests " << input_data.front().action << " " << location_requested << std::endl;
        std::cout << "Page number " << page << std::endl;
        
        instruction_count++;
        // If the page is not present in the table
        if(current_entry.get_present_bit() == 0){
            
            // The initial pages being added
            if(all_frames_used == false){
                
                std::cout << "Page fault ... " << std::endl;
                std::cout << "Loading page " << page << " of process " << current_process_name << " onto frame " << frame_number << std::endl;
                
                
                current_entry.set_reference_bit();
                current_entry.set_frame_number(frame_number);
                current_entry.set_present_bit();
                
                if(frame_number <= num_frames){
                    
                    frame_number++;
                }
            }
            
            // If all the frames are currently occupied , we need to evict a page
            else {
                
                int * evict = smallest_page_counter(processes); // looks for the page to evict
                PageTableEntry &prev_page = processes.at(evict[0]).entries.at(evict[1]);
                
                std::cout << "Page fault ... " << std::endl;
                std::cout << "Evicting Process " << evict[0] << " Page " << evict[1] << std::endl;
                
                if(prev_page.get_modify_bit() == 1){
                    
                    std::cout << "Writing frame " << prev_page.get_frame_number() << " back to disk: " << std::endl;
                    prev_page.clear_modify_bit();
                }
                
                
                std::cout << "Loading Page " << page << " of process " << current_process_name << " onto frame " <<
                prev_page.get_frame_number() << std::endl;
                
                // Loading the new page ...
                current_entry.set_reference_bit();
                current_entry.set_frame_number(prev_page.get_frame_number());
                current_entry.set_present_bit();
                
                // Evicting the old one ...
                prev_page.clear_present_bit();
                prev_page.clear_reference_bit();
                processes.at(evict[0]).counters.at(page).reset_counter();
                
            }
        }
        
        // If we have a write
        if(action_type == "w" ){
            
            current_entry.set_reference_bit();
            current_entry.set_modify_bit();
            
        }
        
        // If we have a read
        else{
            current_entry.set_reference_bit();
        }
        
        // Age the counters, every two instructions
        if(instruction_count % 2 == 0){
            
            for(int i = 0; i < num_processes; i++){
                
                age_process_counters(processes.at(i));
                
            }
        }
        
        int offset = location_requested % page_size;
        std::cout << "Frame number " << current_process.entries.at(page).get_frame_number() << std::endl;
        std::cout << "Physical address " << (page_size * current_process.entries.at(page).get_frame_number()) + offset  << std::endl;
        
        std::cout << "Page Tables (with aging status) " << std::endl;
        for(int i = 0; i < num_processes; i++){
            
            print_page_table(processes.at(i),i);
            
        }
        
        input_data.pop();
    }
}



