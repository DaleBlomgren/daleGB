#pragma once
#include <cstdint>
#include "../Memory/MBC.h"

// Forward declare the class first
class SM83;


// Declare the namespace and its functions
namespace CBInstructions {
    int executeCB(SM83& cpu, MBC& memoryBank);
}

class SM83 {
    // Make the function a friend
    friend int CBInstructions::executeCB(SM83& cpu, MBC& memoryBank);
    
    struct flags {
        bool Z; // Zero Flag
        bool N; // Subtract Flag
        bool H; // Half Carry Flag
        bool C; // Carry Flag
    };
    public:
        SM83(&memoryBank);
        int executeOpcode();
        int movBootRomToMemory();
        void pauseExecution();
        void resumeExecution();
        void IMEEnable(); //enable interrupt master enable flag
        void IMEDisable(); //disable interrupt master enable flag
        void setFlags(uint8_t fbits);
        void resetFlags();
        void unsetFlags(uint8_t fbits);
        void writeFlagsAF(uint8_t flagbracket);

    private:
        uint8_t A;         // Accumulator and Flags
        uint8_t B;
        uint8_t C;
        uint8_t D;
        uint8_t E;         
        uint8_t F;     
        uint8_t H;  
        uint8_t L;  
        uint16_t SP;        // Stack Pointer
        uint16_t PC;        // Program Counter
        uint16_t getBC();        
        uint16_t getDE();
        uint16_t getHL();
        uint16_t getAF();
        //MBC memoryBank;
        int executeCB(MBC& memoryBank);
        flags flags;
        bool IME; // Interrupt Master Enable Flag
        bool halted; // CPU Halted State
        bool haltBug; // HALT Bug State
        void setFlags();
        uint8_t convertFlagStruct();
        uint64_t cycles;
};