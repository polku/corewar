/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parrrser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 14:25:14 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/22 16:12:47 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum	e_sym
{
	HD_NAME, // == ".name" et pas regle name
	HD_CMT, // idem au dessus
	LABEL, // cf ident number
	REG,
	DIR,
	IND,
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF,
	SEP_CHR,
	DIR_CHR,
	LAB_CHR,
	CMT_CHR,
	NEWLINE,
}				e_sym;

typedef enum	e_bool
{
	FALSE = 0,
	TRUE = 1
}				e_bool;

void	get_sym()
{
	//lire liste
}

e_sym	g_sym;

void	build_tree()
{
}

void	error()
{
	printf("error\n");
	exit(0);
}

e_bool	accept(e_sym s)
{
	if (g_sym == s)
	{
		get_sym();
		return (TRUE);
	}
	return (FALSE);
}

void	expect(e_sym s)
{
	if (accept(s))
		return ;
	else
		error();
}

e_bool	op_live()
{
	if (accept(OP_LIVE))
	{
		if (expect(DIR))
		{
			expect(NEWLINE);
			build_tree();
			return (TRUE);
		}
	}
	return (FALSE);
}

e_bool	op_ld()
{
	if (accept(OP_LD))
	{
		if (accept(DIR) || accept(IND))
		{
			expect(SEP_CHR);
			expect(REG);
			expect(NEWLINE);
			return (TRUE);
		}
		else
			error();
	}
	return (FALSE);
}

e_bool	op_st()
{
	if (accept(OP_ST))
	{
		expect(REG);
		expect(SEP);
		if (accept(IND) || accept(REG))
		{
			expect(NEWLINE);
			return (TRUE);
		}
	}
	return (FALSE);
}

e_bool	op_add()
{
	if (accept(OP_ADD))
	{
		expect(REG);
		expect(SEP);
		expect(REG);
		expect(SEP);
		expect(REG);
		expect(NEWLINE);
		return (TRUE);
	}
	return (FALSE);
}

e_bool	op_sub()
{
	if (accept(OP_SUB))
	{
		expect(REG);
		expect(SEP);
		expect(REG);
		expect(SEP);
		expect(REG);
		expect(NEWLINE);
		return (TRUE);
	}
	return (FALSE);
}

e_bool	op_and()
{
	if (accept(OP_AND))
	{
		if (accept(REG) || accept(DIR) || accept(IND))
		{
			expect(SEP);
			if (accept(REG) || accept(DIR) || accept(IND))
			{
				expect(SEP);
				expect(REG);
				expect(NEWLINE);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

e_bool	instruction()
{
	if (op_live() || op_ld() || op_st() || ...)
	{
		//expect(NEWLINE);
	}
}

e_bool	label()
{

}

e_bool	code()
{
	while ()
	{
		if (accept(LABEL))
		{
			continue ;
		}
		if (accept(COMMENT))
		{
		}
		if (instruction)
		{
		}
	}
}

e_bool	header()
{
	expect(HD_NAME);
	expect(HD_CMT);
	return (TRUE);
}

e_bool	program()
{
	header();
	code();
	return (TRUE);
}
