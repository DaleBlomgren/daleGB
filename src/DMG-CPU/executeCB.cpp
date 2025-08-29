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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
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
                PC += 2;
                return 8;
            }
        }
        else if (subblock == 0x10){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x18){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x20){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x28){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x30){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x38){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
    }
    else if (block == 0x40){
        if (subblock == 0x00){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x08){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x18){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x20){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x28){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x30){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x38){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
    }
    else if (block == 0x80){
        if (subblock == 0x00){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x08){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x18){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x20){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x28){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x30){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x38){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
    }
    else if (block == 0xC0){
        if (subblock == 0x00){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x08){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x18){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x20){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x28){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x30){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
        else if (subblock == 0x38){
            if (endblock == 0x00){
                
            }
            else if (endblock == 0x01){

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
    }
    else{
        return -8; // Return -8 if no valid CB opcode found
    }
}
