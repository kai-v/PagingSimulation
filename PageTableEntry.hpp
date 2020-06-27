

#ifndef PageTableEntry_hpp
#define PageTableEntry_hpp

#include <stdio.h>
#include <stdint.h>

class PageTableEntry{
    
public:
    
    PageTableEntry(int page_frame_bits);
    uint32_t get_page_table_entry();
    
    void set_reference_bit();
    int get_reference_bit();
    void clear_reference_bit();
    
    void set_modify_bit();
    int get_modify_bit();
    void clear_modify_bit();
    
    void set_present_bit();
    int get_present_bit(); // becuase once its set , the value doesnt change
    void clear_present_bit();
    
    void set_frame_number(int n);
    int get_frame_number();
    
private:
    
    uint32_t page_table_entry;
    int page_frame_bits;
    
};
#endif /* PageTableEntry_hpp */
