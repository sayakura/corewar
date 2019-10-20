/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <qpeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:02:14 by qpeng             #+#    #+#             */
/*   Updated: 2019/08/04 15:42:31 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_champ *ch_search_champion(int32_t id)
{
    uint32_t     i;

    i = 0;
    while (i < CORE.nplayers)
    {
        if (CORE.champions[i].id == id)
            return (&CORE.champions[i]);    
        i++;
    }
    return (NULL);
}

void    ch_parse_champ_header(t_hdr *hdr, int fd)
{
    off_t   siz;

    if (fd < 0)
        return ;
    if ((siz = lseek(fd, 0, SEEK_END)) == -1)
        PERROR("lseek");
    if ((size_t)siz < sizeof(t_hdr))
        FATAL("Invalid header size\n");
    if (lseek(fd, 0, SEEK_SET) == -1)
        PERROR("lseek");
    if (read(fd, hdr, sizeof(t_hdr)) != sizeof(t_hdr))
        PERROR("read");
    h_rev_bytes(&hdr->magic, sizeof(hdr->magic));
	if (hdr->magic != COREWAR_EXEC_MAGIC)
	{
        printf("%x %x\n", hdr->magic, COREWAR_EXEC_MAGIC);
        FATAL("Invalid header\n");
    }
    h_rev_bytes(&hdr->prog_size, sizeof(hdr->prog_size));
	if (hdr->prog_size != siz - sizeof(t_hdr))
        FATAL("Invalid header\n");
	if (hdr->prog_size > CHAMP_MAX_SIZE)
	{
        printf("%d %d\n", hdr->prog_size, CHAMP_MAX_SIZE);
        FATAL("Champion too large\n");
    }
}

void    ch_champ_intro()
{
    uint8_t     idx;
    t_champ     *champ;

    idx = 0;
    while (idx < CORE.nplayers)
    {
        champ = &CORE.champions[idx];
        LOG("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",  champ->id
            < 0 ? -champ->id : champ->id , 
            champ->prog_size, champ->name, champ->comment);
        idx++;
    }
}

void    ch_load_champ(int fd, uint32_t id, bool assign)
{
    t_hdr               hdr;
    t_champ             *champ;
    static int32_t      index;
    static int32_t       aid;
    uint8_t             *pc;

    ch_parse_champ_header(&hdr, fd);
    CORE.nplayers++;
    champ = &(CORE.champions[index]);
	bzero(champ, sizeof(t_champ));
    memcpy(champ->name, hdr.prog_name, PROG_NAME_LENGTH);
	memcpy(champ->comment, hdr.comment, COMMENT_LENGTH);
    champ->id = assign ? id : --aid;
    champ->prog_size = hdr.prog_size;
	pc = &MEM[(MEM_SIZE / CORE.nplayers) * index];
	if (read(fd, pc, hdr.prog_size) != hdr.prog_size)
		PERROR("read");
    p_fork(pc, champ->id, true);
    index++;
    close(fd);
}