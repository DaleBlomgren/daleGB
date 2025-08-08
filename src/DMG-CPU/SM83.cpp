/*****************************
 * Sharp SM83 processor
 * Here, the data structure will be built to emulate
 * everything that is on this awesome SoC.
 * 8-bit 8080-like Sharp CPU
 * CPU FREQ: 4.194304 MHz`
 * CPU will compute 4 ticks for one instruction (4 T-cycles)
 * Will Emulate 'DMG' version CPU
******************************/
#include "SM83.h"
#include "Opcodes.h"
#include "../Memory/Memory.h"
#include <iostream>
#include <cstdint>

class SM83
{
    struct flags{
        Z:bool; // Zero Flag
        N:bool; // Subtract Flag
        H:bool; // Half Carry Flag
        C:bool; // Carry Flag
    };
    public:
        SM83();
        int executeOpcode();
        int movBootRomToMemory();
        void pauseExecution();
        void resumeExecution();
        void setFlags(uint8_t fbits);
        void resetFlags();
        void unsetFlags(uint8_t fbits);
        void writeFlagsAF(uint8_t flagbracket);
        uint8_t convertFlagStruct();

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
        int referenceTableN();
        int referenceTableCB();
        uint64_t cycles;
};


SM83::SM83()
{
    uint8_t A = 0x01;         // Accumulator and Flags
    uint8_t B = 0x00;
    uint8_t C = 0x13;
    uint8_t D = 0x00;
    uint8_t E = 0xD8;         
    uint8_t F = 0x80;        
    uint8_t H = 0x01;
    uint8_t L = 0x4D;
    uint16_t SP = 0xFFFE;        // Stack Pointer
    uint16_t PC = 0x0100;        // Program Counter
    uint64_t cycles = 0; 
    flags.Z = true; // Zero Flag           | These flags may have to line up with a memory address
    flags.N = false; // Subtract Flag
    flags.H = false; // Half Carry Flag
    flags.C = false; // Carry Flag
}

uint16_t SM83::getBC(){
    return (B << 8) | C;
}

uint16_t SM83::getDE(){
    return (D << 8) | E;
}

uint16_t SM83::getHL(){
    return (H << 8) | L;
}

uint16_t SM83::getAF(){
    return (A << 8) | F;
}

