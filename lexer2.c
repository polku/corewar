/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 17:37:16 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/18 13:29:55 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** automate de reconnaissance des char du shell
** gere pas les options (-lar) et args des cdes (gere ds arbre)
** mettre les elements dans t_token arr[] ou liste chainee 
*/

#include <stdio.h>
#include <stdlib.h>

#define	NB_STATES	8

typedef enum	e_state
{
	cmd			= 0,
	red_in_s	= 1,
	red_in_d	= 2,
	red_out_s	= 3,
	red_out_d	= 4,
	pipe		= 5,
	semicolon	= 6,
	zwait		= 7
}				e_state;

typedef struct	s_token
{
	int			type;
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

void	case_cmd(char c, char *word, int *j, e_state *state)
{
	if (is_alpha(c) == 1)
	{
		word[*j] = c;
		(*j)++;
	}
	else
	{
		if (c == ' ')
			*state = zwait;
		else
			if (c == ';')
				*state = semicolon;
			else
				error(0);
	}
}

void	case_red_in_s(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	if (c != ' ' && c != '<')
		error(1);
	else
	{
		if (c == ' ')
		{
			printf("<\n");
			*state = zwait;
		}
		if (c == '<')
			*state = red_in_d;
	}
}

void	case_red_in_d(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	if (c != ' ')
		error(2);
	else
	{
		*state = zwait;
		printf("<<\n");
	}
}

void	case_red_out_s(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	if (c != ' ' && c != '>')
		error(3);
	else
	{
		if (c == ' ')
		{
			*state = zwait;
			printf(">\n");
		}
		if (c == '>')
			*state = red_out_d;
	}
}

void	case_red_out_d(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	if (c != ' ')
		error(4);
	else
	{
		*state = zwait;
		printf(">>\n");
	}
}

void	case_pipe(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	printf("|\n");
	if (c == ' ')
		*state = zwait;
	else
		error(5);
}

void	case_semicolon(char c, char *word, int *j, e_state *state)
{
	(void) j;
	(void) word;
	printf(";\n");
	if (c == ' ')
		*state = zwait;
	else
		error(6);
}

void	case_zwait(char c, char *word, int *j, e_state *state)
{
	if (c != ' ')
	{
		if (word[0] != '\0')
			printf("%s\n", word);
		clr_str(word, 200);
		word[0] = '\0';
		*j = 0;
	}
	if (is_alpha(c))
	{
		*state = cmd;
		word[*j] = c;
		(*j)++;
	}
	if (c == '<')
		*state = red_in_s;
	if (c == '>')
		*state = red_out_s;
	if (c == '|')
		*state = pipe;
	if (c == ';')
		*state = semicolon;
}

void	init_array(void (*arr[NB_STATES]))
{
	int		i;

	i = 0;
	arr[i++] = &case_cmd;
	arr[i++] = &case_red_in_s;
	arr[i++] = &case_red_in_d;
	arr[i++] = &case_red_out_s;
	arr[i++] = &case_red_out_d;
	arr[i++] = &case_pipe;
	arr[i++] = &case_semicolon;
	arr[i++] = &case_zwait;
}

int		main (int ac, char **av)
{
	int			i;
	int			j;
	e_state		state;
	char		word[256];
	void		(*arr[NB_STATES])(char, char *, int *, e_state *);

	state = zwait;
	i = 0;
	j = 0;
	init_array((void *) arr);
	if (ac == 2)
	{
		while (av[1][i] != '\0')
		{
			(*arr[state])(av[1][i], word, &j, &state);
			i++;
		}
	}
	return (0);
}
