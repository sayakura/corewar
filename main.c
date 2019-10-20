#include "core.h"

void    load_champ(uint32_t id, char *filename, bool assign)
{
    int     fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Can't read source file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    ch_load_champ(fd, id, assign);
}

void    read_args(int ac, char **av)
{
    int32_t         i;

    i = 0;
    while (av[++i])
    {
        if (!strcmp("-v", av[i]))
            CORE.flags |= F_VERBOSE;
        else if (!strcmp("-d", av[i]))
        {
            if (i + 1 < ac)
                CORE.dump_cycle = (uint32_t)atoi(av[i + 1]);
            else
                FATAL("Can't read source file -d");
            i++;
        }
        else if (!strcmp("-n", av[i]))
        {
            if (i + 1 < ac)
                load_champ(atoi(av[i + 1]), av[i + 2], true);
            i += 2;
        }
        else
            load_champ(0, av[i], false);
    }
}

int     main(int ac, char **av)
{
    read_args(ac, av);
    ch_champ_intro();
    //load_champs(ac, av, fds);
    return (0);
}