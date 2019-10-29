#include "core.h"

void    movri(uint8_t vala, uint8_t valb)
{
    REG[REG[vala]] = REG[valb];
}

void    movrr()
{
    REG[REG[RDI]] = REG[REG[RSI]];
}

void    movrm()
{

}

void    movmr()
{

}

void    movlmr()
{
    
}
