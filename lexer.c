/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 17:37:16 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/17 19:45:09 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** automate de reconnaissance des char du shell
** gere pas les options (-lar) et args des cdes (gere ds arbre)
** mettre les elements dans t_token arr[] ou liste chainee 
*/

#include <stdio.h>
#include <stdlib.h>

#define CDE			0
#define	RED_IN_S	1

typedef enum
{
	cmd, red_in_s, red_in_d, red_out_s, red_out_d, pipe, semicolon, zwait
}	e_states;

typedef struct	s_token
{
	int			type; // un type par obj ou regroupement ? 
	char		*value;
}				t_token;

void	error(int code)
{
	printf("error %d\n", code);
	exit(0);
}

int		is_alpha(char c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	return (0);
}

void	clr_str(char *str, int sz)
{
	int		i;

	i = 0;
	while (i < sz)
	{
		str[i] = '\0';
		i++;
	}
}

int		main (int ac, char **av)
{
	int			i;
	int			j;
//	e_states	arr[8][6];
	e_states	state;
	char		word[256];

	state = zwait;
	i = 0;
	j = 0;
	while (av[1][i] != '\0')
	{
		switch (state)
		{
			case cmd:
				if (is_alpha(av[1][i]) == 1)
				{
					word[j] = av[1][i];
					j++;
				}
				else
				{
					if (av[1][i] == ' ')
						state = zwait;
					else
						if (av[1][i] == ';')
							state = semicolon;
						else
							error(0);
				}
			break;

			case red_in_s:
				if (av[1][i] != ' ' && av[1][i] != '<')
					error(1);
				else
				{
					if (av[1][i] == ' ')
					{
						printf("<\n");
						state = zwait;
					}
					if (av[1][i] == '<')
						state = red_in_d;
				}
			break;

			case red_in_d:
				if (av[1][i] != ' ')
					error(2);
				else
				{
					state = zwait;
					printf("<<\n");
				}
			break;

			case red_out_s:
				if (av[1][i] != ' ' && av[1][i] != '>')
					error(3);
				else
				{
					if (av[1][i] == ' ')
					{
						state = zwait;
						printf(">\n");
					}
					if (av[1][i] == '>')
						state = red_out_d;
				}
			break;

			case red_out_d:
				if (av[1][i] != ' ')
					error(4);
				else
				{
					state = zwait;
					printf(">>\n");
				}
			break;

			case pipe:
				printf("| %s\n", word);
				if (av[1][i] == ' ')
					state = zwait;
				else
					error(5);
			break;

			case semicolon:
				printf("; %s\n", word);
				if (av[1][i] == ' ')
					state = zwait;
				else
					error(6);
			break;

			case zwait:
				if (av[1][i] != ' ')
				{
					if (word[0] != '\0')
						printf("%s\n", word);
					clr_str(word, 200);
					word[0] = '\0';
					j = 0;
				}
				if (is_alpha(av[1][i]))
				{
					state = cmd;
					word[j] = av[1][i];
					j++;
				}
				if (av[1][i] == '<')
					state = red_in_s;
				if (av[1][i] == '>')
					state = red_out_s;
				if (av[1][i] == '|')
					state = pipe;
				if (av[1][i] == ';')
					state = semicolon;
			break;

		}
		i++;
	}
	return (0);
}
