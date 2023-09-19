/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/19 15:02:03 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(char **cmd, t_shell *g_shell)
{
	int	i;

	i = 0;
	if (split_lenght(cmd) > 1)
		return (EXIT_FAILURE);
	if (g_shell->split_env == NULL)
		return (EXIT_FAILURE);
	while (g_shell->split_env[i])
	{
		printf("%s\n", g_shell->split_env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_check_double(char *str, char **tab)
{
	int	i;

	i = 0;
	if (!tab || !str)
		return (0);
	while (tab[i])
	{
		if (ft_strcmp(str, tab[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	**ft_sort_tab(char **tab, int i)
{
	char	**new_tab;
	int		j;
	int		len;
	int		min_idx;

	len = split_lenght(tab);
	new_tab = ft_calloc(len + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	while (++i < len)
	{
		j = -1;
		min_idx = -1;
		while (tab[++j])
		{
			if (ft_check_double(tab[j], new_tab) == 1 && \
			(min_idx == -1 || ft_strcmp(tab[j], tab[min_idx]) < 0))
				min_idx = j;
		}
		if (min_idx != -1)
			new_tab[i] = ft_strdup(tab[min_idx]);
		else
			return (ft_free_split(new_tab), NULL);
	}
	return (new_tab);
}

int	ex_builtin(char **cmd, t_shell *g_shell)
{
	int		i;
	char	**new_tab;

	i = 0;
	if (split_lenght(cmd) > 1)
		return (EXIT_FAILURE);
	if (g_shell->split_env == NULL)
		return (EXIT_FAILURE);
	new_tab = ft_sort_tab(g_shell->split_env, -1);
	while (new_tab[i])
	{
		printf("declare -x %s\n", new_tab[i]);
		i++;
	}
	ft_free_split(new_tab);
	return (EXIT_SUCCESS);
}
