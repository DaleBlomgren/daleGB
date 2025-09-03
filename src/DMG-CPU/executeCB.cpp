#include "executeCB.h"
#include "SM83.h"

namespace CBInstructions {

int executeCB() {
    uint8_t opcode = (PC >> 8) & 0xFF;
    uint8_t block = opcode & 0xC0;
    uint8_t subblock = opcode & 0x38;
    uint8_t endblock = opcode & 0x07;

    if (block == 0x00){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x00 RLC B | 2 8 | Z 0 0 C
                uint8_t result = (B << 1) | (B >> 7);
                flags.C = (B >> 7) & 0x01;
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;                
            }
            else if (endblock == 0x01){
                // 0xCB 0x01 RLC C | 2 8 | Z 0 0 C
                uint8_t result = (C << 1) | (C >> 7);
                flags.C = (C >> 7) & 0x01;
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x02 RLC D | 2 8 | Z 0 0 C
                uint8_t result = (D << 1) | (D >> 7);
                flags.C = (D >> 7) & 0x01;
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;                
            }
            else if (endblock == 0x03){
                // 0xCB 0x03 RLC E | 2 8 | Z 0 0 C
                uint8_t result = (E << 1) | (E >> 7);
                flags.C = (E >> 7) & 0x01;
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;                
            }
            else if (endblock == 0x04){
                // 0xCB 0x04 RLC H | 2 8 | Z 0 0 C
                uint8_t result = (H << 1) | (H >> 7);
                flags.C = (H >> 7) & 0x01;
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x05 RLC L | 2 8 | Z 0 0 C
                uint8_t result = (L << 1) | (L >> 7);
                flags.C = (L >> 7) & 0x01;
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x06 RLC [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t result = (value << 1) | (value >> 7);
                flags.C = (value >> 7) & 0x01;
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;                
            }
            else if (endblock == 0x07){
                // 0xCB 0x07 RLC A | 2 8 | Z 0 0 C
                uint8_t result = (A << 1) | (A >> 7);
                flags.C = (A >> 7) & 0x01;
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;                
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                //  0xCB 0x08 RRC B | 2 8 | Z 0 0 C
                uint8_t result = (B >> 1) | (B << 7);
                flags.C = B & 0x01;
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x09 RRC C | 2 8 | Z 0 0 C
                uint8_t result = (C >> 1) | (C << 7);
                flags.C = C & 0x01;
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x0A RRC D | 2 8 | Z 0 0 C
                uint8_t result = (D >> 1) | (D << 7);
                flags.C = D & 0x01;
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x0B RRC E | 2 8 | Z 0 0 C
                uint8_t result = (E >> 1) | (E << 7);
                flags.C = E & 0x01;
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;                
            }
            else if (endblock == 0x04){
                // 0xCB 0x0C RRC H | 2 8 | Z 0 0 C
                uint8_t result = (H >> 1) | (H << 7);
                flags.C = H & 0x01;
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;                                
            }
            else if (endblock == 0x05){
                // 0xCB 0x0D RRC L | 2 8 | Z 0 0 C
                uint8_t result = (L >> 1) | (L << 7);
                flags.C = L & 0x01;
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;                                                
            }
            else if (endblock == 0x06){
                // 0xCB 0x0E RRC [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t result = (value >> 1) | (value << 7);
                flags.C = value & 0x01;
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x0F RRC A | 2 8 | Z 0 0 C
                uint8_t result = (A >> 1) | (A << 7);
                flags.C = A & 0x01;
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x10 RL B | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (B << 1) | carry;
                flags.C = (B >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x11 RL C | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (C << 1) | carry;
                flags.C = (C >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x12 RL D | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (D << 1) | carry;
                flags.C = (D >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x13 RL E | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (E << 1) | carry;
                flags.C = (E >> 7) & 0x01; 
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x14 RL H | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (H << 1) | carry;
                flags.C = (H >> 7) & 0x01; 
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;                
            }
            else if (endblock == 0x05){
                // 0xCB 0x15 RL L | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (L << 1) | carry;
                flags.C = (L >> 7) & 0x01; 
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x16 RL [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (value << 1) | carry;
                flags.C = (value >> 7) & 0x01; 
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x17 RL A | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (A << 1) | carry;
                flags.C = (A >> 7) & 0x01; 
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;   
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x18 RR B | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (B >> 1) | (carry << 7);
                flags.C = B & 0x01; 
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x19 RR C | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (C >> 1) | (carry << 7);
                flags.C = C & 0x01; 
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x1A RR D | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (D >> 1) | (carry << 7);
                flags.C = D & 0x01; 
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x1B RR E | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (E >> 1) | (carry << 7);
                flags.C = E & 0x01; 
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x1C RR H | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (H >> 1) | (carry << 7);
                flags.C = H & 0x01; 
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x1D RR L | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (L >> 1) | (carry << 7);
                flags.C = L & 0x01; 
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x1E RR [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (value >> 1) | (carry << 7);
                flags.C = value & 0x01; 
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x1F RR A | 2 8 | Z 0 0 C
                uint8_t carry = flags.C ? 1 : 0;
                uint8_t result = (A >> 1) | (carry << 7);
                flags.C = A & 0x01; 
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0x20 SLA B | 2 8 | Z 0 0 C
                uint8_t result = (B << 1);
                flags.C = (B >> 7) & 0x01;
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x21 SLA C | 2 8 | Z 0 0 C
                uint8_t result = (C << 1);
                flags.C = (C >> 7) & 0x01;
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x22 SLA D | 2 8 | Z 0 0 C
                uint8_t result = (D << 1);
                flags.C = (D >> 7) & 0x01;
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x23 SLA E | 2 8 | Z 0 0 C
                uint8_t result = (E << 1);
                flags.C = (E >> 7) & 0x01;
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x24 SLA H | 2 8 | Z 0 0 C
                uint8_t result = (H << 1);
                flags.C = (H >> 7) & 0x01;
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x25 SLA L | 2 8 | Z 0 0 C
                uint8_t result = (L << 1);
                flags.C = (L >> 7) & 0x01;
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x26 SLA [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t result = (value << 1);
                flags.C = (value >> 7) & 0x01;
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x27 SLA A | 2 8 | Z 0 0 C
                uint8_t result = (A << 1);
                flags.C = (A >> 7) & 0x01;
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0x28 SRA B | 2 8 | Z 0 0 C
                uint8_t result = (B >> 1) | (B & 0x80);
                flags.C = B & 0x01;
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x29 SRA C | 2 8 | Z 0 0 C
                uint8_t result = (C >> 1) | (C & 0x80);
                flags.C = C & 0x01;
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x2A SRA D | 2 8 | Z 0 0 C
                uint8_t result = (D >> 1) | (D & 0x80);
                flags.C = D & 0x01;
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x2B SRA E | 2 8 | Z 0 0 C
                uint8_t result = (E >> 1) | (E & 0x80);
                flags.C = E & 0x01;
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x2C SRA H | 2 8 | Z 0 0 C
                uint8_t result = (H >> 1) | (H & 0x80);
                flags.C = H & 0x01;
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x2D SRA L | 2 8 | Z 0 0 C
                uint8_t result = (L >> 1) | (L & 0x80);
                flags.C = L & 0x01;
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x2E SRA [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t result = (value >> 1) | (value & 0x80);
                flags.C = value & 0x01;
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x2F SRA A | 2 8 | Z 0 0 C
                uint8_t result = (A >> 1) | (A & 0x80);
                flags.C = A & 0x01;
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0x30 SWAP B | 2 8 | Z 0 0 0
                uint8_t result = (B << 4) | (B >> 4);
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x31 SWAP C | 2 8 | Z 0 0 0
                uint8_t result = (C << 4) | (C >> 4);
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x32 SWAP D | 2 8 | Z 0 0 0
                uint8_t result = (D << 4) | (D >> 4);
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x33 SWAP E | 2 8 | Z 0 0 0
                uint8_t result = (E << 4) | (E >> 4);
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x34 SWAP H | 2 8 | Z 0 0 0
                uint8_t result = (H << 4) | (H >> 4);
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x35 SWAP L | 2 8 | Z 0 0 0
                uint8_t result = (L << 4) | (L >> 4);
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x36 SWAP [HL] | 2 16 | Z 0 0 0
                uint8_t value = readByte(getHL());
                uint8_t result = (value << 4) | (value >> 4);
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x37 SWAP A | 2 8 | Z 0 0 0
                uint8_t result = (A << 4) | (A >> 4);
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;
                flags.C = false;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0x38 SRL B | 2 8 | Z 0 0 C
                uint8_t result = (B >> 1);
                flags.C = B & 0x01;
                B = result;
                flags.Z = (B == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x39 SRL C | 2 8 | Z 0 0 C
                uint8_t result = (C >> 1);
                flags.C = C & 0x01;
                C = result;
                flags.Z = (C == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x3A SRL D | 2 8 | Z 0 0 C
                uint8_t result = (D >> 1);
                flags.C = D & 0x01;
                D = result;
                flags.Z = (D == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x3B SRL E | 2 8 | Z 0 0 C
                uint8_t result = (E >> 1);
                flags.C = E & 0x01;
                E = result;
                flags.Z = (E == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x3C SRL H | 2 8 | Z 0 0 C
                uint8_t result = (H >> 1);
                flags.C = H & 0x01;
                H = result;
                flags.Z = (H == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x3D SRL L | 2 8 | Z 0 0 C
                uint8_t result = (L >> 1);
                flags.C = L & 0x01;
                L = result;
                flags.Z = (L == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x3E SRL [HL] | 2 16 | Z 0 0 C
                uint8_t value = readByte(getHL());
                uint8_t result = (value >> 1);
                flags.C = value & 0x01;
                writeByte(getHL(), result);
                flags.Z = (result == 0);
                flags.N = false;
                flags.H = false;
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x3F SRL A | 2 8 | Z 0 0 C
                uint8_t result = (A >> 1);
                flags.C = A & 0x01;
                A = result;
                flags.Z = (A == 0);
                flags.N = false;
                flags.H = false;    
                PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0x40){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x40 BIT 0 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x41 BIT 0 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x42 BIT 0 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x43 BIT 0 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x44 BIT 0 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x45 BIT 0 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x46 BIT 0 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x47 BIT 0 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x01);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0x48 BIT 1 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x49 BIT 1 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x4A BIT 1 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x4B BIT 1 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x4C BIT 1 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x4D BIT 1 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x4E BIT 1 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x4F BIT 1 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x02);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x50 BIT 2 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x51 BIT 2 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x52 BIT 2 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x53 BIT 2 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x54 BIT 2 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x55 BIT 2 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x56 BIT 2 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x57 BIT 2 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x04);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x58 BIT 3 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x59 BIT 3 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x5A BIT 3 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x5B BIT 3 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x5C BIT 3 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x5D BIT 3 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x5E BIT 3 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x5F BIT 3 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x08);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0x60 BIT 4 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x61 BIT 4 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x62 BIT 4 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x63 BIT 4 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x64 BIT 4 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x65 BIT 4 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x66 BIT 4 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x67 BIT 4 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x10);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0x68 BIT 5 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x69 BIT 5 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x6A BIT 5 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x6B BIT 5 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x6C BIT 5 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x6D BIT 5 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x6E BIT 5 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x6F BIT 5 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x20);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0x70 BIT 6 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x71 BIT 6 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x72 BIT 6 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x73 BIT 6 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x74 BIT 6 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x75 BIT 6 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x76 BIT 6 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x77 BIT 6 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x40);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0x78 BIT 7 B | 2 8 | Z 0 1 -
                flags.Z = !(B & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x79 BIT 7 C | 2 8 | Z 0 1 -
                flags.Z = !(C & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x7A BIT 7 D | 2 8 | Z 0 1 -
                flags.Z = !(D & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x7B BIT 7 E | 2 8 | Z 0 1 -
                flags.Z = !(E & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x7C BIT 7 H | 2 8 | Z 0 1 -
                flags.Z = !(H & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x7D BIT 7 L | 2 8 | Z 0 1 -
                flags.Z = !(L & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x7E BIT 7 [HL] | 2 12 | Z 0 1 -
                uint8_t value = readByte(getHL());
                flags.Z = !(value & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x7F BIT 7 A | 2 8 | Z 0 1 -
                flags.Z = !(A & 0x80);
                flags.N = false;
                flags.H = true;
                PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0x80){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x80 RES 0 B | 2 8 | - - - - Reset bit 0 of B
                B &= ~(1 << 0); // bitwise AND of (11111110) created from 1 << 0 (00000001)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x81 RES 0 C | 2 8 | - - - -
                C &= 0xFE;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x82 RES 0 D | 2 8 | - - - -
                D &= 0xFE;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x83 RES 0 E | 2 8 | - - - -
                E &= 0xFE;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x84 RES 0 H | 2 8 | - - - -
                H &= 0xFE;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x85 RES 0 L | 2 8 | - - - -
                L &= 0xFE;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x86 RES 0 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xFE;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x87 RES 0 A | 2 8 | - - - -
                A &= 0xFE;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0x88 RES 1 B | 2 8 | - - - - Reset bit 1 of B
                B &= ~(1 << 1); // bitwise AND of (11111101)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x89 RES 1 C | 2 8 | - - - -
                C &= 0xFD;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x8A RES 1 D | 2 8 | - - - -
                D &= 0xFD;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x8B RES 1 E | 2 8 | - - - -
                E &= 0xFD;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x8C RES 1 H | 2 8 | - - - -
                H &= 0xFD;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x8D RES 1 L | 2 8 | - - - -
                L &= 0xFD;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x8E RES 1 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xFD;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x8F RES 1 A | 2 8 | - - - -
                A &= 0xFD;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x90 RES 2 B | 2 8 | - - - - 
                B &= ~(1 << 2); // bitwise AND of (11111011)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x91 RES 2 C | 2 8 | - - - -
                C &= 0xFB;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x92 RES 2 D | 2 8 | - - - -
                D &= 0xFB;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x93 RES 2 E | 2 8 | - - - -
                E &= 0xFB;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x94 RES 2 H | 2 8 | - - - -
                H &= 0xFB;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x95 RES 2 L | 2 8 | - - - -
                L &= 0xFB;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x96 RES 2 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xFB;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x97 RES 2 A | 2 8 | - - - -
                A &= 0xFB;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x98 RES 3 B | 2 8 | - - - - 
                B &= ~(1 << 3); // bitwise AND of (11110111)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x99 RES 3 C | 2 8 | - - - -
                C &= 0xF7;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x9A RES 3 D | 2 8 | - - - -
                D &= 0xF7;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x9B RES 3 E | 2 8 | - - - -
                E &= 0xF7;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x9C RES 3 H | 2 8 | - - - -
                H &= 0xF7;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x9D RES 3 L | 2 8 | - - - -
                L &= 0xF7;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x9E RES 3 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xF7;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x9F RES 3 A | 2 8 | - - - -
                A &= 0xF7;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0xA0 RES 4 B | 2 8 | - - - -
                B &= ~(1 << 4); // bitwise AND of (11101111)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xA1 RES 4 C | 2 8 | - - - -
                C &= 0xEF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xA2 RES 4 D | 2 8 | - - - -
                D &= 0xEF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xA3 RES 4 E | 2 8 | - - - -
                E &= 0xEF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xA4 RES 4 H | 2 8 | - - - -
                H &= 0xEF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xA5 RES 4 L | 2 8 | - - - -
                L &= 0xEF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xA6 RES 4 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xEF;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xA7 RES 4 A | 2 8 | - - - -
                A &= 0xEF;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0xA8 RES 5 B | 2 8 | - - - -
                B &= ~(1 << 5); // bitwise AND of (11011111)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xA9 RES 5 C | 2 8 | - - - -
                C &= 0xDF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xAA RES 5 D | 2 8 | - - - -
                D &= 0xDF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xAB RES 5 E | 2 8 | - - - -
                E &= 0xDF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xAC RES 5 H | 2 8 | - - - -
                H &= 0xDF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xAD RES 5 L | 2 8 | - - - -
                L &= 0xDF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xAE RES 5 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xDF;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xAF RES 5 A | 2 8 | - - - -
                A &= 0xDF;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0xB0 RES 6 B | 2 8 | - - - -
                B &= ~(1 << 6); // bitwise AND of (10111111)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xB1 RES 6 C | 2 8 | - - - -
                C &= 0xBF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xB2 RES 6 D | 2 8 | - - - -
                D &= 0xBF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xB3 RES 6 E | 2 8 | - - - -
                E &= 0xBF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xB4 RES 6 H | 2 8 | - - - -
                H &= 0xBF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xB5 RES 6 L | 2 8 | - - - -
                L &= 0xBF;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xB6 RES 6 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0xBF;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xB7 RES 6 A | 2 8 | - - - -
                A &= 0xBF;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0xB8 RES 7 B | 2 8 | - - - -
                B &= ~(1 << 7); // bitwise AND of (01111111)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xB9 RES 7 C | 2 8 | - - - -
                C &= 0x7F;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xBA RES 7 D | 2 8 | - - - -
                D &= 0x7F;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xBB RES 7 E | 2 8 | - - - -
                E &= 0x7F;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xBC RES 7 H | 2 8 | - - - -
                H &= 0x7F;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xBD RES 7 L | 2 8 | - - - -
                L &= 0x7F;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xBE RES 7 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value &= 0x7F;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xBF RES 7 A | 2 8 | - - - -
                A &= 0x7F;
                PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0xC0){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0xC0 SET 0 B | 2 8 | - - - - 
                B |= (1 << 0); // bitwise OR of (00000001)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xC1 SET 0 C | 2 8 | - - - -
                C |= 0x01;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xC2 SET 0 D | 2 8 | - - - -
                D |= 0x01;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xC3 SET 0 E | 2 8 | - - - -
                E |= 0x01;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xC4 SET 0 H | 2 8 | - - - -
                H |= 0x01;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xC5 SET 0 L | 2 8 | - - - -
                L |= 0x01;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xC6 SET 0 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x01;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xC7 SET 0 A | 2 8 | - - - -
                A |= 0x01;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0xC8 SET 1 B | 2 8 | - - - - 
                B |= (1 << 1); // bitwise OR of (00000010)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xC9 SET 1 C | 2 8 | - - - -
                C |= 0x02;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xCA SET 1 D | 2 8 | - - - -
                D |= 0x02;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xCB SET 1 E | 2 8 | - - - -
                E |= 0x02;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xCC SET 1 H | 2 8 | - - - -
                H |= 0x02;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xCD SET 1 L | 2 8 | - - - -
                L |= 0x02;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xCE SET 1 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x02;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xCF SET 1 A | 2 8 | - - - -
                A |= 0x02;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0xD0 SET 2 B | 2 8 | - - - -
                B |= (1 << 2); // bitwise OR of (00000100)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xD1 SET 2 C | 2 8 | - - - -
                C |= 0x04;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xD2 SET 2 D | 2 8 | - - - -
                D |= 0x04;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xD3 SET 2 E | 2 8 | - - - -
                E |= 0x04;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xD4 SET 2 H | 2 8 | - - - -
                H |= 0x04;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xD5 SET 2 L | 2 8 | - - - -
                L |= 0x04;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xD6 SET 2 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x04;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xD7 SET 2 A | 2 8 | - - - -
                A |= 0x04;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0xD8 SET 3 B | 2 8 | - - - -
                B |= (1 << 3); // bitwise OR of (00001000)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xD9 SET 3 C | 2 8 | - - - -
                C |= 0x08;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xDA SET 3 D | 2 8 | - - - -
                D |= 0x08;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                //0xCB 0xDB SET 3 E | 2 8 | - - - -
                E |= 0x08;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xDC SET 3 H | 2 8 | - - - -
                H |= 0x08;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xDD SET 3 L | 2 8 | - - - -
                L |= 0x08;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xDE SET 3 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x08;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xDF SET 3 A | 2 8 | - - - -
                A |= 0x08;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0xE0 SET 4 B | 2 8 | - - - -
                B |= (1 << 4); // bitwise OR of (00010000)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xE1 SET 4 C | 2 8 | - - - -
                C |= 0x10;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xE2 SET 4 D | 2 8 | - - - -
                D |= 0x10;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xE3 SET 4 E | 2 8 | - - - -
                E |= 0x10;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xE4 SET 4 H | 2 8 | - - - -
                H |= 0x10;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xE5 SET 4 L | 2 8 | - - - -
                L |= 0x10;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xE6 SET 4 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x10;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xE7 SET 4 A | 2 8 | - - - -
                A |= 0x10;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0xE8 SET 5 B | 2 8 | - - - -
                B |= (1 << 5); // bitwise OR of (00100000)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xE9 SET 5 C | 2 8 | - - - -
                C |= 0x20;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xEA SET 5 D | 2 8 | - - - -
                D |= 0x20;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xEB SET 5 E | 2 8 | - - - -
                E |= 0x20;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xEC SET 5 H | 2 8 | - - - -
                H |= 0x20;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xED SET 5 L | 2 8 | - - - -
                L |= 0x20;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xEE SET 5 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x20;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xEF SET 5 A | 2 8 | - - - -
                A |= 0x20;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0xF0 SET 6 B | 2 8 | - - - -
                B |= (1 << 6); // bitwise OR of (01000000)
                PC += 1;
                return 8;       
            }
            else if (endblock == 0x01){
                // 0xCB 0xF1 SET 6 C | 2 8 | - - - -
                C |= 0x40;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xF2 SET 6 D | 2 8 | - - - -
                D |= 0x40;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xF3 SET 6 E | 2 8 | - - - -
                E |= 0x40;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xF4 SET 6 H | 2 8 | - - - -
                H |= 0x40;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xF5 SET 6 L | 2 8 | - - - -
                L |= 0x40;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xF6 SET 6 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x40;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xF7 SET 6 A | 2 8 | - - - -
                A |= 0x40;
                PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0xF8 SET 7 B | 2 8 | - - - -
                B |= (1 << 7); // bitwise OR of (10000000)
                PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xF9 SET 7 C | 2 8 | - - - -
                C |= 0x80;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xFA SET 7 D | 2 8 | - - - -
                D |= 0x80;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xFB SET 7 E | 2 8 | - - - -
                E |= 0x80;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xFC SET 7 H | 2 8 | - - - -
                H |= 0x80;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xFD SET 7 L | 2 8 | - - - -
                L |= 0x80;
                PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xFE SET 7 [HL] | 2 16 | - - - -
                uint8_t value = readByte(getHL());
                value |= 0x80;
                writeByte(getHL(), value);
                PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xFF SET 7 A | 2 8 | - - - -
                A |= 0x80;
                PC += 1;
                return 8;
            }
        }
    }
    else{
        return -8; // Return -8 if no valid CB opcode found
    }
}
