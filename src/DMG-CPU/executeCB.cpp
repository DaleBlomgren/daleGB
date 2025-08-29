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
