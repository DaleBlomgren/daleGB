#pragma once
#include "SM83.h"

class SM83;  // Forward declaration

namespace CBInstructions {
    // Function to execute CB-prefixed instructions
    int executeCB(MBC& memoryBank);
}
