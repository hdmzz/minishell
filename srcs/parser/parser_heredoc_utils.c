/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:22:48 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/14 16:21:52 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substitute_input_wth_output(char *input, char *cmd_output)
{
	char	**tab;
	char	**tmp;
	char	*new_input;
	int		i;

	tab = ft_split(input, '$');
	tmp = tab;
	if (!tab || !cmd_output)
	{
		ft_free_split(tab);
		return ("Error substitute_input_wth_output");
	}
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '(')
		{
			tmp[i] = ft_free_ptr(tmp[i]);
			tmp[i] = cmd_output;
		}
		i++;
	}
	new_input = recompose_input(tmp, 0, -1);
	return (new_input);
}

char	*handle_imbricated_cmd(char *input, t_cmd *c)
{
	char	*inp;
	char	*imbrecated_cmd;
	char	*cmd_output;
	int		i;
	int		y;

	i = -1;
	inp = input;
	while (inp[++i] != '\0')
	{
		if (inp[i] == '$' )
		{
			y = input_into_parenthesis(input, &i);
			if (y > i)
			{
				imbrecated_cmd = ft_substr(input, i, y - i);
				cmd_output = exec_imbricated_cmd(imbrecated_cmd, c->g_shell);
				if (cmd_output)
					inp = substitute_input_wth_output(input, cmd_output);
				imbrecated_cmd = ft_free_ptr(imbrecated_cmd);
				input = ft_free_ptr(input);
			}
		}
	}
	return (inp);
}

char	**tab_expanded(char **tab, t_cmd *c)
{
	int		i;
	char	*buff;

	i = -1;
	buff = NULL;
	while (tab[++i])
	{
		if (tab[i] && tab[i][0] == '$')
		{
			if (tab[i + 1][0] == '(' || is_valid_var_hd(tab[i + 1]) == false)
				continue ;
			buff = tab[i + 1];
			tab[i + 1] = var_xpanser(tab[i + 1], c->g_shell);
			buff = ft_free_ptr(buff);
			tab = replace_tab_hd(tab, i);
		}
	}
	return (tab);
}

void	concat_tab_heredoc(char **new_input, char **tab, int i, int total_len)
{
	i = -1;
	while (tab[++i])
	{
		if (tab[i][0] != '$')
			ft_strlcat(*new_input, tab[i], total_len + 1);
		if (tab[i][0] == '$' && tab[i + 1][0] == '(')
			ft_strlcat(*new_input, tab[i], total_len + 1);
		if (tab[i][0] == '$' && is_valid_var_hd(tab[i + 1]) == false)
			ft_strlcat(*new_input, tab[i], total_len + 1);
	}
}

char	*recompose_input(char **tab, int total_len, int i)
{
	char	*new_input;

	while (tab[++i])
		total_len += ft_strlen(tab[i]);
	total_len += i - 1;
	new_input = ft_calloc(total_len + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	concat_tab_heredoc(&new_input, tab, i, total_len);
	ft_free_split(tab);
	return (new_input);
}
