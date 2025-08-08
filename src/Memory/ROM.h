#pragma once

struct ROMHeader {
//    ROMHeader(std::vector<uint8_t> titlebuffer, std::vector<uint8_t> manufacturercodebuffer, std::vector<uint8_t> cgbflagbuffer, std::vector<uint8_t> newlicenseecodebuffer,
//        std::vector<uint8_t> sgbflagbuffer, std::vector<uint8_t> cartridgetypebuffer, std::vector<uint8_t> romsizebuffer, std::vector<uint8_t> ramsizebuffer,
//        std::vector<uint8_t> destinationcodebuffer, std::vector<uint8_t> oldlicenseecodebuffer, std::vector<uint8_t> maskromversionnumberbuffer, std::vector<uint8_t> headerchecksumbuffer,
//        std::vector<uint8_t> globalchecksumbuffer) : title{titlebuffer}, manufacturerCode{manufacturercodebuffer}, CGBFlag{cgbflagbuffer}, newLicenseeCode{newlicenseecodebuffer},
//        SGBFlag{sgbflagbuffer}, cartridgeType{cartridgetypebuffer}, ROMSize{romsizebuffer}, RAMSize{ramsizebuffer}, destinationCode{destinationcodebuffer},
//        oldLicenseeCode{oldlicenseecodebuffer}, maskROMVersionNumber{maskromversionnumberbuffer}, headerChecksum{headerchecksumbuffer}, globalChecksum{globalchecksumbuffer} {}
    std::vector<uint8_t> title;
    std::vector<uint8_t> manufacturerCode;
    uint8_t CGBFlag;
    std::vector<uint8_t> newLicenseeCode;
    uint8_t SGBFlag;
    uint8_t cartridgeType;
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
};
