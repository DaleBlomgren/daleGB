
#include <stdint.h>
#include <errno.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include "ROM.h"

ROM::ROM() {

}

ROM::~ROM() {

}

ROM::ROM(const char* filename) {
    loadROM(filename);
    loadHeader();
}

bool ROM::loadROM(const char* filename) {
    //Get ROM Size
    std::filesystem::path inputFilePath{filename};
    auto length = std::filesystem::file_size(inputFilePath);
    if (length == 0){
        std::cout << "Error: Length == 0\n";
        return false;
    }
    else
        size = length;

    //Initialize ROM Binary Vector with size extrapilated from earlier std::filesystem function
    std::vector<uint8_t> buffer(size);

    //Open and read file to ROM data structure
    std::ifstream pfile(filename, std::ios_base::binary);
    if (pfile.is_open()){
        pfile.read(reinterpret_cast<char*>(buffer.data()), length);
    }
    else {
        fputs("File error", stderr);
        pfile.close();
        return false;
    }
    
    //Assign Buffer to private vector
    fullROM = buffer;

    pfile.close();
    return true;
}

void ROM::printROMBinary(){
    for (uint8_t byte : fullROM) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl; // Restore the output format to decimal
}

void ROM::interpretGameHeader(){
    std::cout << "Rom Title: ";
    for (const auto& element : header.title) {
        std::cout << static_cast<char>(element);
    }
    std::cout << std::endl;

    std::cout << "Manufacturer Code: ";
    for (uint8_t byte : header.manufacturerCode){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;

    std::cout << "CGBFlag: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.CGBFlag) << std::dec << std::endl;
    std::cout << "SGBFlag: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.SGBFlag) << std::dec << std::endl;
//    std::cout << "Old Licensee Code: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.oldLicenseeCode) << std::dec << std::endl;
    std::cout << "Licensee Holder: ";
    std::stringstream hexStream;
    std::string hexCheck;
    switch(header.oldLicenseeCode){
        case 0x33:
            switch(static_cast<char>(header.newLicenseeCode[0])){
                case '0':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "None" << std::endl;
                            break;
                        case '1':
                            std::cout << "Nintendo R&D1" << std::endl;
                            break;
                        case '8':
                            std::cout << "Capcom" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '1':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '3':
                            std::cout << "Electronic Arts" << std::endl;
                            break;
                        case '8':
                            std::cout << "Hudson Soft" << std::endl;
                            break;
                        case '9':
                            std::cout << "b-ai" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '2':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "kss" << std::endl;
                            break;
                        case '2':
                            std::cout << "pow" << std::endl;
                            break;
                        case '4':
                            std::cout << "PCM Complete" << std::endl;
                            break;
                        case '5':
                            std::cout << "san-x" << std::endl;
                            break;
                        case '8':
                            std::cout << "Kemco Japan" << std::endl;
                            break;
                        case '9':
                            std::cout << "seta" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '3':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "Viacom" << std::endl;
                            break;
                        case '1':
                            std::cout << "Nintendo" << std::endl;
                            break;
                        case '2':
                            std::cout << "Bandai" << std::endl;
                            break;
                        case '3': 
                            std::cout << "Ocean/Acclaim" << std::endl;
                            break;
                        case '4':
                            std::cout << "Konami" << std::endl;
                            break;
                        case '5':
                            std::cout << "Hector" << std::endl;
                            break;
                        case '7':
                            std::cout << "Taito" << std::endl;
                            break;
                        case '8':
                            std::cout << "Hudson" << std::endl;
                            break;
                        case '9':
                            std::cout << "Banpresto" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '4':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '1':
                            std::cout << "Ubisoft" << std::endl;
                            break;
                        case '2':
                            std::cout << "Atlus" << std::endl;
                            break;
                        case '4':
                            std::cout << "Malibu" << std::endl;
                            break;
                        case '6':
                            std::cout << "angel" << std::endl;
                            break;
                        case '7':
                            std::cout << "Bullet-Proof" << std::endl;
                            break;
                        case '9':
                            std::cout << "irem" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '5':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "Absolute" << std::endl;
                            break;
                        case '1':
                            std::cout << "Acclaim" << std::endl;
                            break;
                        case '2':
                            std::cout << "Activision" << std::endl;
                            break;
                        case '3':
                            std::cout << "American Sammy" << std::endl;
                            break;
                        case '4': 
                            std::cout << "Konami" << std::endl;
                            break;
                        case '5':
                            std::cout << "Hi tech entertainment" << std::endl;
                            break;
                        case '6':
                            std::cout << "LJN" << std::endl;
                            break;
                        case '7':
                            std::cout << "Matchbox" << std::endl;
                            break;
                        case '8':
                            std::cout << "Mattel" << std::endl;
                            break;
                        case '9':
                            std::cout << "Milton Bradley" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '6':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "Titus" << std::endl;
                            break;
                        case '1':
                            std::cout << "Virgin" << std::endl;
                            break;
                        case '4':
                            std::cout << "LucasArts" << std::endl;
                            break;
                        case '7':
                            std::cout << "Ocean" << std::endl;
                            break;
                        case '9':
                            std::cout << "Electronic Arts" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '7':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "Infogrames" << std::endl;
                            break;
                        case '1':
                            std::cout << "Interplay" << std::endl;
                            break;
                        case '2':
                            std::cout << "Broderbund" << std::endl;
                            break;
                        case '3':
                            std::cout << "sculptured" << std::endl;
                            break;
                        case '5':
                            std::cout << "sci" << std::endl;
                            break;
                        case '8':
                            std::cout << "THQ" << std::endl;
                            break;
                        case '9':
                            std::cout << "Accolade" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '8':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '0':
                            std::cout << "misawa" << std::endl;
                            break;
                        case '3':
                            std::cout << "lozc" << std::endl;
                            break;
                        case '6':
                            std::cout << "Tokuma Shoten Intermedia" << std::endl;
                            break;
                        case '7':
                            std::cout << "Tsukuda Original" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case '9':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '1':
                            std::cout << "Chunsoft" << std::endl;
                            break;
                        case '2':
                            std::cout << "Video system" << std::endl;
                            break;
                        case '3':
                            std::cout << "Ocean/Acclaim" << std::endl;
                            break;
                        case '5':
                            std::cout << "Varie" << std::endl;
                            break;
                        case '6':
                            std::cout << "Yonezawa/s'pal" << std::endl;
                            break;
                        case '7':
                            std::cout << "Kaneko" << std::endl;
                            break;
                        case '9':
                            std::cout << "Pack in soft" << std::endl;
                            break;
                        case 'H':
                            std::cout << "Bottoms Up" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                case 'A':
                    switch(static_cast<char>(header.newLicenseeCode[1])){
                        case '4':
                            std::cout << "Konami (Yu-Gi-Oh!)" << std::endl;
                            break;
                        default:
                            std::cout << "Missed Licensee Code" << std::endl;
                    }
                    break;
                default:
                    std::cout << "Missed Licensee Code" << std::endl;
            }
            break;
        case 0x00:
            std::cout << "None" << std::endl;
            break;
        case 0x01:
            std::cout << "Nintendo" << std::endl;
            break;
        case 0x08:
            std::cout << "Capcom" << std::endl;
            break;
        case 0x09:
            std::cout << "Hot-B" << std::endl;
            break;
        case 0x0A:
            std::cout << "Jaleco" << std::endl;
            break;
        case 0x0B:
            std::cout << "Coconuts Japan" << std::endl;
            break;
        case 0x0C:
            std::cout << "Elite Systems" << std::endl;
            break;
        case 0x13:
            std::cout << "EA (Electronic Arts)" << std::endl;
            break;
        case 0x18:
            std::cout << "Hudsonsoft" << std::endl;
            break;
        case 0x19:
            std::cout << "ITC Entertainment" << std::endl;
            break;
        case 0x1A:
            std::cout << "Yanoman" << std::endl;
            break;
        case 0x1D:
            std::cout << "Japan Clary" << std::endl;
            break;
        case 0x1F:
            std::cout << "Virgin Interactive" << std::endl;
            break;
        case 0x24:
            std::cout << "PCM Complete" << std::endl;
            break;
        case 0x25:
            std::cout << "San-X" << std::endl;
            break;
        case 0x28:
            std::cout << "Kotobuki Systems" << std::endl;
            break;
        case 0x29:
            std::cout << "Seta" << std::endl;
            break;
        case 0x30:
            std::cout << "Infogrames" << std::endl;
            break;
        case 0x31:
            std::cout << "Nintendo" << std::endl;
            break;
        case 0x32:
            std::cout << "Bandai" << std::endl;
            break;
        case 0x34:
            std::cout << "Konami" << std::endl;
            break;
        case 0x35:
            std::cout << "HectorSoft" << std::endl;
            break;
        case 0x38:
            std::cout << "Capcom" << std::endl;
            break;
        case 0x39:
            std::cout << "Banpresto" << std::endl;
            break;
        case 0x3C:
            std::cout << ".Entertainment i" << std::endl;
            break;
        case 0x3E:
            std::cout << "Gremlin" << std::endl;
            break;
        case 0x41:
            std::cout << "Ubisoft" << std::endl;
            break;
        case 0x42:
            std::cout << "Atlus" << std::endl;
            break;
        case 0x44:
            std::cout << "Malibu" << std::endl;
            break;
        case 0x46:
            std::cout << "Angel" << std::endl;
            break;
        case 0x47:
            std::cout << "Spectrum Holoby" << std::endl;
            break;
        case 0x49:
            std::cout << "Irem" << std::endl;
            break;
        case 0x4A:
            std::cout << "Virgin Interactive" << std::endl;
            break;
        case 0x4D:
            std::cout << "Malibu" << std::endl;
            break;
        case 0x4F: 
            std::cout << "U.S. Gold" << std::endl;
            break;
        case 0x50:
            std::cout << "Absolute" << std::endl;
            break;
        case 0x51:
            std::cout << "Acclaim" << std::endl;
            break;
        case 0x52:
            std::cout << "Activision" << std::endl;
            break;
        case 0x53:
            std::cout << "American Sammy" << std::endl;
            break;
        case 0x54:
            std::cout << "GameTek" << std::endl;
            break;
        case 0x55:
            std::cout << "Park Place" << std::endl;
            break;
        case 0x56:
            std::cout << "LJN" << std::endl;
            break;
        case 0x57:
            std::cout << "Matchbox" << std::endl;
            break;
        case 0x59:
            std::cout << "Milton Bradley" << std::endl;
            break;
        case 0x5A:
            std::cout << "Mindscape" << std::endl;
            break;
        case 0x5B:
            std::cout << "Romstar" << std::endl;
            break;
        case 0x5C:
            std::cout << "Naxat Soft" << std::endl;
            break;
        case 0x5D:
            std::cout << "Tradewest" << std::endl;
            break;
        case 0x60:
            std::cout << "Titus" << std::endl;
            break;
        case 0x61:
            std::cout << "Virgin Interactive" << std::endl;
            break;
        case 0x67:
            std::cout << "Ocean Interactive" << std::endl;
            break;
        case 0x69:
            std::cout << "EA (Electronic Arts)" << std::endl;
            break;
        case 0x6E:
            std::cout << "Elite Systems" << std::endl;
            break;
        case 0x6F:
            std::cout << "Electro Brain" << std::endl;
            break;
        case 0x70:
            std::cout << "Infogrames" << std::endl;
            break;
        case 0x71:
            std::cout << "Interplay" << std::endl;
            break;
        case 0x72:
            std::cout << "Broderbund" << std::endl;
            break;
        case 0x73:
            std::cout << "Sculptered Soft" << std::endl;
            break;
        case 0x75:
            std::cout << "The Sales Curve" << std::endl;
            break;
        case 0x78:
            std::cout << "t.hq" << std::endl;
            break;
        case 0x79:
            std::cout << "Accolade" << std::endl;
            break;
        case 0x7A:
            std::cout << "Triffix Entertainment" << std::endl;
            break;
        case 0x7C:
            std::cout << "Microprose" << std::endl;
            break;
        case 0x7F:
            std::cout << "Kemco" << std::endl;
            break;
        case 0x80:
            std::cout << "Misawa Entertainment" << std::endl;
            break;
        case 0x83:
            std::cout << "Lozc" << std::endl;
            break;
        case 0x86:
            std::cout << "Tokuma Shoten Intermeda" << std::endl;
            break;
        case 0x8B:
            std::cout << "Bullet-Proof Software" << std::endl;
            break;
        case 0x8C:
            std::cout << "Vic Tokai" << std::endl;
            break;
        case 0x8E:
            std::cout << "Ape" << std::endl;
            break;
        case 0x8F:
            std::cout << "I'Max" << std::endl;
            break;
        case 0x91:
            std::cout << "Chunsoft Co." << std::endl;
            break;
        case 0x92:
            std::cout << "Video System" << std::endl;
            break;
        case 0x93:
            std::cout << "Tsubaraya Productions Co." << std::endl;
            break;
        case 0x95:
            std::cout << "Varie Corporation" << std::endl;
            break;
        case 0x96:
            std::cout << "Yonezawa/S'Pal" << std::endl;
            break;
        case 0x97:
            std::cout << "Kaneko" << std::endl;
            break;
        case 0x99:
            std::cout << "Arc" << std::endl;
            break;
        case 0x9A:
            std::cout << "Nihon Bussan" << std::endl;
            break;
        case 0x9B:
            std::cout << "Tecmo" << std::endl;
            break;
        case 0x9C:
            std::cout << "Imagineer" << std::endl;
            break;
        case 0x9D:
            std::cout << "Banpresto" << std::endl;
            break;
        case 0x9F:
            std::cout << "Nova" << std::endl;
            break;
        case 0xA1:
            std::cout << "Hori Electric" << std::endl;
            break;
        case 0xA2:
            std::cout << "Bandai" << std::endl;
            break;
        case 0xA4:
            std::cout << "Konami" << std::endl;
            break;
        case 0xA6:
            std::cout << "Kawada" << std::endl;
            break;
        case 0xA7:
            std::cout << "Takara" << std::endl;
            break;
        case 0xA9:
            std::cout << "Technos Japan" << std::endl;
            break;
        case 0xAA:
            std::cout << "Broderbund" << std::endl;
            break;
        case 0xAC:
            std::cout << "Toei Animation" << std::endl;
            break;
        case 0xAD:
            std::cout << "Toho" << std::endl;
            break;
        case 0xAF:
            std::cout << "Namco" << std::endl;
            break;
        case 0xB0:
            std::cout << "Acclaim" << std::endl;
            break;
        case 0xB1:
            std::cout << "ASCII or Nexsoft" << std::endl;
            break;
        case 0xB2:
            std::cout << "Bandai" << std::endl;
            break;
        case 0xB4:
            std::cout << "Square Enix" << std::endl;
            break;
        case 0xB6:
            std::cout << "HAL Laboratory" << std::endl;
            break;
        case 0xB7:
            std::cout << "SNK" << std::endl;
            break;
        case 0xB9:
            std::cout << "Pony Canyon" << std::endl;
            break;
        case 0xBA:
            std::cout << "Culture Brain" << std::endl;
            break;
        case 0xBB:
            std::cout << "Sunsoft" << std::endl;
            break;
        case 0xBD:
            std::cout << "Sony Imagesoft" << std::endl;
            break;
        case 0xBF:
            std::cout << "Sammy" << std::endl;
            break;
        case 0xC0:
            std::cout << "Taito" << std::endl;
            break;
        case 0xC2:
            std::cout << "Kemco" << std::endl;
            break;
        case 0xC3:
            std::cout << "Squaresoft" << std::endl;
            break;
        case 0xC4:
            std::cout << "Takuma Shoten Intermedia" << std::endl;
            break;
        case 0xC5:
            std::cout << "Data East" << std::endl;
            break;
        case 0xC6:
            std::cout << "Tonkinhouse" << std::endl;
            break;
        case 0xC8:
            std::cout << "Koei" << std::endl;
            break;
        case 0xC9:
            std::cout << "UFL" << std::endl;
            break;
        case 0xCA:
            std::cout << "Ultra" << std::endl;
            break;
        case 0xCB:
            std::cout << "Vap" << std::endl;
            break;
        case 0xCC:
            std::cout << "Use Corporation" << std::endl;
            break;
        case 0xCD:
            std::cout << "Meldac" << std::endl;
            break;
        case 0xCE:
            std::cout << ".Pony Canyon or" << std::endl;
            break;
        case 0xCF:
            std::cout << "Angel" << std::endl;
            break;
        case 0xD0:
            std::cout << "Taito" << std::endl;
            break;
        case 0xD1:
            std::cout << "Sofel" << std::endl;
            break;
        case 0xD2:
            std::cout << "Quest" << std::endl;
            break;
        case 0xD3:
            std::cout << "Sigma Enterprises" << std::endl;
            break;
        case 0xD4:
            std::cout << "ASK Kodansha Co." << std::endl;
            break;
        case 0xD6:
            std::cout << "Naxat Soft" << std::endl;
            break;
        case 0xD7:
            std::cout << "Copya System" << std::endl;
            break;
        case 0xD9:
            std::cout << "Banpresto" << std::endl;
            break;
        case 0xDA:
            std::cout << "Tomy" << std::endl;
            break;
        case 0xDB:
            std::cout << "LJN" << std::endl;
            break;
        case 0xDD:
            std::cout << "NCS" << std::endl;
            break;
        case 0xDE:
            std::cout << "Human" << std::endl;
            break;
        case 0xDF:
            std::cout << "Altron" << std::endl;
            break;
        case 0xE0:
            std::cout << "Jaleco" << std::endl;
            break;
        case 0xE1:
            std::cout << "Towa Chiki" << std::endl;
            break;
        case 0xE2:
            std::cout << "Yutaka" << std::endl;
            break;
        case 0xE3:
            std::cout << "Varie" << std::endl;
            break;
        case 0xE5:
            std::cout << "Epoch" << std::endl;
            break;
        case 0xE7:
            std::cout << "Athena" << std::endl;
            break;
        case 0xE8:
            std::cout << "Asmik ACE Entertainment" << std::endl;
            break;
        case 0xE9:
            std::cout << "Natsume" << std::endl;
            break;
        case 0xEA:
            std::cout << "King Records" << std::endl;
            break;
        case 0xEB:
            std::cout << "Atlus" << std::endl;
            break;
        case 0xEC:
            std::cout << "Epic/Sony Records" << std::endl;
            break;
        case 0xEE:
            std::cout << "IGS" << std::endl;
            break;
        case 0xF0:
            std::cout <<"A Wave" << std::endl;
            break;
        case 0xF3:
            std::cout << "Extreme Entertainment" << std::endl;
            break;
        case 0xFF:
            std::cout << "LJN" << std::endl;
            break;
        default:
            std::cout << "Unknown" << std::endl;
    }
    
//    std::cout << "New Licensee Code: $";    
//    for (const auto& element : header.newLicenseeCode) {
//        std::cout << static_cast<char>(element) << " ";
//    }
//    std::cout << std::endl;

    std::cout << "Cartridge Type: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.MBCCode) << std::dec << std::endl;
    std::cout << "ROM Size: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.ROMSize) << std::dec << std::endl;
    std::cout << "RAM Size: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.RAMSize) << std::dec << std::endl;
    std::cout << "Destination Code: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.destinationCode) << std::dec << std::endl;
    std::cout << "Mask ROM Version Number: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.maskROMVersionNumber) << std::dec << std::endl;
    std::cout << "Header Checksum: $" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(header.headerChecksum) << std::dec << std::endl;

    std::cout << "Global Checksum: ";    
    for (const auto& element : header.globalChecksum) {
        std::cout << std::hex << std::setw(2) << static_cast<int>(element) << ' ';
    }
    std::cout << std::endl << std::dec;
}

bool ROM::loadHeader() {
    //Title Section and cout Example
    size_t startIndex = 0x0134;
    size_t endIndex = 0x0144;
    if (startIndex < fullROM.size() && endIndex <= fullROM.size() && startIndex < endIndex){}
    else{
        std::cout << "titleBuffer was unable to be grabbed.\n" << std::endl;
        return false;
    }
    std::vector<uint8_t> titleBuffer((fullROM.begin() + startIndex), (fullROM.begin() + endIndex));

    //Manufacturer Code
    startIndex = 0x013F;
    endIndex = 0x0143;
    if (startIndex < fullROM.size() && endIndex <= fullROM.size() && startIndex < endIndex){}
    else{
        std::cout << "manufacturerCodeBuffer was unable to be grabbed.\n" << std::endl;
        return false;
    }
    std::vector<uint8_t> manufacturerCodeBuffer((fullROM.begin() + startIndex), (fullROM.begin() + endIndex));
    
    //CGBFlag
    uint8_t CGBFlagBuffer = fullROM.at(0x0143);

    //New Licensee Code
    startIndex = 0x0144;
    endIndex = 0x0146;
    if (startIndex < fullROM.size() && endIndex <= fullROM.size() && startIndex < endIndex){}
    else{
        std::cout << "newLicenseeCodeBuffer was unable to be grabbed.\n" << std::endl;
        return false;
    }
    std::vector<uint8_t> newLicenseeCodeBuffer((fullROM.begin() + startIndex), (fullROM.begin() + endIndex));

    //SGBFlag and Print Example
    uint8_t SGBFlagBuffer = fullROM.at(0x0146);
    //std::cout << "SGBFlagBuffer: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(SGBFlagBuffer) << std::dec << std::endl;

    // MBC Type
    uint8_t MBCCode = fullROM.at(0x0147);

    //ROM Size Designation
    uint8_t ROMSizeBuffer = fullROM.at(0x0148);

    //RAM Size Designation
    uint8_t RAMSizeBuffer = fullROM.at(0x0149);

    //Destination Code
    uint8_t destinationCodeBuffer = fullROM.at(0x014A);

    //Old Licensee Code
    uint8_t oldLicenseeCodeBuffer = fullROM.at(0x014B);

    //Mask ROM Version Number
    uint8_t maskROMVersionNumberBuffer = fullROM.at(0x014C);

    //Header Checksum
    uint8_t headerChecksumBuffer = fullROM.at(0x014D);

    //Global Checksum
    startIndex = 0x014E;
    endIndex = 0x0150;
    if (startIndex < fullROM.size() && endIndex <= fullROM.size() && startIndex < endIndex){}
    else{
        std::cout << "globalChecksumBuffer was unable to be grabbed.\n" << std::endl;
        return false;
    }
    std::vector<uint8_t> globalChecksumBuffer((fullROM.begin() + startIndex), (fullROM.begin() + endIndex));

    header.title = titleBuffer;
    header.manufacturerCode = manufacturerCodeBuffer;
    header.CGBFlag = CGBFlagBuffer;
    header.newLicenseeCode = newLicenseeCodeBuffer;
    header.SGBFlag = SGBFlagBuffer;
    header.MBCCode = MBCCode;
    header.ROMSize = ROMSizeBuffer;
    header.RAMSize = RAMSizeBuffer;
    header.destinationCode = destinationCodeBuffer;
    header.oldLicenseeCode = oldLicenseeCodeBuffer;
    header.maskROMVersionNumber = maskROMVersionNumberBuffer;
    header.headerChecksum = headerChecksumBuffer;
    header.globalChecksum = globalChecksumBuffer;


    return true;
}

uint8_t ROM::getMBC() {
    return header.MBCCode;
}

std::vector<uint8_t> ROM::loadROMSegment(uint16_t dataStart, uint16_t dataFinish){
    uint16_t value = dataFinish - dataStart;
    std::vector<uint8_t> buffer(static_cast<long>(value));
    uint16_t j = 0x0000; 
    for (uint16_t i = dataStart; i < dataFinish; i++){
        buffer[j] = fullROM[i];
        j++;
    }

    return buffer;
}

uint8_t ROM::retROMSize() {
    return header.ROMSize;
}