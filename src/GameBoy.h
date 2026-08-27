#pragma once
#include <cstdint>
#include "Memory/ROM.h"
#include "Memory/MBC.h"
#include "DMG-CPU/SM83.h"
#include <SDL2/SDL.h>

class GameBoy {
    
    public:
        static const uint64_t CYCLES_PER_FRAME = 70224; // Approximate cycles per frame (1 frame = 1/60 seconds)
        static constexpr double TARGET_FPS = 60.0;

        GameBoy(ROM &Game);
        void run(SDL_Event& event);
    private:
        ROM GBGame;
        MBC GBMemory;
        SM83 CPU;
        uint64_t totalCycles;

        void handleInterrupts();
};