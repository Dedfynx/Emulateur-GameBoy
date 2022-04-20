#include "Emu.hpp"

int main(int argv, char **args)
    {

        if(argv != 2){
            std::cout << "Usage : EmuGB.exe  rom_name" << std::endl;
            std::exit(0);
        }
        DedOs::Emu emu{args[1]};

        return 0;
    }
