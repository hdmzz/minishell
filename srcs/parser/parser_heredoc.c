/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:20:05 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/14 10:43:13 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	delim_in_quotes(t_token *lst)
{
	int	delim_in_quotes;

	delim_in_quotes = 0;
	while (lst->type == white_space || lst->type == double_redir_left)
		lst = lst->next;
	if (lst->type == double_quote)
	{
		lst = lst->next;
		while (lst && lst->type != double_quote)
			lst = lst->next;
		if (lst && lst->type == double_quote)
			delim_in_quotes = 1;
	}
	return (delim_in_quotes);
}

int	heredoc_first_analyzer(t_shell *g_shell)
{
	t_token	*lst;

	lst = g_shell->list_token;
	while (lst)
	{
		if (lst->type == double_redir_left)
		{
			if (delim_in_quotes(lst))
				lst->hd_delim_into_quotes = 1;
		}
		lst = lst->next;
	}
	return (1);
}

int	input_into_parenthesis(char *input, int *i)
{
	int	y;

	y = 0;
	*i += 1;
	if (input[*i] == '(')
	{
		*i += 1;
		y = *i;
		while (input[y] && input[y] != ')')
			y++;
		if (!input[y])
			return (0);
		if (input[y] == ')')
			return (y);
	}
	return (0);
}

bool	is_valid_var_hd(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_hd_inp(char *input, t_cmd *c)
{
	char	*inp;
	int		i;
	int		y;

	i = -1;
	y = 0;
	inp = input;
	while (inp[++i] != '\0')
	{
		if (inp[i] == '$' && c->hd_delim_into_quotes == 0)
		{
			y = input_into_parenthesis(input, &i);
			if (y > i)
			{
				inp = heredoc_cmd_parser(input, c);
				if (inp == NULL)
					return (false);
			}
			else if (is_valid_var_hd(inp) == false)
				return (false);
		}
	}
	return (true);
}
