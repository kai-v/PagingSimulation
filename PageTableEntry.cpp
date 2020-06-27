

#include "PagingSimulator.hpp"
#include <bitset>


PageTableEntry::PageTableEntry(int page_frame_bits){
    
    this->page_frame_bits = page_frame_bits;
    page_table_entry = 0;
    
}

uint32_t PageTableEntry::get_page_table_entry(){
    
    return page_table_entry;
}

void PageTableEntry::set_reference_bit(){
    
    uint32_t one = 1;
    page_table_entry |= one << 31;
}

int PageTableEntry::get_reference_bit(){
    
    uint32_t one = 1;
    
    if((page_table_entry & (one << 31)) != 0){
        
        return 1;
    }
    return 0;
}

void PageTableEntry::clear_reference_bit(){
    
    uint32_t one = 1;
    page_table_entry &= ~(one << 31);
}


void PageTableEntry::set_modify_bit(){
    
    uint32_t one = 1;
    page_table_entry |= one << 30;
    
}
int PageTableEntry::get_modify_bit(){
    
    uint32_t one = 1;
    
    if((page_table_entry & (one << 30)) != 0){
        
        return 1;
    }
    
    return 0;
}

void PageTableEntry::clear_modify_bit(){
    
    uint32_t one = 1;
    page_table_entry &= ~(one << 30);
}

int PageTableEntry::get_present_bit(){
    
    uint32_t one = 1;
    uint32_t temp = page_table_entry;
    
    if((temp & (one << 29)) != 0){
        
        return 1;
    }
    
    return 0;
}

void PageTableEntry::set_present_bit(){
    
    uint32_t one = 1;
    page_table_entry |= one << 29;
    
}

void PageTableEntry::clear_present_bit(){
    
    uint32_t one = 1;
    
    page_table_entry &= ~(one << 29);
}

void PageTableEntry::set_frame_number(int n){
    
    uint32_t one = 1;
    for(int i = 0; i < page_frame_bits ; i++){
        
        // If that corrosponsing digit in n is 1 , then set bit page table entry
        if((n & (one << i)) != 0) {
            (page_table_entry |= one << i);
        }
        
        // If its a 0 , clear that corrosponding digit in page table entry
        else{
            page_table_entry &= ~(one << i);
        }
        
    }
}

int PageTableEntry::get_frame_number(){
    
    uint32_t one = 1;
    return ((one << page_frame_bits) - 1) & (page_table_entry >> (1 - 1));
    
}


