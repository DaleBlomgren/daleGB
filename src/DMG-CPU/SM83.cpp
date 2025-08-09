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
            // 0x0A - LD A,[BC] | 1 8 | - - - -
            A = Memory::readByte(getBC()); 
            PC += 1;
            return 8;           
        }

        else if (endblock == 0x03){
            // 0x0B - DEC BC | 1 8 | - - - -
            uint16_t bc = getBC();
            bc--;
            B = (bc >> 8) & 0xFF;
            C = bc & 0xFF;
            PC += 1;
            return 8;
        }

        else if (endblock == 0x04){
            // 0x0C - INC C | 1 4 | Z 0 H -
            C++;
            flags.Z = (C == 0); 
            flags.N = false; 
            flags.H = (C & 0x0F) == 0; 
            PC += 1;
            return 4;
        }

        else if (endblock == 0x05){
            // 0x0D - DEC C | 1 4 | Z 1 H -
            C--;
            flags.Z = (C == 0);
            flags.N = true;
            flags.H = (C & 0x0F) == 0x0F;
            PC += 1;
            return 4;
        }

        else if (endblock == 0x06){
            // 0x0E - LD C,n8 | 2 8 | - - - -
            C = Memory::readByte(PC + 1); 
            PC += 2;
            return 8;
        }

        else if (endblock == 0x07){
            // 0x0F - RRCA | 1 4 | 0 0 0 C
            uint8_t carry = A & 0x01; // Check if the lowest bit is set
            A = (A >> 1) | (carry << 7); // Rotate right
            flags.Z = (A == 0); 
            flags.N = false; 
            flags.H = false; 
            flags.C = (carry != 0); // Set C flag if the lowest bit was set
            PC += 1; 
            return 4;     
        }
    }

    else if (subblock == 0x10){ // 0xXX010XXX block
        if (endblock == 0x00){ // implementation of the STOP instruction is a bit complex
            // 0x10 - STOP n8 | 2 4 | - - - -
            // https://gist.github.com/SonoSooS/c0055300670d678b5ae8433e20bea595#nop-and-stop
            // This is a special case, the CPU will stop executing instructions
            // until a reset or an interrupt occurs.
            uint8_t n8 = Memory::readByte(PC + 1); 
            if (n8 == 0x00) {
                // Stop the CPU
                // This is a no-operation instruction that stops the CPU until an interrupt occurs.
                // In a real implementation, you would set a flag to indicate that the CPU is stopped.
                PC += 2; // Increment PC by 2 to skip the next byte
                return 4; // Return 4 T-states for STOP
            } else {
                printf("Invalid STOP instruction with parameter: 0x%02X at PC: 0x%04X\n", n8, PC);
                return -1; // Invalid STOP instruction
            }
        }

        else if (endblock == 0x01){
            // 0x11 - LD DE,n16 | 3 12 | - - - -
            E = Memory::readByte(PC + 1);
            D = Memory::readByte(PC + 2); 
            PC += 3;
            return 12;
        }

        else if (endblock == 0x02){
            // 0x12 - LD [DE],A | 1 8 | - - - -
            Memory::writeByte(getDE(), A); 
            PC += 1;
            return 8;
        }

        else if (endblock == 0x03){
            // 0x13 - INC DE | 1 8 | - - - -
            uint16_t de = getDE();
            de++;
            D = (de >> 8) & 0xFF; 
            E = de & 0xFF;
            PC += 1;
            return 8;
        }

        else if (endblock == 0x04){
            // 0x14 - INC D | 1 4 | Z 0 H -
            D++;
            lags.Z = (D == 0); 
            flags.N = false; 
            flags.H = (D & 0x0F) == 0; // Set H flag if lower nibble is 0
            PC += 1;
            return 4; 
        }

        else if (endblock == 0x05){
            // 0x15 - DEC D | 1 4 | Z 1 H -
            D--;
            flags.Z = (D == 0); 
            flags.N = true; 
            flags.H = (D & 0x0F) == 0x0F; // Set H flag if lower nibble is 0x0F
            PC += 1;
            return 4; 
        }

        else if (endblock == 0x06){
            // 0x16 - LD D,n8 | 2 8 | - - - -
            D = Memory::readByte(PC + 1);
            PC += 2;
            return 8;
        }

        else if (endblock == 0x07){
            // 0x17 - RLA | 1 4 | 0 0 0 C
            uint8_t carry = flags.C ? 0x01 : 0x00; // Get the current C flag || May be wasteful, could use bool
            A = (A << 1) | carry; // Rotate left with carry
            flags.Z = 0;
            flags.N = false;
            flags.H = false;
            flags.C = (A & 0x80) != 0; // Set C flag if the highest bit was set
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x18){ // 0xXX011XXX block
        if (endblock == 0x00){
            // 0x18 - JR e8 | 2 12 | - - - -
            int8_t offset = Memory::readByte(PC + 1); // Read signed byte
            PC += 2; // Increment PC by 2 to skip the offset byte
            PC += offset; // Add the signed offset to PC
            return 12; 
        }

        else if (endblock == 0x01) {
            // 0x19 - ADD HL,DE | 1 8 | - 0 H C
            uint16_t result, carry_per_bit = getHL() + getDE();
            flags.N = false; // N flag is always 0 for ADD
            flags.H = ((getHL() & 0x0FFF) + (getDE() & 0x0FFF)) > 0x0FFF; // Set H flag if there was a half carry
            flags.C = (carry_per_bit > 0xFFFF); // Set C flag if there was a carry
            result = getHL() + getDE();
            H = (result >> 8) & 0xFF; // Set high byte
            L = result & 0xFF; // Set low byte
            PC += 1; 
            return 8; 
        }

        else if (endblock == 0x02) {
            // 0x1A - LD A,[DE] | 1 8 | - - - -
            A = Memory::readByte(getDE());
            PC += 1;
            return 8;
        }

        else if (endblock == 0x03) {
            // 0x1B - DEC DE | 1 8 | - - - -
            uint16_t de = getDE();
            de--;
            D = (de >> 8) & 0xFF;
            E = de & 0xFF;
            PC += 1;
            return 8;
        }

        else if (endblock == 0x04) {
            // 0x1C - INC E | 1 4 | Z 0 H -
            E++;
            flags.Z = (E == 0);
            flags.N = false;
            flags.H = (E & 0x0F) == 0; 
            PC += 1;
            return 4;
        }

        else if (endblock == 0x05) {
            
        }

        else if (endblock == 0x06) {
            
        }

        else if (endblock == 0x07) {
            
        }
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