/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/17 15:08:42 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/17 17:25:46 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_tree
{
	int				content;
	struct s_tree	*left_child;
	struct s_tree	*right_child;
}				t_tree;

int	g_lvl = 0;

t_tree	*build_tree(t_tree *tree, int nb)
{
	t_tree	*new;

	new = (t_tree *) malloc(sizeof(t_tree));
	if (tree == NULL)
	{
		tree = new;
		tree->content = nb;
		tree->left_child = NULL;
		tree->right_child = NULL;
	}
	else
	{
		if (tree->content > nb )
			tree->left_child = build_tree(tree->left_child, nb);
		else
			tree->right_child = build_tree(tree->right_child, nb);
	}
	return (tree);
}

void	display(t_tree *t)
{
	if (t != NULL)
	{
		display(t->left_child);
		printf("%d\n", t->content);
		display(t->right_child);
	}
}

void	search_tree(t_tree *t, int nb)
{
	if (t != NULL)
	{
		search_tree(t->left_child, nb);
		if (t->content == nb)
		{
			printf("Element present\n");
			return ;
		}
		search_tree(t->right_child, nb);
	}
}

int		main()
{
	t_tree	*tree;
	int		nb;

	tree = NULL;
	tree = build_tree(tree, 8);
	tree = build_tree(tree, 0);
	tree = build_tree(tree, 5);
	tree = build_tree(tree, 11);
	tree = build_tree(tree, 13);
	tree = build_tree(tree, 42);
	tree = build_tree(tree, 66);
	tree = build_tree(tree, 5);
	tree = build_tree(tree, 2);
	tree = build_tree(tree, 3);
	printf("===============\n");
	display(tree);
	printf("===============\n");
	printf("Entrer un nombre : \n");
	scanf("%d", &nb);
	search_tree(tree, nb);
	printf("===============\n");
	return (0);
}
