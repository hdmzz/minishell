/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:20 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/19 15:29:23 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "typedef.h"
#include "minishell.h"

int	long_long_overflow(char *to_check)
{
	long long	nb;
	char		*str;
	int			ret;

	ret = 1;
	nb = ft_atoll(to_check);
	str = ft_lltoa(nb);
	if (ft_strcmp(str, to_check) == 0)
		ret = 0;
	free(str);
	return (ret);
}

int	check_exit_arg(char **tab)
{
	int	i;

	i = 0;
	if (!tab[1])
		return (0);
	while (tab[1][i])
	{
		if (!ft_isdigit(tab[1][i]))
			return (error_handler(tab[0], tab[1], \
			"numeric argument required", 2));
		i++;
	}
	if (long_long_overflow(tab[1]))
		return (error_handler(tab[0], tab[1], "numeric argument required", 2));
	else
		return (ft_atoi(tab[1]));
}

int	exit_cmd(t_cmd *c, t_shell *g_shell, int last_exit)
{
	int	tab_len;

	tab_len = split_lenght(c->cmd);
	if (tab_len > 1)
	{
		if (tab_len > 2)
		{
			error_handler(c->cmd[0], "too many arguments", NULL, 2);
			g_last_exit_code = 1;
			return (1);
		}
	}
	if (last_exit == 1)
		printf("exit\n");
	g_last_exit_code = check_exit_arg(c->cmd);
	ft_free_shell(g_shell, last_exit);
	rl_clear_history();
	exit(g_last_exit_code);
	return (1);
}

int	exit_builtin(t_shell *g_shell, int last_exit)
{
	if (last_exit == 1)
		printf("exit\n");
	ft_free_shell(g_shell, last_exit);
	rl_clear_history();
	exit(last_exit);
	return (1);
}
