/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/13 19:22:38 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/23 18:09:12 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "filler.h"
#include "libft.h"

void	print_solution(t_coord cd)
{
	ft_putnbr_fd(cd.x, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(cd.y, 1);
}

int			find_case(t_piece *pc, t_coord cd)
{
	int		res;

	res = cd.y * pc->width + cd.x;
	return (res);
}

t_coord		find_coord(t_piece *pc, int nb)
{
	t_coord cd;

	cd.x = nb % pc->width;
	cd.y = nb % pc->width;
	return (cd);
}

int		find_solution(t_piece *map, t_piece *pc, char symb)
{
	int		i;
	int		j;
	int		k;
	int		nb;
	char	symb_adv;

	i =	0;
	nb = 0;
	symb_adv = (symb == 'o' ? 'x' : 'o');
	while (i < map->heigth * map->width)
	{
		j = 0;
		k = i;
		while (j < pc->width * pc->heigth)
		{
			if (pc->descr[j] == '.')
			{
				k++; //
				j++;
			}
			else if (pc->descr[j] == '*' && (map->descr[k] == '.' || map->descr[k] == symb - 32))
			{
				k++; //
				j++;
			}
			else if (pc->descr[j] == '*' && (map->descr[k] == symb_adv || map->descr[k] == symb_adv - 32))
			{
				break ;
			}
			else
			{
				nb++;
				if (nb > 1)
					break ;
			}
		}
		ft_putnbr_fd(j, 2);
		ft_putstr_fd(" ", 2);
		if (j == pc->width * pc->heigth) // emplacement bon
			return (i);
		i++;
	}
	return (-1);
}

void	corr_str(char *s)
{
	while (ft_isdigit(*s) == 1)
		s++;
	*s = '\0';
}

int		main()
{
	char	*line;
	int		i;
	int     fd;
	char	symb;
	t_piece	map;
	t_piece piece;
	char	**split;
	int		ln_num;
	int		j;
	int		solution;

	line = (char *) malloc(2048);
	fd = open("./output", O_CREAT | O_TRUNC | O_WRONLY, 0644);

//	while (1)
//	{
/* Recup map */
		ft_get_next_line(0, &line); // $$$ exec
		symb = (*(line + 10) == '1' ? 'o' : 'x');
		ft_get_next_line(0, &line); // Plateau 20 40
		split = ft_strsplit(line, ' ');
		corr_str(split[2]);
		map.heigth = ft_atoi(split[1]);
		map.width = ft_atoi(split[2]);
		map.descr = (char *) malloc(sizeof(char) * map.heigth * map.width);
		ln_num = 4;
		ft_free_arr(split);
		i = 0;
		while (ft_get_next_line(0, &line) && i < map.heigth + 1)
		{
			if (i > 0)
			{
				if (i == 1001 || i == 10001) // taille max ?
					ln_num++;
				j = 0;
				while (line[j] != '\0')
				{
					map.descr[i * map.width + j] = line[j + ln_num];
					j++;
				}
			}
			i++;
		}
/* Recup piece */
		split = ft_strsplit(line, ' ');
		corr_str(split[2]);
		piece.heigth = ft_atoi(split[1]);
		piece.width = ft_atoi(split[2]);
		piece.descr = (char *) malloc(sizeof(char) * piece.heigth * piece.width);
		ft_free_arr(split);
		while (ft_get_next_line(0, &line) && i < piece.heigth + 1)
		{
			j = 0;
			while (line[j] != '\0')
			{
				piece.descr[i * piece.width + j] = line[j];
				j++;
			}
			i++;
		}
/*********/
		solution = find_solution(&map, &piece, symb);
		print_solution(find_coord(&map, solution));
		free(map.descr);
		free(piece.descr);
//	}
	free(line);
	return (0);
}
