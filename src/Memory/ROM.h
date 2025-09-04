#pragma once

struct ROMHeader {
    std::vector<uint8_t> title;
    std::vector<uint8_t> manufacturerCode;
    uint8_t CGBFlag;
    std::vector<uint8_t> newLicenseeCode;
    uint8_t SGBFlag;
    uint8_t MBCCode;
    uint8_t ROMSize;
    uint8_t RAMSize;
    uint8_t destinationCode;
    uint8_t oldLicenseeCode;
    uint8_t maskROMVersionNumber;
    uint8_t headerChecksum; //BootRom runs the check when GB is turned on
    std::vector<uint8_t> globalChecksum; //Sum of all bytes of the cartridge ROM (except for the two checksum bytes) Not used in anything except for Pokemon Stadium
};

class ROM {
    private:
        std::vector<uint8_t> fullROM;
        std::uintmax_t size;
        struct ROMHeader header{};
    public:
        ROM();
        ROM(const char* filename);
        ~ROM();
        void interpretGameHeader();
        void printROMBinary();
        bool loadROM(const char* filename);
        bool loadHeader();
        uint8_t getMBC();
};
