/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:07:12 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/22 13:23:47 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, int type, int pos)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *to_add)
{
	t_token	*start;

	start = *lst;
	if (start == NULL)
	{
		*lst = to_add;
		return ;
	}
	if (lst && *lst && to_add)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = to_add;
	}
}

/*
	this is where we calaculate the size of each token
	the idea is to use th strchr function for each chararcter of input
	sarch an occucrence in the string composed of all the metacharcter, control
	operators, and words
*/
int	token_len(char *input)
{
	int	len;

	len = 0 ;
	if (ft_strchr("><\t\n |$\\\"\'", input[len]))
	{
		if (ft_strncmp("<<", input, 2) || ft_strncmp(">>", input, 2))
			len = 2;
		else
			len = 1;
	}
	else
	{
		while (!ft_strchr("><\t\n |$\\\"\'", input[len]))
			len ++;
	}
	return (len);
}

int	get_token_type(char *str)
{
	int	i;
	static t_token_trslte	tok_type[] = {
	{"\n", new_line, "new_line"},
	{" ", white_space, "white_space"},
	{"\t", white_space, "white_space"},
	{"|", pipeline, "pipeline"},
	{"\'", single_quote, "single_quote"},
	{"\"", double_quote, "double_quote"},
	{"<", simple_redir_left, "simple_redir_left"},
	{">", simple_redir_right, "simple_redir_right"},
	{"<<", double_redir_left, "double_redir_left"},
	{">>", double_redir_right, "double_redir_right"},
	{"$", dollar, "dollar"},
	{NULL, -1, NULL}
	};

	i = -1;
	while (tok_type[++i].type != -1)
		if (!ft_strcmp(tok_type[i].value, str))
			return (tok_type[i].type);
	return (0);
}

/*
	this function calculates the token size
	ten malloc the size of the token and add it to the list
	in arguments
*/
int	create_token(t_token **lst, char *input, int *pos)
{
	char	*value;
	int		token_size;
	int		type;
	t_token	*new;

	token_size = token_len(input);//ici on a la longeur de ce que l'on va mettre ds la value
	value = ft_strndup(input, token_size);
	if (token_size == 0 || !value)
		return (0);
	type = get_token_type(value);
	if (!type)
		type = literal;
	new = new_token(value, type, *pos);
	if (!new)
		return(free(value), 0);
	token_add_back(lst, new);
}

/*
*	The function recovers the command then for each
*	create a token with the value and the token type
*/
t_token	*lexer(t_shell *g_shell)
{
	int		i;
	t_token	*token;
	char	*input;

	token = NULL;
	i = 0;
	input = g_shell->start_buff;
	if (!input)
		return (NULL);
	while (*input)
	{
		if (!create_token(&token, input, &i))
		{
			//free token list etc
			exit(EXIT_FAILURE);
		}
	}
}
