/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:22:48 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/13 17:08:37 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab_expanded(char **tab, t_cmd *c)
{
	int		i;
	char	*buff;

	i = 0;
	buff = NULL;
	while (tab[i])
	{
		if (tab[i] && tab[i][0] == '$')
		{
			buff = tab[i + 1];
			if (buff && ft_strspn(buff, \
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_") \
			!= ft_strlen(buff))
				continue ;
			tab[i + 1] = var_xpanser(tab[i + 1], c->g_shell);
			buff = ft_free_ptr(buff);
		}
		i++;
	}
	return (tab);
}
//total_len = 0, i = -1, tab_len = 0
//tab aura ete expanse, il faut juste skip les $ restant
char	*recompose_input(char **tab, int total_len, int tab_len, int i)
{
	char	*new_input;

	while (tab[++i])
		total_len += ft_strlen(tab[i]);
	tab_len = i;
	total_len += i - 1;
	new_input = ft_calloc(total_len + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '$')
		{
			ft_strlcat(new_input, tab[i], total_len + 1);
			if (i < tab_len - 1)
				ft_strlcat(new_input, " ", total_len + 1);
		}
		i++;
	}
	ft_free_split(tab);
	return (new_input);
}

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
	new_input = recompose_input(tmp, 0, 0, -1);
	return (new_input);
}

