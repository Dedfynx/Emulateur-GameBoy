#pragma once

#include <vector>
#include <string>

#include "Common.hpp"

namespace DedOs
{
    class Bus;
    /*
    Flags
	{
		A = (1 << 0),	// Unused
		B = (1 << 1),	// Unused
		C = (1 << 2),	// Unused
		D = (1 << 3),	// Unused
		C = (1 << 4),	// Carry flag
		H = (1 << 5),	// Half Carry
		N = (1 << 6),	// Substraction
		Z = (1 << 7),	// Zero
	};
    */

    struct Registre
    {
        uint8_t a;
        uint8_t f;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t h;
        uint8_t l;
        uint16_t sp;
        uint16_t pc;
    };

    class Cpu
    {

    public:
        Cpu();
        ~Cpu();

        bool step();
        void loadBus(Bus *b) { bus = b; };

        bool isHalted() { return halted; }
        bool isRunning() { return running; }

        uint8_t readRegIE();
        void setRegIE(uint8_t val);

    private:
        Registre regs;

#define CPU_FLAG_Z BIT(regs.f, 7)
#define CPU_FLAG_N BIT(regs.f, 6) //DAA only
#define CPU_FLAG_H BIT(regs.f, 5) //DAA only
#define CPU_FLAG_C BIT(regs.f, 4)

        void setFlags(uint8_t z, uint8_t n, uint8_t h, uint8_t c);

        uint16_t fetchData;
        uint16_t memDest;
        bool isMem;
        uint8_t cOpcode;

        Bus *bus = nullptr;

        bool halted;
        bool running;

        bool IME;
        uint8_t ieRegister;

        void fetch();
        void execute();
        void emuCycle(int nb);

        //Addressing Mode
        enum AddrMode
        {
            A_NONE,
            A_IMP,
            A_R,
            A_R_R,
            A_R_D8,
            A_R_D16,
            A_R_A8,
            A_R_A16,
            A_R_HLI,
            A_R_HLD,
            A_R_MR,
            A_D8,
            A_D16,
            A_D16_R,
            A_MR,
            A_MR_R,
            A_MR_D8,
            A_HLI_R,
            A_HLD_R,
            A_A8_R,
            A_A16_R,
            A_HL_SPR
        };
        //Register used
        enum RegType
        {
            R_NONE,
            //8 bits
            R_A,
            R_F,
            R_B,
            R_C,
            R_D,
            R_E,
            R_H,
            R_L,
            //16 bits
            R_AF,
            R_BC,
            R_DE,
            R_HL,
            R_SP,
            R_PC
        };

        enum CondType
        {
            CT_NONE,
            CT_NZ,
            CT_Z,
            CT_NC,
            CT_C
        };

        uint16_t readReg(RegType r);
        void setReg(RegType r, uint16_t val);

        //stack
        void push(uint8_t value);
        void push16(uint16_t value);
        uint8_t pop();
        uint16_t pop16();

        struct Instruction
        {
            std::string name;
            void (Cpu::*operate)(void) = nullptr;
            AddrMode aMode;
            RegType reg1;
            RegType reg2;
            CondType cond;
            uint8_t cycles = 0;
        };

        std::vector<Instruction> lookup;
        Instruction curInst;

        bool checkCondition();

        //Operation
    #pragma region Operation
        void procNone();
        void procNop();
        void procLd();
        void procJp();
        void procInc();
        void procDec();
        void procRlca();
        void procAdd();
        void procRrca();
        void procStop();
        void procRla();
        void procJr();
        void procRra();
        void procDaa();
        void procCpl();
        void procScf();
        void procCcf();
        void procHalt();
        void procAdc();
        void procSub();
        void procSbc();
        void procAnd();
        void procXor();
        void procOr();
        void procCp();
        void procPop();
        void procPush();
        void procRet();
        void procCb();
        void procCall();
        void procReti();
        void procLdh();
        void procJphl();
        void procDi();
        void procEi();
        void procRst();
        void procErr();

        void procRlc();
        void procRrc();
        void procRl();
        void procRr();
        void procSla();
        void procSra();
        void procSwap();
        void procSrl();
        void procBit();
        void procRes();
        void procSet();
    #pragma endregion Operation


    };
}
