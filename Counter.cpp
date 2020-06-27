//
//  Counter.cpp
//  Project 8
//
//  Created by Kai Velagapudi on 5/27/20.
//  Copyright © 2020 Kai Velagapudi. All rights reserved.
//

#include <bitset>
#include "Counter.hpp"

Counter::Counter(){
    
    counter = 0;
}

void Counter::age_counter(int ref_bit){
    
    // right shift the counter by 1
    counter >>= 1;
    
    // If the reference bit is 1 , then we set the left most bit to 1
    if(ref_bit == 1){
    
    uint8_t one = 1;
    counter |= one << 7;
    
    }
    
    // else if the reference bit is 0 we do nothing
}

uint8_t Counter::get_counter(){
    
    return counter;
}

void Counter::reset_counter(){
    
    counter = 0;
}
