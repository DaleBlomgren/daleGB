#include "executeCB.h"
#include "SM83.h"


namespace CBInstructions {

int executeCB(SM83& cpu, MBC& memoryBank) {
    uint8_t opcode = (cpu.PC >> 8) & 0xFF;
    uint8_t block = opcode & 0xC0;
    uint8_t subblock = opcode & 0x38;
    uint8_t endblock = opcode & 0x07;

    if (block == 0x00){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x00 RLC B | 2 8 | Z 0 0 C
                uint8_t result = (cpu.B << 1) | (cpu.B >> 7);
                cpu.flags.C = (cpu.B >> 7) & 0x01;
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;                
            }
            else if (endblock == 0x01){
                // 0xCB 0x01 RLC C | 2 8 | Z 0 0 C
                uint8_t result = (cpu.C << 1) | (cpu.C >> 7);
                cpu.flags.C = (cpu.C >> 7) & 0x01;
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x02 RLC D | 2 8 | Z 0 0 C
                uint8_t result = (cpu.D << 1) | (cpu.D >> 7);
                cpu.flags.C = (cpu.D >> 7) & 0x01;
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;                
            }
            else if (endblock == 0x03){
                // 0xCB 0x03 RLC E | 2 8 | Z 0 0 C
                uint8_t result = (cpu.E << 1) | (cpu.E >> 7);
                cpu.flags.C = (cpu.E >> 7) & 0x01;
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;                
            }
            else if (endblock == 0x04){
                // 0xCB 0x04 RLC H | 2 8 | Z 0 0 C
                uint8_t result = (cpu.H << 1) | (cpu.H >> 7);
                cpu.flags.C = (cpu.H >> 7) & 0x01;
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x05 RLC L | 2 8 | Z 0 0 C
                uint8_t result = (cpu.L << 1) | (cpu.L >> 7);
                cpu.flags.C = (cpu.L >> 7) & 0x01;
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x06 RLC [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value << 1) | (value >> 7);
                cpu.flags.C = (value >> 7) & 0x01;
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;                
            }
            else if (endblock == 0x07){
                // 0xCB 0x07 RLC A | 2 8 | Z 0 0 C
                uint8_t result = (cpu.A << 1) | (cpu.A >> 7);
                cpu.flags.C = (cpu.A >> 7) & 0x01;
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;                
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                //  0xCB 0x08 RRC B | 2 8 | Z 0 0 C
                uint8_t result = (cpu.B >> 1) | (cpu.B << 7);
                cpu.flags.C = cpu.B & 0x01;
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x09 RRC C | 2 8 | Z 0 0 C
                uint8_t result = (cpu.C >> 1) | (cpu.C << 7);
                cpu.flags.C = cpu.C & 0x01;
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x0A RRC D | 2 8 | Z 0 0 C
                uint8_t result = (cpu.D >> 1) | (cpu.D << 7);
                cpu.flags.C = cpu.D & 0x01;
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x0B RRC E | 2 8 | Z 0 0 C
                uint8_t result = (cpu.E >> 1) | (cpu.E << 7);
                cpu.flags.C = cpu.E & 0x01;
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;                
            }
            else if (endblock == 0x04){
                // 0xCB 0x0C RRC H | 2 8 | Z 0 0 C
                uint8_t result = (cpu.H >> 1) | (cpu.H << 7);
                cpu.flags.C = cpu.H & 0x01;
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;                                
            }
            else if (endblock == 0x05){
                // 0xCB 0x0D RRC L | 2 8 | Z 0 0 C
                uint8_t result = (cpu.L >> 1) | (cpu.L << 7);
                cpu.flags.C = cpu.L & 0x01;
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;                                                
            }
            else if (endblock == 0x06){
                // 0xCB 0x0E RRC [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value >> 1) | (value << 7);
                cpu.flags.C = value & 0x01;
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x0F RRC A | 2 8 | Z 0 0 C
                uint8_t result = (cpu.A >> 1) | (cpu.A << 7);
                cpu.flags.C = cpu.A & 0x01;
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x10 RL B | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.B << 1) | carry;
                cpu.flags.C = (cpu.B >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x11 RL C | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.C << 1) | carry;
                cpu.flags.C = (cpu.C >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x12 RL D | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.D << 1) | carry;
                cpu.flags.C = (cpu.D >> 7) & 0x01; //popped bit on left hand side saved in carry flag
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x13 RL E | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.E << 1) | carry;
                cpu.flags.C = (cpu.E >> 7) & 0x01; 
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x14 RL H | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.H << 1) | carry;
                cpu.flags.C = (cpu.H >> 7) & 0x01; 
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;                
            }
            else if (endblock == 0x05){
                // 0xCB 0x15 RL L | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.L << 1) | carry;
                cpu.flags.C = (cpu.L >> 7) & 0x01; 
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x16 RL [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (value << 1) | carry;
                cpu.flags.C = (value >> 7) & 0x01; 
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x17 RL A | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.A << 1) | carry;
                cpu.flags.C = (cpu.A >> 7) & 0x01; 
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;   
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x18 RR B | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.B >> 1) | (carry << 7);
                cpu.flags.C = cpu.B & 0x01; 
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x19 RR C | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.C >> 1) | (carry << 7);
                cpu.flags.C = cpu.C & 0x01; 
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x1A RR D | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.D >> 1) | (carry << 7);
                cpu.flags.C = cpu.D & 0x01; 
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x1B RR E | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.E >> 1) | (carry << 7);
                cpu.flags.C = cpu.E & 0x01; 
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x1C RR H | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.H >> 1) | (carry << 7);
                cpu.flags.C = cpu.H & 0x01; 
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x1D RR L | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.L >> 1) | (carry << 7);
                cpu.flags.C = cpu.L & 0x01; 
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x1E RR [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (value >> 1) | (carry << 7);
                cpu.flags.C = value & 0x01; 
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x1F RR A | 2 8 | Z 0 0 C
                uint8_t carry = cpu.flags.C ? 1 : 0;
                uint8_t result = (cpu.A >> 1) | (carry << 7);
                cpu.flags.C = cpu.A & 0x01; 
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0x20 SLA B | 2 8 | Z 0 0 C
                uint8_t result = (cpu.B << 1);
                cpu.flags.C = (cpu.B >> 7) & 0x01;
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x21 SLA C | 2 8 | Z 0 0 C
                uint8_t result = (cpu.C << 1);
                cpu.flags.C = (cpu.C >> 7) & 0x01;
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x22 SLA D | 2 8 | Z 0 0 C
                uint8_t result = (cpu.D << 1);
                cpu.flags.C = (cpu.D >> 7) & 0x01;
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x23 SLA E | 2 8 | Z 0 0 C
                uint8_t result = (cpu.E << 1);
                cpu.flags.C = (cpu.E >> 7) & 0x01;
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x24 SLA H | 2 8 | Z 0 0 C
                uint8_t result = (cpu.H << 1);
                cpu.flags.C = (cpu.H >> 7) & 0x01;
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x25 SLA L | 2 8 | Z 0 0 C
                uint8_t result = (cpu.L << 1);
                cpu.flags.C = (cpu.L >> 7) & 0x01;
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x26 SLA [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value << 1);
                cpu.flags.C = (value >> 7) & 0x01;
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x27 SLA A | 2 8 | Z 0 0 C
                uint8_t result = (cpu.A << 1);
                cpu.flags.C = (cpu.A >> 7) & 0x01;
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0x28 SRA B | 2 8 | Z 0 0 C
                uint8_t result = (cpu.B >> 1) | (cpu.B & 0x80);
                cpu.flags.C = cpu.B & 0x01;
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x29 SRA C | 2 8 | Z 0 0 C
                uint8_t result = (cpu.C >> 1) | (cpu.C & 0x80);
                cpu.flags.C = cpu.C & 0x01;
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x2A SRA D | 2 8 | Z 0 0 C
                uint8_t result = (cpu.D >> 1) | (cpu.D & 0x80);
                cpu.flags.C = cpu.D & 0x01;
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x2B SRA E | 2 8 | Z 0 0 C
                uint8_t result = (cpu.E >> 1) | (cpu.E & 0x80);
                cpu.flags.C = cpu.E & 0x01;
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x2C SRA H | 2 8 | Z 0 0 C
                uint8_t result = (cpu.H >> 1) | (cpu.H & 0x80);
                cpu.flags.C = cpu.H & 0x01;
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x2D SRA L | 2 8 | Z 0 0 C
                uint8_t result = (cpu.L >> 1) | (cpu.L & 0x80);
                cpu.flags.C = cpu.L & 0x01;
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x2E SRA [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value >> 1) | (value & 0x80);
                cpu.flags.C = value & 0x01;
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x2F SRA A | 2 8 | Z 0 0 C
                uint8_t result = (cpu.A >> 1) | (cpu.A & 0x80);
                cpu.flags.C = cpu.A & 0x01;
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0x30 SWAP B | 2 8 | Z 0 0 0
                uint8_t result = (cpu.B << 4) | (cpu.B >> 4);
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x31 SWAP C | 2 8 | Z 0 0 0
                uint8_t result = (cpu.C << 4) | (cpu.C >> 4);
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x32 SWAP D | 2 8 | Z 0 0 0
                uint8_t result = (cpu.D << 4) | (cpu.D >> 4);
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x33 SWAP E | 2 8 | Z 0 0 0
                uint8_t result = (cpu.E << 4) | (cpu.E >> 4);
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x34 SWAP H | 2 8 | Z 0 0 0
                uint8_t result = (cpu.H << 4) | (cpu.H >> 4);
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x35 SWAP L | 2 8 | Z 0 0 0
                uint8_t result = (cpu.L << 4) | (cpu.L >> 4);
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x36 SWAP [HL] | 2 16 | Z 0 0 0
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value << 4) | (value >> 4);
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x37 SWAP A | 2 8 | Z 0 0 0
                uint8_t result = (cpu.A << 4) | (cpu.A >> 4);
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.flags.C = false;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0x38 SRL B | 2 8 | Z 0 0 C
                uint8_t result = (cpu.B >> 1);
                cpu.flags.C = cpu.B & 0x01;
                cpu.B = result;
                cpu.flags.Z = (cpu.B == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x39 SRL C | 2 8 | Z 0 0 C
                uint8_t result = (cpu.C >> 1);
                cpu.flags.C = cpu.C & 0x01;
                cpu.C = result;
                cpu.flags.Z = (cpu.C == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x3A SRL D | 2 8 | Z 0 0 C
                uint8_t result = (cpu.D >> 1);
                cpu.flags.C = cpu.D & 0x01;
                cpu.D = result;
                cpu.flags.Z = (cpu.D == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x3B SRL E | 2 8 | Z 0 0 C
                uint8_t result = (cpu.E >> 1);
                cpu.flags.C = cpu.E & 0x01;
                cpu.E = result;
                cpu.flags.Z = (cpu.E == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x3C SRL H | 2 8 | Z 0 0 C
                uint8_t result = (cpu.H >> 1);
                cpu.flags.C = cpu.H & 0x01;
                cpu.H = result;
                cpu.flags.Z = (cpu.H == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x3D SRL L | 2 8 | Z 0 0 C
                uint8_t result = (cpu.L >> 1);
                cpu.flags.C = cpu.L & 0x01;
                cpu.L = result;
                cpu.flags.Z = (cpu.L == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x3E SRL [HL] | 2 16 | Z 0 0 C
                uint8_t value = memoryBank.readByte(cpu.getHL());
                uint8_t result = (value >> 1);
                cpu.flags.C = value & 0x01;
                memoryBank.writeByte(cpu.getHL(), result);
                cpu.flags.Z = (result == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x3F SRL A | 2 8 | Z 0 0 C
                uint8_t result = (cpu.A >> 1);
                cpu.flags.C = cpu.A & 0x01;
                cpu.A = result;
                cpu.flags.Z = (cpu.A == 0);
                cpu.flags.N = false;
                cpu.flags.H = false;    
                cpu.PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0x40){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x40 BIT 0 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x41 BIT 0 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x42 BIT 0 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x43 BIT 0 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x44 BIT 0 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x45 BIT 0 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x46 BIT 0 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x47 BIT 0 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x01);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0x48 BIT 1 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x49 BIT 1 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x4A BIT 1 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x4B BIT 1 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x4C BIT 1 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x4D BIT 1 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x4E BIT 1 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x4F BIT 1 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x02);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x50 BIT 2 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x51 BIT 2 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x52 BIT 2 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x53 BIT 2 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x54 BIT 2 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x55 BIT 2 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x56 BIT 2 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x57 BIT 2 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x04);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x58 BIT 3 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x59 BIT 3 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x5A BIT 3 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x5B BIT 3 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x5C BIT 3 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x5D BIT 3 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x5E BIT 3 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x5F BIT 3 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x08);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0x60 BIT 4 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x61 BIT 4 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x62 BIT 4 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x63 BIT 4 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x64 BIT 4 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x65 BIT 4 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x66 BIT 4 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x67 BIT 4 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x10);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0x68 BIT 5 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x69 BIT 5 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x6A BIT 5 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x6B BIT 5 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x6C BIT 5 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x6D BIT 5 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x6E BIT 5 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x6F BIT 5 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x20);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0x70 BIT 6 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x71 BIT 6 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x72 BIT 6 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x73 BIT 6 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x74 BIT 6 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x75 BIT 6 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x76 BIT 6 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x77 BIT 6 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x40);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0x78 BIT 7 B | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.B & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x79 BIT 7 C | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.C & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x7A BIT 7 D | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.D & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x7B BIT 7 E | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.E & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x7C BIT 7 H | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.H & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x7D BIT 7 L | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.L & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x7E BIT 7 [HL] | 2 12 | Z 0 1 -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                cpu.flags.Z = !(value & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 12;
            }
            else if (endblock == 0x07){
                // 0xCB 0x7F BIT 7 A | 2 8 | Z 0 1 -
                cpu.flags.Z = !(cpu.A & 0x80);
                cpu.flags.N = false;
                cpu.flags.H = true;
                cpu.PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0x80){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0x80 RES 0 B | 2 8 | - - - - Reset bit 0 of B
                cpu.B &= ~(1 << 0); // bitwise AND of (11111110) created from 1 << 0 (00000001)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x81 RES 0 C | 2 8 | - - - -
                cpu.C &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x82 RES 0 D | 2 8 | - - - -
                cpu.D &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x83 RES 0 E | 2 8 | - - - -
                cpu.E &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x84 RES 0 H | 2 8 | - - - -
                cpu.H &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x85 RES 0 L | 2 8 | - - - -
                cpu.L &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x86 RES 0 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xFE;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x87 RES 0 A | 2 8 | - - - -
                cpu.A &= 0xFE;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0x88 RES 1 B | 2 8 | - - - - Reset bit 1 of B
                cpu.B &= ~(1 << 1); // bitwise AND of (11111101)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x89 RES 1 C | 2 8 | - - - -
                cpu.C &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x8A RES 1 D | 2 8 | - - - -
                cpu.D &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x8B RES 1 E | 2 8 | - - - -
                cpu.E &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x8C RES 1 H | 2 8 | - - - -
                cpu.H &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x8D RES 1 L | 2 8 | - - - -
                cpu.L &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x8E RES 1 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xFD;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x8F RES 1 A | 2 8 | - - - -
                cpu.A &= 0xFD;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0x90 RES 2 B | 2 8 | - - - - 
                cpu.B &= ~(1 << 2); // bitwise AND of (11111011)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x91 RES 2 C | 2 8 | - - - -
                cpu.C &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x92 RES 2 D | 2 8 | - - - -
                cpu.D &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x93 RES 2 E | 2 8 | - - - -
                cpu.E &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x94 RES 2 H | 2 8 | - - - -
                cpu.H &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x95 RES 2 L | 2 8 | - - - -
                cpu.L &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x96 RES 2 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xFB;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x97 RES 2 A | 2 8 | - - - -
                cpu.A &= 0xFB;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0x98 RES 3 B | 2 8 | - - - - 
                cpu.B &= ~(1 << 3); // bitwise AND of (11110111)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0x99 RES 3 C | 2 8 | - - - -
                cpu.C &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0x9A RES 3 D | 2 8 | - - - -
                cpu.D &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0x9B RES 3 E | 2 8 | - - - -
                cpu.E &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0x9C RES 3 H | 2 8 | - - - -
                cpu.H &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0x9D RES 3 L | 2 8 | - - - -
                cpu.L &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0x9E RES 3 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xF7;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0x9F RES 3 A | 2 8 | - - - -
                cpu.A &= 0xF7;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0xA0 RES 4 B | 2 8 | - - - -
                cpu.B &= ~(1 << 4); // bitwise AND of (11101111)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xA1 RES 4 C | 2 8 | - - - -
                cpu.C &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xA2 RES 4 D | 2 8 | - - - -
                cpu.D &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xA3 RES 4 E | 2 8 | - - - -
                cpu.E &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xA4 RES 4 H | 2 8 | - - - -
                cpu.H &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xA5 RES 4 L | 2 8 | - - - -
                cpu.L &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xA6 RES 4 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xEF;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xA7 RES 4 A | 2 8 | - - - -
                cpu.A &= 0xEF;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0xA8 RES 5 B | 2 8 | - - - -
                cpu.B &= ~(1 << 5); // bitwise AND of (11011111)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xA9 RES 5 C | 2 8 | - - - -
                cpu.C &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xAA RES 5 D | 2 8 | - - - -
                cpu.D &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xAB RES 5 E | 2 8 | - - - -
                cpu.E &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xAC RES 5 H | 2 8 | - - - -
                cpu.H &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xAD RES 5 L | 2 8 | - - - -
                cpu.L &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xAE RES 5 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xDF;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xAF RES 5 A | 2 8 | - - - -
                cpu.A &= 0xDF;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0xB0 RES 6 B | 2 8 | - - - -
                cpu.B &= ~(1 << 6); // bitwise AND of (10111111)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xB1 RES 6 C | 2 8 | - - - -
                cpu.C &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xB2 RES 6 D | 2 8 | - - - -
                cpu.D &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xB3 RES 6 E | 2 8 | - - - -
                cpu.E &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xB4 RES 6 H | 2 8 | - - - -
                cpu.H &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xB5 RES 6 L | 2 8 | - - - -
                cpu.L &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xB6 RES 6 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0xBF;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xB7 RES 6 A | 2 8 | - - - -
                cpu.A &= 0xBF;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0xB8 RES 7 B | 2 8 | - - - -
                cpu.B &= ~(1 << 7); // bitwise AND of (01111111)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xB9 RES 7 C | 2 8 | - - - -
                cpu.C &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xBA RES 7 D | 2 8 | - - - -
                cpu.D &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xBB RES 7 E | 2 8 | - - - -
                cpu.E &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xBC RES 7 H | 2 8 | - - - -
                cpu.H &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xBD RES 7 L | 2 8 | - - - -
                cpu.L &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xBE RES 7 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value &= 0x7F;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xBF RES 7 A | 2 8 | - - - -
                cpu.A &= 0x7F;
                cpu.PC += 1;
                return 8;
            }
        }
    }
    else if (block == 0xC0){
        if (subblock == 0x00){
            if (endblock == 0x00){
                // 0xCB 0xC0 SET 0 B | 2 8 | - - - - 
                cpu.B |= (1 << 0); // bitwise OR of (00000001)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xC1 SET 0 C | 2 8 | - - - -
                cpu.C |= 0x01;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xC2 SET 0 D | 2 8 | - - - -
                cpu.D |= 0x01;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xC3 SET 0 E | 2 8 | - - - -
                cpu.E |= 0x01;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xC4 SET 0 H | 2 8 | - - - -
                cpu.H |= 0x01;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xC5 SET 0 L | 2 8 | - - - -
                cpu.L |= 0x01;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xC6 SET 0 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x01;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xC7 SET 0 A | 2 8 | - - - -
                cpu.A |= 0x01;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x08){
            if (endblock == 0x00){
                // 0xCB 0xC8 SET 1 B | 2 8 | - - - - 
                cpu.B |= (1 << 1); // bitwise OR of (00000010)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xC9 SET 1 C | 2 8 | - - - -
                cpu.C |= 0x02;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xCA SET 1 D | 2 8 | - - - -
                cpu.D |= 0x02;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xCB SET 1 E | 2 8 | - - - -
                cpu.E |= 0x02;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xCC SET 1 H | 2 8 | - - - -
                cpu.H |= 0x02;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xCD SET 1 L | 2 8 | - - - -
                cpu.L |= 0x02;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xCE SET 1 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x02;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xCF SET 1 A | 2 8 | - - - -
                cpu.A |= 0x02;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                // 0xCB 0xD0 SET 2 B | 2 8 | - - - -
                cpu.B |= (1 << 2); // bitwise OR of (00000100)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xD1 SET 2 C | 2 8 | - - - -
                cpu.C |= 0x04;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xD2 SET 2 D | 2 8 | - - - -
                cpu.D |= 0x04;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xD3 SET 2 E | 2 8 | - - - -
                cpu.E |= 0x04;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xD4 SET 2 H | 2 8 | - - - -
                cpu.H |= 0x04;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xD5 SET 2 L | 2 8 | - - - -
                cpu.L |= 0x04;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xD6 SET 2 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x04;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xD7 SET 2 A | 2 8 | - - - -
                cpu.A |= 0x04;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x18){
            if (endblock == 0x00){
                // 0xCB 0xD8 SET 3 B | 2 8 | - - - -
                cpu.B |= (1 << 3); // bitwise OR of (00001000)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xD9 SET 3 C | 2 8 | - - - -
                cpu.C |= 0x08;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xDA SET 3 D | 2 8 | - - - -
                cpu.D |= 0x08;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                //0xCB 0xDB SET 3 E | 2 8 | - - - -
                cpu.E |= 0x08;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xDC SET 3 H | 2 8 | - - - -
                cpu.H |= 0x08;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xDD SET 3 L | 2 8 | - - - -
                cpu.L |= 0x08;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xDE SET 3 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x08;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xDF SET 3 A | 2 8 | - - - -
                cpu.A |= 0x08;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x20){
            if (endblock == 0x00){
                // 0xCB 0xE0 SET 4 B | 2 8 | - - - -
                cpu.B |= (1 << 4); // bitwise OR of (00010000)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xE1 SET 4 C | 2 8 | - - - -
                cpu.C |= 0x10;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xE2 SET 4 D | 2 8 | - - - -
                cpu.D |= 0x10;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xE3 SET 4 E | 2 8 | - - - -
                cpu.E |= 0x10;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xE4 SET 4 H | 2 8 | - - - -
                cpu.H |= 0x10;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xE5 SET 4 L | 2 8 | - - - -
                cpu.L |= 0x10;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xE6 SET 4 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x10;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xE7 SET 4 A | 2 8 | - - - -
                cpu.A |= 0x10;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x28){
            if (endblock == 0x00){
                // 0xCB 0xE8 SET 5 B | 2 8 | - - - -
                cpu.B |= (1 << 5); // bitwise OR of (00100000)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xE9 SET 5 C | 2 8 | - - - -
                cpu.C |= 0x20;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xEA SET 5 D | 2 8 | - - - -
                cpu.D |= 0x20;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xEB SET 5 E | 2 8 | - - - -
                cpu.E |= 0x20;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xEC SET 5 H | 2 8 | - - - -
                cpu.H |= 0x20;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xED SET 5 L | 2 8 | - - - -
                cpu.L |= 0x20;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xEE SET 5 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x20;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xEF SET 5 A | 2 8 | - - - -
                cpu.A |= 0x20;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x30){
            if (endblock == 0x00){
                // 0xCB 0xF0 SET 6 B | 2 8 | - - - -
                cpu.B |= (1 << 6); // bitwise OR of (01000000)
                cpu.PC += 1;
                return 8;       
            }
            else if (endblock == 0x01){
                // 0xCB 0xF1 SET 6 C | 2 8 | - - - -
                cpu.C |= 0x40;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xF2 SET 6 D | 2 8 | - - - -
                cpu.D |= 0x40;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xF3 SET 6 E | 2 8 | - - - -
                cpu.E |= 0x40;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xF4 SET 6 H | 2 8 | - - - -
                cpu.H |= 0x40;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xF5 SET 6 L | 2 8 | - - - -
                cpu.L |= 0x40;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xF6 SET 6 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x40;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xF7 SET 6 A | 2 8 | - - - -
                cpu.A |= 0x40;
                cpu.PC += 1;
                return 8;
            }
        }
        else if (subblock == 0x38){
            if (endblock == 0x00){
                // 0xCB 0xF8 SET 7 B | 2 8 | - - - -
                cpu.B |= (1 << 7); // bitwise OR of (10000000)
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x01){
                // 0xCB 0xF9 SET 7 C | 2 8 | - - - -
                cpu.C |= 0x80;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x02){
                // 0xCB 0xFA SET 7 D | 2 8 | - - - -
                cpu.D |= 0x80;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x03){
                // 0xCB 0xFB SET 7 E | 2 8 | - - - -
                cpu.E |= 0x80;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x04){
                // 0xCB 0xFC SET 7 H | 2 8 | - - - -
                cpu.H |= 0x80;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x05){
                // 0xCB 0xFD SET 7 L | 2 8 | - - - -
                cpu.L |= 0x80;
                cpu.PC += 1;
                return 8;
            }
            else if (endblock == 0x06){
                // 0xCB 0xFE SET 7 [HL] | 2 16 | - - - -
                uint8_t value = memoryBank.readByte(cpu.getHL());
                value |= 0x80;
                memoryBank.writeByte(cpu.getHL(), value);
                cpu.PC += 1;
                return 16;
            }
            else if (endblock == 0x07){
                // 0xCB 0xFF SET 7 A | 2 8 | - - - -
                cpu.A |= 0x80;
                cpu.PC += 1;
                return 8;
            }
        }
    }
  return -8; // Return -8 if no valid CB opcode found
}
}