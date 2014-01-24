/* cf presentation thor
	read_PIPE() remplacees par accept(t_tklist *lst)
*/

typedef enum	e_bool
{
	FALSE	= 0,
	TRUE	= 1
}				e_bool;

typedef enum	e_type
{
	WORD,
	REDIR_IN_S,
	REDIR_IN_D,
	REDIR_OUT_S,
	REDIR_OUT_D,
	PIPE,
	SEMICOLON
}				e_type;

typedef struct	s_tree
{
	e_type			type;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

e_bool	read_expr(t_tree *tree)
{

}

e_bool	read_semi_expr(t_tree *tree)
{
	t_tree	*new;

	new = (t_tree *) malloc(sizeof(t_tree));
	new->type = SEMICOLON;
	new->left = NULL;
	new->right = NULL;
	if (read_pipe_expr(new->left))
	{
		read_SEMICOLON(); // &&
		read_expr(new->right);
		build_tree(tree, new);
		return (TRUE);
	}
	free(new);
	return (FALSE);
}

e_bool	read_pipe_expr(t_tree *tree)
{
	t_tree	*new;

	new = (t_tree *) malloc(sizeof(t_tree));
	new->type = PIPE;
	new->left = NULL;
	new->right = NULL;
	if (read_redir_expr(new->left))
	{
		read_PIPE(); // &&
		read_pipe_expr(new->right);
		build_tree(tree, new);
		return (TRUE);
	}
	free(new);
	return (FALSE);
}

e_bool	read_redir_out_expr(t_tree *tree)
{
	t_tree	*new;

	new = (t_tree *) malloc(sizeof(t_tree));
	new->type = REDIR_IN_S;
	new->left = NULL;
	new->right = NULL;
	if (read_command(new->left))
	{
		read_REDIR_OUT_S(); // gere pas >>
		read_redir_expr(new->right);
		build_tree(tree, new);
		return (TRUE);
	}
	free(new);
	return (FALSE);
}

e_bool	read_command(t_tree)
{
	if (read_WORD())
		return (TRUE);
	else
		return (FALSE);
}

e_bool	read_command_arg(t_tree)
{
	if (read_WORD())
		return (TRUE);
	else
		return (FALSE);
}

void	parser(t_tklist *list)
{
	while (read_expr(list) == TRUE && list)
	{
		list = list->next;
	}

}
