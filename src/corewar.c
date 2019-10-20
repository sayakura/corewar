#include "core.h"

void    cw_dump()
{
    int         i;
    unsigned    siz;

    i = 0;
    siz = (unsigned)sqrt(MEM_SIZE);
    while (i < MEM_SIZE)
    {
        if (i % siz == 0)
        {
            if (i)
                printf("\n");
            printf("%#06x : ", i);
        }
        fflush(stdout);
        h_puthex(MEM[i]);
        printf(" ");
        i++;
    }
    printf("\n");
    exit(1);
}

void    cw_start()
{
    while (true)
    {
        ++CORE.cycle;
        if (CORE.cycle > CORE.dump_cycle)
            cw_dump();
        p_process_loop();
        // if (CORE.cycle >= CORE.kill_cycle)
        //     printf("kill them all!\n");
        if (!CORE.nprocess)
            printf("some one gotta win!\n");
    }
}