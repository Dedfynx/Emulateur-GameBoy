#include "Emu.hpp"

namespace DedOs
{
    Emu::Emu(std::string romPath)
    {
        setup(romPath);
        run();
    }
    Emu::~Emu()
    {
    }

    void Emu::setup(std::string romPath)
    {
        std::cout << "Setup ..." << std::endl;
        cartouche = std::make_shared<Cartouche>();
        if (!cartouche->load(romPath.c_str()))
        {
            std::cout << "Probleme chargement cartouche" << std::endl;
            std::exit(0);
        };
        bus.loadCartouche(cartouche);

        SDL_Init(SDL_INIT_VIDEO);
        std::cout << "SDL Init" << std::endl;
    }
    void Emu::run()
    {
        std::cout << "Run ..." << std::endl;
        while (bus.cpu.isRunning())
        {
            if (!bus.cpu.step())
            {
                std::cout << "CPU Arrété" << std::endl;
                std::exit(0);
            }
            
        }

        /* SDL_Window *window = SDL_CreateWindow(
            "EmuGB",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0);

        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000);

        SDL_DestroyWindow(window);
        SDL_Quit(); */
    }
}