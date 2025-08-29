class SM83
{
    friend namespace CBInstructions;  // Allow CB instructions to access private members
    
    struct flags{
        bool Z; // Zero Flag
        bool N; // Subtract Flag
        bool H; // Half Carry Flag
        bool C; // Carry Flag
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
    //    int referenceTableN();
    //    int referenceTableCB();
    //    int executeCB();
        flags flags;
        uint64_t cycles;
};