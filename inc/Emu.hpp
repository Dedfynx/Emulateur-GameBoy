#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <iostream>
#include <string>

#include "Bus.hpp"
#include "Cartouche.hpp"

namespace dedOs
{
    class Emu
    {
    public:
        Emu(std::string romPath);
        ~Emu();

        void setup(std::string romPath);
        void run();
    private:
        std::shared_ptr<Cartouche> cartouche;
        Bus bus;
    };
}