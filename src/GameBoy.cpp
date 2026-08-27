#include "GameBoy.h"
#include "Memory/ROM.h"
#include "Memory/MBC.h"
#include "DMG-CPU/SM83.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

GameBoy::GameBoy(ROM &Game) {
    GBGame = ROM(Game);
    GBGame.interpretGameHeader();

    GBMemory = MBC();
    // Set MBank mode
    if (GBMemory.setMBCCode(GBGame.getMBC())){
        std::cout << "MBC Set: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(GBGame.getMBC()) << std::dec << std::endl;
    }
    else {
        std::cout << "Game not supported yet, stay tuned!  MBC: " << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(GBGame.getMBC()) << std::dec  << std::endl;
        std::cin;
        exit(4);
    }

    // Load ROM into Memory
    GBMemory.writeROMSegmenttoRAM(GBGame.loadROMSegment(0x0000,GBGame.retROMSize())); // MBC Mode 0 for now
    //init CPU
    CPU = SM83(GBMemory);
    totalCycles = 0;
}

void GameBoy::run(SDL_Event& event) {
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (true) {
        handleInterrupts();

        while (totalCycles < CYCLES_PER_FRAME) {
            int cyclesTaken = CPU.executeOpcode(GBMemory);
            totalCycles += cyclesTaken;
        }

        totalCycles = 0;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) 
                return;
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime).count();
        if (elapsed < 1000.0 / TARGET_FPS) {
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(1000.0 / TARGET_FPS - elapsed)));
        }
        lastFrameTime = currentTime;
    }

}

void GameBoy::handleInterrupts() {

}