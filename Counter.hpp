

#ifndef Counter_hpp
#define Counter_hpp
#include <stdio.h>
#include <stdint.h>

class Counter{
    
public:
    Counter();
    uint8_t get_counter();
    void age_counter(int ref_bit);
    void reset_counter();
    
private:
    
    uint8_t counter;
    
};
#endif /* Counter_hpp */
