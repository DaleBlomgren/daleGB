#pragma once
#include "SM83.h"

class SM83;  // Forward declaration

namespace CBInstructions {
    // Function to execute CB-prefixed instructions
    int executeCB(SM83& cpu, MBC& memoryBank);
}
