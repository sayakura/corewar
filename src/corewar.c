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

void    cw_kill()
{
    t_process   *cur;
    t_process   *prev;

    cur = CORE.process;
    while (cur && CORE.cycle - cur->last_live > CORE.cycle_to_die)
    {
        printf("killed %u at %u\n",cur->champ_id, CORE.cycle);
        CORE.process = cur->next;
        CORE.nprocess--;
        free(cur);
        cur = CORE.process;
    }
    prev = cur;
    cur = prev ? prev->next : NULL;
    while (cur)
    {
        if (CORE.cycle - cur->last_live > CORE.cycle_to_die)
        {
            printf("killed %u at %u\n",cur->champ_id, CORE.cycle);
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
            CORE.nprocess--;
        }
        else
            cur = cur->next;
    }
    if (++CORE.checks >= MAX_CHECKS || CORE.nbr_live_called > NBR_LIVE)
    {
        if (CORE.cycle_to_die > CYCLE_DELTA)
            CORE.cycle_to_die -= CYCLE_DELTA;
        else
            CORE.cycle_to_die = 0;
        CORE.nbr_live_called = 0;
        CORE.checks = 0;
        CORE.kill_cycle = CORE.cycle + CORE.cycle_to_die;
    }
}

void    cw_start()
{
    CORE.kill_cycle = CYCLE_TO_DIE;
    CORE.cycle_to_die = CYCLE_TO_DIE;
    CORE.nbr_live_called = 0;
    CORE.checks = 0;
    while (true)
    {
        ++CORE.cycle;
        if (CORE.cycle > CORE.dump_cycle)
            cw_dump();
        p_process_loop();
        if (CORE.cycle >= CORE.kill_cycle)
            cw_kill();
        if (!CORE.nprocess)
        {
            printf("someone won at %d!\n", CORE.cycle);
            exit(0);
        }
    }
}