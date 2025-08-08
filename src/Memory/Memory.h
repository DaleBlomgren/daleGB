
#pragma once

#include <cstdint>
#include <vector>
#include "ROM.h"

class Memory {
    public:
        Memory();
        ~Memory() = default;
    
        uint8_t readByte(uint16_t address) const;
        void writeByte(uint16_t address, uint8_t value);
        void randomizeRAM();
    private:
        std::vector<uint8_t> memorybank; // Memory vector to hold the data || std::vector self deletes when it goes out of scope
};