int SM83::executeOpcode(){
  // returns number of T-cycles executed
  uint8_t opcode = (PC >> 8) & 0xFF;
  uint8_t block = opcode & 0xC0;
  uint8_t subblock = opcode & 0x38;
  uint8_t endblock = opcode & 0x07;  
  /*
    Check opcode
    execute code
    Increment program counter
    Adjust Flags affected
    return appropriate number of "T-states" (cycles)
  */
  if (block == 0x00){ // 0x00XXXXXX block
    if (subblock == 0x00){ // 0xXX000XXX block
        if (endblock == 0x00){
            // 0x00 - NOP
            PC += 1;
            return 4; // NOP takes 4 T-states
        }

        else if (endblock == 0x01){
            // 0x01 - LD BC,n16
            C = Memory::readByte(PC + 1); // Little-endian order
            B = Memory::readByte(PC + 2);
            PC += 3; 
            return 12; // Returns 12 T-states
        }

        else if (endblock == 0x02){
            // 0x02 - LD [BC],A
            Memory::writeByte(getBC(), A); // Write A to memory at address BC
            PC += 1; 
            return 8;
        }

        else if (endblock == 0x03){ // !! Check here for improvements in the future
            // 0x03 - INC BC
            uint16_t bc = getBC();
            bc++;
            B = (bc >> 8) & 0xFF; 
            C = bc & 0xFF;
            PC += 1;
            return 8;
        }

        else if (endblock == 0x04){
            // 0x04 - Inc B | 1 4 | Z 0 H -
            B++;
            flags.Z = (B == 0); 
            flags.N = false; 
            flags.H = (B & 0x0F) == 0; // Set H flag if lower nibble is 0
            PC += 1;
            return 4; 
        }

        else if (endblock == 0x05){
            // 0x05 - DEC B | 1 4 | Z 1 H -
            B--;
            flags.Z = (B == 0); 
            flags.N = true; 
            flags.H = (B & 0x0F) == 0x0F; // Set H flag if lower nibble is 0x0F
            PC += 1;
            return 4; 
        }

        else if (endblock == 0x06){
           // 0x06 - LD B,n8 | 2 8 | - - - -
           B = Memory::readByte(PC + 1); // Load immediate value into B
           PC += 2;
           return 8; 
        }

        else if (endblock == 0x07){
            // 0x07 - RLCA | 1 4 | 0 0 0 C
            uint8_t carry = A & 0x80; // Check if the highest bit
            A = (A << 1) | (carry >> 7); // Rotate left
            flags.Z = (A == 0); 
            flags.N = false; 
            flags.H = false; 
            flags.C = (carry != 0); // Set C flag if the highest bit was set
            PC += 1; 
            return 4; 
        }
        
    else if (subblock == 0x08){ // 0xXX001XXX block
        if (endblock == 0x00){
            // 0x08 - LD [a16],SP | 3 20 | - - - -
            uint8_t nn_lsb = Memory::readByte(PC + 1); // Read low byte
            uint8_t nn_msb = Memory::readByte(PC + 2); // Read high byte
            uint16_t nn = (nn_msb << 8) | nn_lsb;
            Memory::writeByte(nn, SP & 0xFF); // Write low byte of SP
            Memory::writeByte(nn + 1, (SP >> 8) & 0xFF); // Write high byte of SP
            PC += 3;
            return 20; 
        }

        else if (endblock == 0x01){ // !! revisit this for a more efficient implementation
            // 0x09 - ADD HL,BC | 1 8 | - 0 H C
            uint16_t result, carry_per_bit = getHL() + getBC(); // if problem here, maybe make uint32_t
            flags.C = (carry_per_bit > 0xFFFF); // Set C flag if there was a carry
            flags.N = false; // N flag is always 0 for ADD
            flags.H = ((getHL() & 0x0FFF) + (getBC() & 0x0FFF)) > 0x0FFF; // Set H flag if there was a half carry
            result = getHL() + getBC();
            H = (result >> 8) & 0xFF; // Set high byte
            L = result & 0xFF; // Set low byte
            PC += 1;
            return 8; 
        }
        else if (endblock == 0x02){
            
        }
        else if (endblock == 0x03){
            
        }
        else if (endblock == 0x04){
            
        }
        else if (endblock == 0x05){
            
        }
        else if (endblock == 0x06){
            
        }
        else if (endblock == 0x07){
            
        }
    }
    else if (subblock == 0x10){

    }
    else if (subblock == 0x18){

    }
    else if (subblock == 0x20){

    }
    else if (subblock == 0x28){

    }
    else if (subblock == 0x30){

    }
    else if (subblock == 0x38){

    }
  }

  else if (block == 0x40){ // 0x01xxxxxx block
    if (subblock == 0x00){

    }
    else if (subblock == 0x08){

    }
    else if (subblock == 0x10){

    }
    else if (subblock == 0x18){

    }
    else if (subblock == 0x20){

    }
    else if (subblock == 0x28){

    }
    else if (subblock == 0x30){

    }
    else if (subblock == 0x38){

    }
  }

  else if (block == 0x80){ // 0x10xxxxxx block
    if (subblock == 0x00){

    }
    else if (subblock == 0x08){

    }
    else if (subblock == 0x10){

    }
    else if (subblock == 0x18){

    }
    else if (subblock == 0x20){

    }
    else if (subblock == 0x28){

    }
    else if (subblock == 0x30){

    }
    else if (subblock == 0x38){

    }
  }

  else if (block == 0xC0){ // 0x11xxxxxx block
    if (subblock == 0x00){

    }
    else if (subblock == 0x08){

    }
    else if (subblock == 0x10){

    }
    else if (subblock == 0x18){

    }
    else if (subblock == 0x20){

    }
    else if (subblock == 0x28){

    }
    else if (subblock == 0x30){

    }
    else if (subblock == 0x38){

    }
  }

  else{
    printf("Unknown opcode: 0x%02X at PC: 0x%04X\n", opcode, PC);)
    return -2; // Return -2 if no valid opcode found
  }
  return -1;
}

int SM83::movBootRomToMemory(){
  // code to be executed
  return 0;
}



uint8_t SM83::convertFlagStruct(){
    uint8_t flagbracket = 0x00;
        // code to be executed
    if (flags.Z == true){
        flagbracket |= 0x80; // Set Z flag
    }
    else{
        flagbracket &= ~0x80; // Clear Z flag
  }
    if (flags.N == true){
        flagbracket |= 0x40; // Set N flag
    }
    else{
        flagbracket &= ~0x40; // Clear N flag
    }
    if (flags.H == true){
        flagbracket |= 0x20; // Set H flag
    }
    else{
        flagbracket &= ~0x20; // Clear H flag
    }
    if (flags.C == true){
        flagbracket |= 0x10; // Set C flag
    }
    else{
        flagbracket &= ~0x10; // Clear C flag
    }
    return flagbracket;
}

void SM83::writeFlagsAF(flagbracket){
    F = (F & 0xF0) | (flagbracket & 0x0F); // Set the lower nibble of A to the flags
}

void SM83::setFlags(fbits){
    flags.Z = (fbits & 0x80) != 0; // Set Z flag
    flags.N = (fbits & 0x40) != 0; // Set N flag
    flags.H = (fbits & 0x20) != 0; // Set H flag
    flags.C = (fbits & 0x10) != 0; // Set C flag
}