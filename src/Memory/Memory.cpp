/******************* Memory Map ****************************
 * 0000-3FFF: 16kB ROM bank #0
 * 4000-7FFF: 16kB switchable ROM bank
 * 8000-9FFF: Video RAM
 * A000-BFFF: 8kB switchable RAM bank
 * C000-DFFF: 8kB internal RAM
 * E000-FDFF: Echo of 8kB Internal RAM
 * FE00-FE9F: Sprite Attribute Memory (OAM)
 * FEA0-FEFF: Empty but unusable for I/O
 * FF00-FF4B: I/O
 * FF4C-FF7F: Empty but unusable for I/O
 * FF80-FFFE: Internal RAM
 * FFFF: Interrupt Enable Register
 * Total Addressable Memory: 65536 bytes or 64KB
********************************************************/

#include <random>
#include "Memory.h"


/*class Memory {
public:
    Memory();
    ~Memory() = default;

    // Function to read a byte from memory
    uint8_t readByte(uint16_t address) const;

    // Function to write a byte to memory
    void writeByte(uint16_t address, uint8_t value);
    void randomizeRAM(); //Randomize WRAM and HRAM
    int readToROMBank(ROM& rom);
private:
    std::vector<uint8_t> memorybank; // Memory vector to hold the data || std::vector self deletes when it goes out of scope
};
*/

Memory::Memory() {
    memorybank.resize(65536,0); // Initialize memory with 64KB
    randomizeRAM();
}

void Memory::randomizeRAM() {
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator with Mersenne twister algorithm
    std::uniform_int_distribution<> distr(0, 255); // Define the range

    for (size_t i = 0xC000; i < 0xFFFF; ++i) { // Randomize WRAM and HRAM
        memorybank[i] = static_cast<uint8_t>(distr(gen));
    }
}

uint8_t Memory::readByte(uint16_t address) const {
    if (address < memorybank.size()) {
        return memorybank[address];
    }
    return 0; // Return 0 if address is out of bounds
}
void Memory::writeByte(uint16_t address, uint8_t value) {
    if (address < memorybank.size()) {
        memorybank[address] = value;
    }
}