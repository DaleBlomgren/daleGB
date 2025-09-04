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
#include "../Memory/Memory.h"
#include "executeCB.h"
#include <iostream>
#include <cstdint>

/*class SM83
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
        //void setFlags(uint8_t fbits);
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
//        int referenceTableN();
//        int referenceTableCB();
//        int executeCB();
        flags flags;
        void setFlags();
        uint64_t cycles;
}*/

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
    IME = 0;
    halted = false;
    haltBug = false;
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
            // 0x1D - DEC E | 1 4 | Z 1 H -
            E--;
            flags.Z = (E == 0);
            flags.N = true;
            flags.H = (E & 0x0F) == 0x0F;
            PC += 1;
            return 4;
        }

        else if (endblock == 0x06) {
            // 0x1E - LD E,n8 | 2 8 | - - - -
            E = Memory::readByte(PC + 1); 
            PC += 2;
            return 8;
        }

        else if (endblock == 0x07) {
            // 0x1F - RRA | 1 4 | 0 0 0 C
            uint8_t carry = flags.C ? 0x80 : 0x00; // Get the current C flag | May be wasteful, could use bool
            A = (A >> 1) | carry; // Rotate right with carry
            flags.Z = 0;
            flags.N = false;
            flags.H = false;
            flags.C = (A & 0x01) != 0; 
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x20){ // 0xXX100XXX block
        if (endblock == 0x00){
            // 0x20 - JR NZ, e8 | 2 12 | - - - -
            if (flags.Z == false) {
                int8_t offset = Memory::readByte(PC + 1); // Read signed byte
                PC += 2; // Increment PC by 2 to skip the offset byte
                PC += offset; // Add the signed offset to PC
                return 12; 
            } else {
                PC += 2; // Skip the offset if Z flag is set
                return 8; // Return 8 T-states for JR NZ
            }
        }

        else if (endblock == 0x01){
            // 0x21 - LD HL, n16 | 3 12 | - - - -
            L = Memory::readByte(PC + 1); 
            H = Memory::readByte(PC + 2); 
            PC += 3; 
            return 12; 
        }

        else if (endblock == 0x02){
            // 0x22 - LD [HL+], A | 1 8 | - - - -
            Memory::writeByte(getHL(), A); // !! May be wrong,we want to load data from A register to 16-bit absolute address specified by HL
            uint16_t hl = getHL();
            hl++;
            H = (hl >> 8) & 0xFF;
            L = hl & 0xFF; // Increment HL after writing
            PC += 1;
            return 8;   
        }

        else if (endblock == 0x03){
            // 0x23 - INC HL | 1 8 | - - - -
            uint16_t hl = getHL();
            hl++;
            H = (hl >> 8) & 0xFF; 
            L = hl & 0xFF;
            PC += 1;
            return 8;
        }

        else if (endblock == 0x04){
            // 0x24 - INC H | 1 4 | Z 0 H -
            H++;
            flags.Z = (H == 0); 
            flags.N = false; 
            flags.H = (H & 0x0F) == 0; 
            PC += 1;
            return 4;
        }

        else if (endblock == 0x05){
            // 0x25 - DEC H | 1 4 | Z 1 H -
            H--;
            flags.Z = (H == 0); 
            flags.N = true; 
            flags.H = (H & 0x0F) == 0x0F; 
            PC += 1;
            return 4;
        }

        else if (endblock == 0x06){
            // 0x26 - LD H, n8 | 2 8 | - - - -
            H = Memory::readByte(PC + 1); 
            PC += 2;
            return 8;
        }

        else if (endblock == 0x07){ // !! kinda complicated, but helpful resource here: https://blog.ollien.com/posts/gb-daa/
            // 0x27 - DAA | 1 4 | Z 0 H C
            bool should_carry = false;
            if(flags.N == true) { //check to see if subtract flag N is set
                uint8_t adjust = 0x00;
                if (flags.C == true || A > 0x99) { 
                    adjust |= 0x60; // Set C flag and adjust for carry 
                }
                if (flags.H == true || (A & 0x0F) > 0x09) { 
                    adjust |= 0x06; // Set H flag and adjust for half carry
                }
                A -= adjust; // Subtract the adjustment value
                flags.Z = (A == 0); // Set Z flag if A is zero
                flags.H = false; // Clear H flag
                flags.C = (A > 0x99); // Set C flag if A is greater than 0x99
                pc += 1; // Increment PC
                return 4; // Return 4 T-states for DAA
            }
            else{ //subtract flag n not set
                uint8_t adjust = 0x00;
                if (flags.C == true || A > 0x99) { 
                    adjust |= 0x60; // Set C flag and adjust for carry
                }
                if (flags.H == true || (A & 0x0F) > 0x09) { 
                    adjust |= 0x06; // Set H flag and adjust for half carry 
                }
                A += adjust; // Add the adjustment value
                flags.Z = (A == 0); // Set Z flag if A is zero
                flags.H = false; // Clear H flag
                flags.C = (A > 0x99); // Set C flag if A is greater than 0x99
                PC += 1; // Increment PC
                return 4; // Return 4 T-states for DAA
            }

        }
    }
    else if (subblock == 0x28){
        if (endblock == 0x00){ 
            // 0x28 - JR Z, e8 | 2 12/8 | ---- 
            if (flag.Z == true) { 
                int8_t offset = Memory::readByte(PC + 1); // Read signed byte
                PC += 2; // Increment PC by 2 to skip the offset byte
                PC += offset; // Add the signed offset to PC
                return 12; // Return 12 T-states for JR Z
            } else {
                PC += 2; // Skip the offset if Z flag is not set
                return 8; 
            }
        }
        else if (endblock == 0x01){
            // 0x29 - ADD HL,HL | 1 8 | - 0 H C
            uint16_t result, carry_per_bit = getHL() + getHL(); // if problem here, maybe make uint32_t
            flags.C = (carry_per_bit > 0xFFFF); // Set C flag if there was a carry
            flags.N = false; // N flag is always 0 for ADD
            flags.H = ((getHL() & 0x0FFF) + (getHL() & 0x0FFF)) > 0x0FFF; // Set H flag if there was a half carry
            result = getHL() + getHL();
            H = (result >> 8) & 0xFF; // Set high byte
            L = result & 0xFF; // Set low byte
            PC += 1;
            return 8;            
        }
        else if (endblock == 0x02){
            // 0x2A - LD A,[HL+] | 1 8 | - - - -
            A = Memory::readByte(getHL()); // Load data from memory at address HL into A
            uint16_t hl = getHL();
            hl++;
            H = (hl >> 8) & 0xFF; // Increment HL after reading
            L = hl & 0xFF; // Increment HL after reading
            PC += 1;
            return 8;
        }
        else if (endblock == 0x03){
            // 0x2B - DEC HL | 1 8 | - - - -
            uint16_t hl = getHL();
            hl--;
            H = (hl >> 8) & 0xFF; // Decrement HL
            L = hl & 0xFF; // Decrement HL
            PC += 1;
            return 8;
        }
        else if (endblock == 0x04){
            // 0x2C - INC L | 1 4 | Z 0 H -
            L++;
            flags.Z = (L == 0); 
            flags.N = false; 
            flags.H = (L & 0x0F) == 0; // Set H flag if lower nibble is 0
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x05){
            // 0x2D - DEC L | 1 4 | Z 1 H -
            L--;
            flags.Z = (L == 0); 
            flags.N = true; 
            flags.H = (L & 0x0F) == 0x0F; // Set H flag if lower nibble is 0x0F
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x06){
            // 0x2E - LD L,n8 | 2 8 | - - - -
            L = Memory::readByte(PC + 1); // Load immediate value into L
            PC += 2;
            return 8; 
        }
        else if (endblock == 0x07){
            // 0x2F - CPL | 1 4 | - 1 1 - AKA bitwise NOT
            A = ~A; 
            flags.N = true; 
            flags.H = true; 
            PC += 1;
            return 4;      
        } 
    }
    else if (subblock == 0x30){
        if (endblock == 0x00){
            //0x30 - JR NC, e8 | 2 12/8 | - - - -
            if (flags.C == false) { // Check if C flag is not set
                int8_t offset = Memory::readByte(PC + 1); 
                PC += 2; 
                PC += offset; 
                return 12; 
            }
            else {
                PC += 2; 
                return 8; 
            }
        }
        else if (endblock == 0x01){
            // 0x31 - LD SP, n16 | 3 12 | - - - -
            uint16_t nn = Memory::readByte(PC + 1) | (Memory::readByte(PC + 2) << 8); // Read n16
            SP = nn; 
            PC += 3; 
            return 12;
        }
        else if (endblock == 0x02){
            // 0x32 [HL-], A | 1 8 | - - - -
            Memory::writeByte(getHL(), A); // Write A to memory at address HL
            uint16_t hl = getHL();
            hl--; 
            H = (hl >> 8) & 0xFF; 
            L = hl & 0xFF; 
            PC += 1; 
            return 8;
        }
        else if (endblock == 0x03){
            // 0x33 - INC SP | 1 8 | - - - -
            SP++; // Increment Stack Pointer
            PC += 1; 
            return 8; 
        }
        else if (endblock == 0x04){
            // 0x34 - INC [HL] | 1 12 | Z 0 H -
            uint16_t hl = getHL();
            uint8_t value = Memory::readByte(hl); // Read value at address HL
            value++; // Increment value
            flags.Z = (value == 0); 
            flags.N = false; 
            flags.H = (value & 0x0F) == 0;
            Memory::writeByte(hl, value); 
            PC += 1;
            return 12; 
        }
        else if (endblock == 0x05){
            // 0x35 - DEC [HL] | 1 12 | Z 1 H -
            uint16_t hl = getHL();
            uint8_t value = Memory::readByte(hl); 
            value--; 
            flags.Z = (value == 0);
            flags.N = true;
            flags.H = (value & 0x0F) == 0x0F;
            Memory::writeByte(hl, value); 
            PC += 1;
            return 12;
        }
        else if (endblock == 0x06){
            // 0x36 - LD [HL], n8 | 2 12 | - - - -
            uint16_t hl = getHL();
            uint8_t n8 = Memory::readByte(PC + 1);
            Memory::writeByte(hl, n8); 
            PC += 2; 
            return 12;
        }
        else if (endblock == 0x07){
            // 0x37 - SCF | 1 4 | - 0 0 1 "Set Carry Flag"
            flags.C = true; // Set Carry flag
            flags.N = false; // Clear Subtract flag
            flags.H = false; // Clear Half Carry flag
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x38){
        if (endblock == 0x00){
            // 0x38 JR C,e8 | 2 12/8 | - - - -
            if (flags.C == true) {
                int8_t offset = Memory::readByte(PC + 1); 
                PC += 2; 
                PC += offset; 
                return 12;
            }
            else {
                PC += 2;
                return 8;
            }
        }
        else if (endblock == 0x01){
            // 0x39 - ADD HL,SP | 1 8 | - 0 H C
            uint16_t result, carry_per_bit = getHL() + SP; 
            flags.C = (carry_per_bit > 0xFFFF); // Set C flag if there was a carry, if problem here, maybe make uint32_t
            flags.N = false;
            flags.H = ((getHL() & 0x0FFF) + (SP & 0x0FFF)) > 0x0FFF; 
            result = getHL() + SP;
            H = (result >> 8) & 0xFF; 
            L = result & 0xFF; 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x02){
            // 0x3A - LD A,[HL-] | 1 8 | - - - -
            A = Memory::readByte(getHL());
            uint16_t hl = getHL();
            hl--; 
            H = (hl >> 8) & 0xFF; 
            L = hl & 0xFF; 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x03){
            // 0x3B - DEC SP | 1 8 | - - - -
            SP--;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x04){
            // 0x3C - INC A | 1 4 | Z 0 H -
            A++;
            flags.Z = (A == 0); 
            flags.N = false;
            flags.H = (A & 0x0F) == 0; 
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x3D - DEC A | 1 4 | Z 1 H -
            A--;
            flags.Z = (A == 0);
            flags.N = true;
            flags.H = (A & 0x0F) == 0x0F; 
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x3E - LD A,n8 | 2 8 | - - - -
            A = Memory::readByte(PC + 1); // Load immediate value into A
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x3F - CCF | 1 4 | - 0 0 C | Complement Carry Flag
            flags.C = !flags.C;
            flags.N = false; 
            flags.H = false; 
            PC += 1;
            return 4;
        }
    }
  }

  else if (block == 0x40){ // 0x01xxxxxx block | LOAD Registers Instructions
    if (subblock == 0x00){
        if (endblock == 0x00) {
            // 0x40 - LD B,B | 1 4 | - - - - //Some emulators interpret LD B,B as a breakpoint though its regularly interpreted as a no-op;
            B = B;
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x01) {
            // 0x41 - LD B,C | 1 4 | - - - -
            B = C; 
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02) {
            // 0x42 - LD B,D | 1 4 | - - - -
            B = D;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03) {
            // 0x43 - LD B,E | 1 4 | - - - -
            B = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04) {
            // 0x44 - LD B,H | 1 4 | - - - -
            B = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05) {
            // 0x45 - LD B,L | 1 4 | - - - -
            B = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06) {
            // 0x46 - LD B,[HL] | 1 8 | - - - -
            B = Memory::readByte(getHL());
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07) {
            // 0x47 - LD B,A | 1 4 | - - - -
            B = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x08){
        if (endblock == 0x00){
            // 0x48 - LD C,B | 1 4 | - - - -
            C = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x49 - LD C,C | 1 4 | - - - - 
            C = C; // No operation, C remains unchanged
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x4A - LD C,D | 1 4 | - - - -
            C = D;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x4B - LD C,E | 1 4 | - - - -
            C = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x4C - LD C,H | 1 4 | - - - -
            C = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x4D - LD C,L | 1 4 | - - - -
            C = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x4E - LD C,[HL] | 1 8 | - - - -
            C = Memory::readByte(getHL()); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x4F - LD C,A | 1 4 | - - - -
            C = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x10){
        if (endblock == 0x00){
            // 0x50 - LD D,B | 1 4 | - - - -
            D = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x51 - LD D,C | 1 4 | - - - -
            D = C;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x52 - LD D,D | 1 4 | - - - - Some emulators interpret LD D,D as a debug message though its regularly interpreted as a no-op;
            D = D; // No operation, D remains unchanged
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x53 - LD D,E | 1 4 | - - - -
            D = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x54 - LD D,H | 1 4 | - - - -
            D = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x55 - LD D,L | 1 4 | - - - -
            D = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x56 - LD D,[HL] | 1 8 | - - - -
            D = Memory::readByte(getHL()); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x57 - LD D,A | 1 4 | - - - -
            D = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x18){
        if (endblock == 0x00){
            // 0x58 - LD E,B | 1 4 | - - - -
            E = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x59 - LD E,C | 1 4 | - - - -
            E = C;
            PC += 1;
            return 4;
        }
        
        else if (endblock == 0x02){
            // 0x5A - LD E,D | 1 4 | - - - -
            E = D;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x5B - LD E,E | 1 4 | - - - - 
            E = E;
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x04){
            // 0x5C - LD E,H | 1 4 | - - - -
            E = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x5D - LD E,L | 1 4 | - - - -
            E = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x5E - LD E,[HL] | 1 8 | - - - -
            E = Memory::readByte(getHL());
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x5F - LD E,A | 1 4 | - - - -
            E = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x20){
        if (endblock == 0x00){
            // 0x60 - LD H,B | 1 4 | - - - -
            H = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x61 - LD H,C | 1 4 | - - - -
            H = C;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x62 - LD H,D | 1 4 | - - - -
            H = D;
            PC += 1;
            return 4;
        
        }
        else if (endblock == 0x03){
            // 0x63 - LD H,E | 1 4 | - - - -
            H = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x64 - LD H,H | 1 4 | - - - -
            H = H; // No operation
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x65 - LD H,L | 1 4 | - - - -
            H = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x66 - LD H,[HL] | 1 8 | - - - -
            uint16_t hl = getHL();
            H = Memory::readByte(hl); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x67 - LD H,A | 1 4 | - - - -
            H = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x28){
        if (endblock == 0x00){
            // 0x68 - LD L,B | 1 4 | - - - -
            L = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x69 - LD L,C | 1 4 | - - - -
            L = C;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x6A - LD L,D | 1 4 | - - - -
            L = D;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x6B - LD L,E | 1 4 | - - - -
            L = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x6C - LD L,H | 1 4 | - - - -
            L = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x6D - LD L,L | 1 4 | - - - -
            L = L; // No operation
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x6E - LD L,[HL] | 1 8 | - - - -
            uint16_t hl = getHL();
            L = Memory::readByte(hl); 
            PC += 1;
            return 8;            
        }
        else if (endblock == 0x07){
            // 0x6F - LD L,A | 1 4 | - - - -
            L = A;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x30){
        if (endblock == 0x00){
            // 0x70 - LD [HL],B | 1 8 | - - - -
            Memory::writeByte(getHL(), B); // Write B to memory at address HL
            PC += 1;
            return 8;
        }
        else if (endblock == 0x01){
            // 0x71 - LD [HL],C | 1 8 | - - - -
            Memory::writeByte(getHL(), C); // Write C to memory at address HL
            PC += 1;
            return 8;
        }
        else if (endblock == 0x02){
            // 0x72 - LD [HL],D | 1 8 | - - - -
            Memory::writeByte(getHL(), D); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x03){
            // 0x73 - LD [HL],E | 1 8 | - - - -
            Memory::writeByte(getHL(), E); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x04){
            // 0x74 - LD [HL],H | 1 8 | - - - -
            Memory::writeByte(getHL(), H);
            PC += 1;
            return 8;
        }
        else if (endblock == 0x05){
            // 0x75 - LD [HL],L | 1 8 | - - - -
            Memory::writeByte(getHL(), L);
            PC += 1;
            return 8;
        }
        else if (endblock == 0x06){
            // 0x76 - HALT | 1 4 | - - - -
            // "Halt system clock until an interrupt occurs"
            // The HALT instruction stops the CPU until an interrupt occurs.
            // This is a placeholder for the HALT instruction, which will be handled in the CPU
            // emulation loop.
            // In a real implementation, you would set a flag (IME flag) to indicate that the CPU is halted
            // and wait for an interrupt to resume execution.
            // For now, we will just return 4 T-states.
            PC += 1;
            return 4;
        }
        else if (endblock == 0x07){
            // 0x77 - LD [HL],A | 1 8 | - - - -
            Memory::writeByte(getHL(), A); // Write A to memory at address HL
            PC += 1;
            return 8;
        }
    }
    else if (subblock == 0x38){
        if (endblock == 0x00){
            // 0x78 - LD A,B | 1 4 | - - - -
            A = B;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x79 - LD A,C | 1 4 | - - - -
            A = C;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x7A - LD A,D | 1 4 | - - - -
            A = D;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x7B - LD A,E | 1 4 | - - - -
            A = E;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x7C - LD A,H | 1 4 | - - - -
            A = H;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x7D - LD A,L | 1 4 | - - - -
            A = L;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x7E - LD A,[HL] | 1 8 | - - - -
            A = Memory::readByte(getHL()); 
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x7F - LD A,A | 1 4 | - - - -
            A = A; // No operation
            PC += 1;
            return 4;
        }
    }
  }

  else if (block == 0x80){ // 0x10xxxxxx block
    if (subblock == 0x00){
        if (endblock == 0x00){
            // 0x80 - ADD A,B | 1 4 | Z 0 H C
            uint8_t result = A + B;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (B & 0x0F)) > 0x0F; // Set H flag if there was a half carry in the operation
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x81 - ADD A,C | 1 4 | Z 0 H C
            uint8_t result = A + C;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (C & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = 0;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x82 - ADD A,D | 1 4 | Z 0 H C
            uint8_t result = A + D;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (D & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = 0;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0x83 - ADD A,E | 1 4 | Z 0 H C
            uint8_t result = A + E;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (E & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = 0;
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x04){
            // 0x84 - ADD A,H | 1 4 | Z 0 H C
            uint8_t result = A + H;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (H & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x85 - ADD A,L | 1 4 | Z 0 H C
            uint8_t result = A + L;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (H & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4; 
        }
        else if (endblock == 0x06){
            // 0x86 - ADD A,[HL] | 1 8 | Z 0 H C
            uint8_t value = Memory::readByte(getHL());
            uint8_t result = A + value;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (value & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x87 - ADD A,A | 1 4 | Z 0 H C
            uint8_t result = A + A;
            flags.C = (result < A);
            flags.H = ((A & 0x0F) + (A & 0x0F)) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x08){
        if (endblock == 0x00){
            // 0x88 - ADC A,B | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + B + carry;
            flags.C = (result < A) || (carry && result == A); //hmm?  Maybe not a carry
            flags.H = ((A & 0x0F) + (B & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x89 - ADC A,C | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + C + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (C & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x8A - ADC A,D | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + D + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (D & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x03){
            // 0x8B - ADC A,E | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + E + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (E & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x04){
            // 0x8C - ADC A,H | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + H + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (H & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x8D - ADC A,L | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + L + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (L & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x06){
            // 0x8E - ADC A,[HL] | 1 8 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t value = Memory::readByte(getHL());
            uint8_t result = A + value + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (value & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 8;            
        }
        else if (endblock == 0x07){
            // 0x8F - ADC A,A | 1 4 | Z 0 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A + A + carry;
            flags.C = (result < A) || (carry && result == A);
            flags.H = ((A & 0x0F) + (A & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x10){
        if (endblock == 0x00){
            // 0x90 - SUB A,B | 1 4 | Z 1 H C
            uint8_t result = A - B;
            flags.C = (A < B);
            flags.H = (A & 0x0F) < (B & 0x0F); // Set H flag if there was a half borrow in the operation
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x91 - SUB A,C | 1 4 | Z 1 H C
            uint8_t result = A - C;
            flags.C = (A < C);
            flags.H = (A & 0x0F) < (C & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x92 - SUB A,D | 1 4 | Z 1 H C
            uint8_t result = A - D;
            flags.C = (A < D);
            flags.H = (A & 0x0F) < (D & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x03){
            // 0x93 - SUB A,E | 1 4 | Z 1 H C
            uint8_t result = A - E;
            flags.C = (A < E);
            flags.H = (A & 0x0F) < (E & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x04){
            // 0x94 - SUB A,H | 1 4 | Z 1 H C
            uint8_t result = A - H;
            flags.C = (A < H);
            flags.H = (A & 0x0F) < (H & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x05){
            // 0x95 - SUB A,L | 1 4 | Z 1 H C
            uint8_t result = A - L;
            flags.C = (A < L);
            flags.H = (A & 0x0F) < (L & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0x96 - SUB A,[HL] | 1 8 | Z 1 H C
            uint8_t value = Memory::readByte(getHL());
            uint8_t result = A - value;
            flags.C = (A < value);
            flags.H = (A & 0x0F) < (value & 0x0F);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 8; 
        }
        else if (endblock == 0x07){
            // 0x97 - SUB A,A | 1 4 | 1 1 0 0
            A -= A;
            flags.Z = true;
            flags.N = true;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x18){
        if (endblock == 0x00){
            // 0x98 - SBC A,B | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - B - carry;
            flags.C = (A < (B + carry));
            flags.H = (A & 0x0F) < ((B & 0x0F) + carry);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0x99 - SBC A,C | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - C - carry;
            flags.C = (A < (C + carry));
            flags.H = (A & 0x0F) + ((C & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0x9A - SBC A,D | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - D - carry;
            flags.C = (A < (D + carry));
            flags.H = (A & 0x0F) + ((D & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x03){
            // 0x9B - SBC A,E | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - E - carry;
            flags.C = (A < (E + carry));
            flags.H = (A & 0x0F) + ((E & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0x9C - SBC A,H | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - H - carry;
            flags.C = (A < (H + carry));
            flags.H = (A & 0x0F) + ((H & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0x9D - SBC A,L | 1 4 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - L - carry;
            flags.C = (A < (L + carry));
            flags.H = (A & 0x0F) + ((L & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;            
        }
        else if (endblock == 0x06){
            // 0x9E - SBC A,[HL] | 1 8 | Z 1 H C
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t value = Memory::readByte(getHL());
            uint8_t result = A - value - carry;
            flags.C = (A < (value + carry));
            flags.H = (A & 0x0F) + ((value & 0x0F) + carry) > 0x0F;
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0x9F - SBC A,A | 1 4 | Z 1 H -
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - A - carry;
            flags.H = (carry != 0);
            A = result;
            flags.Z = (A == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x20){
        if (endblock == 0x00){
            // 0xA0 - AND A,B | 1 4 | Z 0 1 0
            A = A & B;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0xA1 - AND A,C | 1 4 | Z 0 1 0
            A = A & C;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0xA2 - AND A,D | 1 4 | Z 0 1 0
            A = A & D;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0xA3 - AND A,E | 1 4 | Z 0 1 0
            A = A & E;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xA4 - AND A,H | 1 4 | Z 0 1 0
            A = A & H;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0xA5 - AND A,L | 1 4 | Z 0 1 0
            A = A & L;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0xA6 - AND A,[HL] | 1 8 | Z 0 1 0
            uint8_t value = Memory::readByte(getHL());
            A = A & value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xA7 - AND A,A | 1 4 | Z 0 1 0
            A = A & A; // No operation
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x28){
        if (endblock == 0x00){
            // 0xA8 - XOR A,B | 1 4 | Z 0 0 0
            A = A ^ B;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0xA9 - XOR A,C | 1 4 | Z 0 0 0
            A = A ^ C;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0xAA - XOR A,D | 1 4 | Z 0 0 0
            A = A ^ D;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0xAB - XOR A,E | 1 4 | Z 0 0 0
            A = A ^ E;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xAC - XOR A, H | 1 4 | Z 0 0 0
            A = A ^ H;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0xAD - XOR A,L | 1 4 | Z 0 0 0
            A = A ^ L;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0xAE - XOR A,[HL] | 1 8 | Z 0 0 0
            uint8_t value = Memory::readByte(getHL());
            A = A ^ value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xAF - XOR A,A |1 4 | 1 0 0 0
            A = A ^ A; // No operation
            flags.Z = true;
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x30){
        if (endblock == 0x00){
            // 0xB0 - OR A,B | 1 4 | Z 0 0 0
            A = A | B;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0xB1 - OR A,C | 1 4 | Z 0 0 0
            A = A | C;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0xB2 - OR A,D | 1 4 | Z 0 0 0
            A = A | D;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0xB3 - OR A,E | 1 4 | Z 0 0 0
            A = A | E;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xB4 - OR A,H | 1 4 | Z 0 0 0
            A = A | H;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0xB5 - OR A,L | 1 4 | Z 0 0 0
            A = A | L;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0xB6 - OR A,[HL] | 1 8 | Z 0 0 0
            uint8_t value = Memory::readByte(getHL());
            A = A | value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xB7 - OR A,A | 1 4 | Z 0 0 0
            A = A | A; // No operation
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
    }
    else if (subblock == 0x38){
        if (endblock == 0x00){
            // 0xB8 - CP A,B | 1 4 | Z 1 H C
            uint8_t result = A - B;
            flags.C = (A < B);
            flags.H = (A & 0x0F) < (B & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x01){
            // 0xB9 - CP A,C | 1 4 | Z 1 H C
            uint8_t result = A - C;
            flags.C = (A < C);
            flags.H = (A & 0x0F) < (C & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x02){
            // 0xBA - CP A,D | 1 4 | Z 1 H C
            uint8_t result = A - D;
            flags.C = (A < D);
            flags.H = (A & 0x0F) < (D & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x03){
            // 0xBB - CP A,E | 1 4 | Z 1 H C
            uint8_t result = A - E;
            flags.C = (A < E);
            flags.H = (A & 0x0F) < (E & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xBC - CP A,H | 1 4 | Z 1 H C
            uint8_t result = A - H;
            flags.C = (A < H);
            flags.H = (A & 0x0F) < (H & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x05){
            // 0xBD - CP A,L | 1 4 | Z 1 H C
            uint8_t result = A - L;
            flags.C = (A < L);
            flags.H = (A & 0x0F) < (L & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 4;
        }
        else if (endblock == 0x06){
            // 0xBE - CP A,[HL] | 1 8 | Z 1 H C
            uint8_t value = Memory::readByte(getHL());
            uint8_t result = A - value;
            flags.C = (A < value);
            flags.H = (A & 0x0F) < (value & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 1;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xBF - CP A,A | 1 4 | 1 1 0 0
            A - A; //no op
            flags.Z = true;
            flags.N = true;
            flags.H = false;
            flags.C = false;
            PC += 1;
            return 4;
        }
    }
  }

  else if (block == 0xC0){ // 0x11xxxxxx block
    if (subblock == 0x00){
        if (endblock == 0x00){
            // 0xC0 - RET NZ | 1 20/8 | - - - -
            if (flags.Z == false){
                uint8_t low = Memory::readByte(SP);
                SP += 1;
                uint8_t high = Memory::readByte(SP);
                SP += 1;
                PC = (high << 8) | low;
                return 20;
            }
            else{
                PC += 1;
                return 8;
            }
        }
        else if (endblock == 0x01){
            // 0xC1 - POP BC | 1 12 | - - - -
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            B = high;
            C = low;
            PC += 1;
            return 12;
        }
        else if (endblock == 0x02){
            // 0xC2 - JP NZ, a16 | 3 16/12 | - - - -
            if (flags.Z == false){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                PC = address;
                return 16;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x03){
            // 0xC3 - JP a16 | 3 16 | - - - -
            uint8_t low = Memory::readByte(PC + 1);
            uint8_t high = Memory::readByte(PC + 2);
            uint16_t address = (high << 8) | low;
            PC = address;
            return 16;            
        }
        else if (endblock == 0x04){
            // 0xC4 - CALL NZ, a16 | 3 24/12 | - - - -
            if (flags.Z == false){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                SP -= 1;
                Memory::writeByte(SP, PC + 3 >> 8); //PC is 16 bit, so push high byte first
                SP -= 1;
                Memory::writeByte(SP, PC + 3 & 0xFF); //then push low byte, push return address onto stack
                PC = address;
                return 24;
            }
            else{
                PC += 3;
                return 12;
            }            
        }
        else if (endblock == 0x05){
            // 0xC5 - PUSH BC | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, B); // Push high byte first
            SP -= 1;
            Memory::writeByte(SP, C); // Then push low byte
            PC += 1;
            return 16;            
        }
        else if (endblock == 0x06 ){
            // 0xC6 - ADD A,n8 | 2 8 | Z 0 H C
            uint8_t value = Memadsffdory::readByte(PC + 1);
            A += value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = ((A & 0x0F) + (value & 0x0F)) > 0x0F;
            flags.C = (A < value);
            PC += 2;
            return 8;            
        }
        else if (endblock == 0x07){
            // 0xC7 - RST $00 | 1 16 | - - - -
            uint8_t n = 0x00;
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); // Push high byte first, not the same address as PC as it would loop
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); // Then push low byte
            PC = n;
            return 16;
        }   
    }
    else if (subblock == 0x08){
        if (endblock == 0x00){
            // 0xC8 - RET Z | 1 20/8 | - - - -
            if (flags.Z == true){ //return from subroutine if Z flag is set
                uint8_t low = Memory::readByte(SP);
                SP += 1;
                uint8_t high = Memory::readByte(SP);
                SP += 1;
                PC = (high << 8) | low;
                return 20;                
            }
            else{
                PC += 1;
                return 8;
            }            
        }
        else if (endblock == 0x01){
            // 0xC9 - RET | 1 16 | - - - -
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            PC = (high << 8) | low;
            return 16;
        }
        else if (endblock == 0x02){
            // 0xCA - JP Z, a16 | 3 16/12 | - - - -
            if (flags.Z == true){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                PC = address;
                return 16;
            }
            else{
                PC += 3;
                return 12;
            } 
        }
        else if (endblock == 0x03){
            // 0xCB - PREFIX CB | 1 4 | - - - -
            PC += 1;
            return (executeCB()); // CB prefixed opcodes take a total of 2 bytes and 8 cycles total (I think)
        }
        else if (endblock == 0x04){
            // 0xCC - CALL Z, a16 | 3 24/12 | - - - -
            if (flags.Z == true) {
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) >> 8); 
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) & 0xFF); 
                PC = address;
                return 24;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x05){
            // 0xCD - CALL a16 | 3 24 | - - - -
            uint8_t low = Memory::readByte(PC + 1);
            uint8_t high = Memory::readByte(PC + 2);
            uint16_t address = (high << 8) | low;
            SP -= 1;
            Memory::writeByte(SP, (PC + 3) >> 8);
            SP -= 1;
            Memory::writeByte(SP, (PC + 3) & 0xFF);
            PC = address;
            return 24;
        }
        else if (endblock == 0x06){
            // 0xCE - ADC A,n8 | 2 8 | Z 0 H C
            uint8_t value = Memory::readByte(PC + 1);
            uint8_t carry = flags.C ? 1 : 0;
            uint16_t result = A + value + carry;
            flags.Z = ((result & 0xFF) == 0);
            flags.N = false;
            flags.H = ((A & 0x0F) + (value & 0x0F) + carry) > 0x0F;
            flags.C = (result < A) || (carry && result == A);  // I am unsure about the second bit of logic here
            A = result & 0xFF;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xCF - RST $08 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); //
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); //
            PC = 0x08;
            return 16;
        }
    }
    else if (subblock == 0x10){
        if (endblock == 0x00){
            // 0xD0 - RET NC | 1 20/8 | - - - -
            if (flags.C == false){
                uint8_t low = Memory::readByte(SP);
                SP += 1;
                uint8_t high = Memory::readByte(SP);
                SP += 1;
                PC = (high << 8) | low;
                return 20;
            }
            else{
                PC += 1;
                return 8;
            }
        }
        else if (endblock == 0x01){
            // 0xD1 - POP DE | 1 12 | - - - -
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            D = high;
            E = low;
            PC += 1;
            return 12;
        }
        else if (endblock == 0x02){
            // 0xD2 - JP NC, a16 | 3 16/12 | - - - -
            if (flags.C == false){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                PC = address;
                return 16;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x03){
            // 0xD3 - INVALID | - - | - - - -
            return -1; // Invalid opcode
        }
        else if (endblock == 0x04){
            // 0xD4 - CALL NC, a16 | 3 24/12 | - - - -
            if (flags.C == false){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) >> 8); 
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) & 0xFF); 
                PC = address;
                return 24;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x05){
            // 0xD5 - PUSH DE | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, D); // Push high byte first
            SP -= 1;
            Memory::writeByte(SP, E); // Then push low byte
            PC += 1;
            return 16;
        }
        else if (endblock == 0x06){
            // 0xD6 - SUB A,n8 | 2 8 | Z 1 H C
            uint8_t value = Memory::readByte(PC + 1);
            uint8_t result = A - value;
            flags.Z = (result == 0);
            flags.N = true;
            flags.H = (A & 0x0F) < (value & 0x0F);
            flags.C = (A < value);
            A = result;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xD7 - RST $10 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF);
            PC = 0x10;
            return 16;
        }
    }
    else if (subblock == 0x18){
        if (endblock == 0x00){
            // 0xD8 - RET C | 1 20/8 | - - - -
            if (flags.C == true){
                uint8_t low = Memory::readByte(SP);
                SP += 1;
                uint8_t high = Memory::readByte(SP);
                SP += 1;
                PC = (high << 8) | low;
                return 20;
            }
            else{
                PC += 1;
                return 8;
            }
        }
        else if (endblock == 0x01){
            // 0xD9 - RETI | 1 16 | - - - -
            // Return from interrupt controller
            // Also enables interrupts by setting the IME flag to true
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            PC = (high << 8) | low;
            IMEEnable();
            return 16;            
        }
        else if (endblock == 0x02){
            // 0xDA - JP C, a16 | 3 16/12 | - - - -
            if (flags.C == true){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                PC = address;
                return 16;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x03){
            // 0xDB - INVALID | - - | - - - -
            return -1; // Invalid opcode
        }
        else if (endblock == 0x04){
            // 0xDC - CALL C, a16 | 3 24/12 | - - - -
            if (flags.C == true){
                uint8_t low = Memory::readByte(PC + 1);
                uint8_t high = Memory::readByte(PC + 2);
                uint16_t address = (high << 8) | low;
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) >> 8); 
                SP -= 1;
                Memory::writeByte(SP, (PC + 3) & 0xFF); 
                PC = address;
                return 24;
            }
            else{
                PC += 3;
                return 12;
            }
        }
        else if (endblock == 0x05){
            // 0xDD - INVALID | - - | - - - -
            return -1; // Invalid opcode
        }
        else if (endblock == 0x06){
            // 0xDE - SBC A,n8 | 2 8 | Z 1 H C
            uint8_t value = Memory::readByte(PC + 1);
            uint8_t carry = flags.C ? 1 : 0;
            uint8_t result = A - value - carry;
            flags.Z = (result == 0);
            flags.N = true;
            flags.H = (A & 0x0F) + ((value & 0x0F) + carry) > 0x0F;
            flags.C = (A < result) || (carry && A == result); // I am unsure about the second bit of logic here
            A = result;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xDF - RST $18 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF);
            PC = 0x18;
            return 16;
        }
    }
    else if (subblock == 0x20){
        if (endblock == 0x00){
            // 0xE0 - LDH [a8], A | 2 12 | - - - -
            uint8_t littlebyte = Memory::readByte(PC + 1);
            Memory::writeByte(0xFF00 + littlebyte, A);
            PC += 2;
            return 12;
        }
        else if (endblock == 0x01){
            // 0xE1 - POP HL | 1 12 | - - - -
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            H = high;
            L = low;
            PC += 1;
            return 12;

        }
        else if (endblock == 0x02){
            // 0xE2 - LDH [C], A | 1 8 | - - - -
            Memory::writeByte(0xFF00 & C , A);
            PC += 1;
            return 8;
        }
        else if (endblock == 0x03){
            // 0xE3 - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x04){
            // 0xE4 -Invalid Instruction
            return -1
        }
        else if (endblock == 0x05){
            // 0xE5 - PUSH HL | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, H); 
            SP -= 1;
            Memory::writeByte(SP, L); 
            PC += 1;
            return 16;
        }
        else if (endblock == 0x06){
            // 0xE6 - AND A,n8 | 2 8 | Z 0 1 0
            uint8_t value = Memory::readByte(PC + 1);
            A = A & value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = true;
            flags.C = false;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xE7 - RST $20 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); 
            PC = 0x20;
            return 16;
        }
    }
    else if (subblock == 0x28){
        if (endblock == 0x00){
            // 0xE8 - ADD SP, r8 | 2 16 | 0 0 H C
            int8_t value = static_cast<int8_t>(Memory::readByte(PC + 1)); 
            flags.Z = false;
            flags.N = false;
            flags.H = (SP & 0x0F) + (value & 0x0F) > 0x0F;
            flags.C = (SP & 0xFF) + (value & 0xFF) > 0xFF;
            SP += value;
            PC += 2;
            return 16;
        }
        else if (endblock == 0x01){
            // 0xE9 - JP HL | 1 4 | - - - -
            PC = getHL();
            return 4;
        }
        else if (endblock == 0x02){
            // 0xEA - LD [a16], A | 3 16 | - - - -
            uint8_t low = Memory::readByte(PC + 1);
            uint8_t high = Memory::readByte(PC + 2);
            uint16_t address = (high << 8) | low;
            Memory::writeByte(address, A);
            PC += 3;
            return 16;
        }
        else if (endblock == 0x03){
            // 0xEB - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x04){
            // 0xEC - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x05){
            // 0xED - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x06){
            // 0xEE - XOR A,n8 | 2 8 | Z 0 0 0
            uint8_t value = Memory::readByte(PC + 1);
            A = A ^ value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xEF - RST $28 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); 
            PC = 0x28;
            return 16;
        }
    }
    else if (subblock == 0x30){
        if (endblock == 0x00){
            // 0xF0 - LDH A, [a8] | 2 12 | - - - -
            uint8_t littlebyte = Memory::readByte(PC + 1);
            A = Memory::readByte(0xFF00 + littlebyte);
            PC += 2;
            return 12;
        }
        else if (endblock == 0x01){
            // 0xF1 - POP AF | 1 12 | - - - -
            uint8_t low = Memory::readByte(SP);
            SP += 1;
            uint8_t high = Memory::readByte(SP);
            SP += 1;
            A = high;
            F = low & 0xF0; // Lower nibble of F is always 0
            PC += 1;
            return 12;
        }
        else if (endblock == 0x02){
            // 0xF2 - LDH A, [C] | 1 8 | - - - -
            A = Memory::readByte(0xFF00 + C);
            PC += 1;
            return 8;
        }
        else if (endblock == 0x03){
            // 0xF3 - DI | 1 4 | - - - -
            // "interrupt checking is suppressed so fetch_cycle() is not used"
            // was I supposed to check for interrupts then increase PC?
            IMEDisable();
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xF4 - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x05){
            // 0xF5 - PUSH AF | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, A); 
            SP -= 1;
            Memory::writeByte(SP, F & 0xF0); // Lower nibble of F is always 0
            PC += 1;
            return 16;
        }
        else if (endblock == 0x06){
            // 0xF6 - OR A,n8 | 2 8 | Z 0 0 0
            uint8_t value = Memory::readByte(PC + 1);
            A = A | value;
            flags.Z = (A == 0);
            flags.N = false;
            flags.H = false;
            flags.C = false;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xF7 - RST $30 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); 
            PC = 0x30;
            return 16;
        }
    }
    else if (subblock == 0x38){
        if (endblock == 0x00){
            // 0xF8 - LD HL, SP+r8 | 2 12 | 0 0 H C
            int8_t value = static_cast<int8_t>(Memory::readByte(PC + 1)); 
            uint16_t result = SP + value;
            flags.Z = false;
            flags.N = false;
            flags.H = (SP & 0x0F) + (value & 0x0F) > 0x0F;
            flags.C = (SP & 0xFF) + (value & 0xFF) > 0xFF;
            H = (result >> 8) & 0xFF;
            L = result & 0xFF;
            PC += 2;
            return 12;
        }
        else if (endblock == 0x01){
            // 0xF9 - LD SP, HL | 1 8 | - - - -
            SP = getHL();
            PC += 1;
            return 8;
        }
        else if (endblock == 0x02){
            // 0xFA - LD A, [a16] | 3 16 | - - - -
            uint8_t low = Memory::readByte(PC + 1);
            uint8_t high = Memory::readByte(PC + 2);
            uint16_t address = (high << 8) | low;
            A = Memory::readByte(address);
            PC += 3;
            return 16;
        }
        else if (endblock == 0x03){
            // 0xFB - EI | 1 4 | - - - -
            IMEEnable();
            PC += 1;
            return 4;
        }
        else if (endblock == 0x04){
            // 0xFC - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x05){
            // 0xFD - Invalid Instruction
            return -1;
        }
        else if (endblock == 0x06){
            // 0xFE - CP A,n8 | 2 8 | Z 1 H C
            uint8_t value = Memory::readByte(PC + 1);
            uint8_t result = A - value;
            flags.C = (A < value);
            flags.H = (A & 0x0F) < (value & 0x0F); 
            flags.Z = (result == 0);
            flags.N = true;
            PC += 2;
            return 8;
        }
        else if (endblock == 0x07){
            // 0xFF - RST $38 | 1 16 | - - - -
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) >> 8); 
            SP -= 1;
            Memory::writeByte(SP, (PC + 1) & 0xFF); 
            PC = 0x38;
            return 16;
        }
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

void SM83::IMEEnable(){
    IME = true;
}

void SM83::IMEDisable(){
    IME = false;
}