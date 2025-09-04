
#pragma once

#include <cstdint>
#include <vector>
#include "ROM.h"

class MBC {
    public:
        MBC();
        ~MBC() = default;
    
        uint8_t readByte(uint16_t address) const;
        void writeByte(uint16_t address, uint8_t value);
        void randomizeRAM();
        void setIFR(uint8_t value); //set interrupt flag register
        int setMBCCode(uint8_t code);
    private:
        std::vector<uint8_t> memorybank; // Memory vector to hold the data || std::vector self deletes when it goes out of scope
        uint8_t MBCCode;
};