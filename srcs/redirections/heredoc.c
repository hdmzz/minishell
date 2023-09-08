/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/08 10:21:12 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		g_last_exit_code = 130;
		//rl_on_new_line();
		tputs("\n", 1, ft_putchar);
		rl_redisplay();
		rl_done = 1;
	}
}

int	heredoc(t_cmd *c)
{
	char	*tmp;
	int		ret;
	struct sigaction sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (perror("sigaction"), 1);
	ret = 130;
	while (1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ret = error_handler("warning", \
			"here doc delimited by end of file wanted", c->heredoc_delim, 0);
			break ;
		}
		if (ft_strcmp(c->heredoc_delim, tmp) == 0)
		{
			ret = 1;
			break ;
		}
		if (c->hd_delim_into_quotes == 0 && g_last_exit_code != 130)
			tmp = heredoc_expanser(tmp, c, -1, 0);
		if (!tmp)
			return (tmp = ft_free_ptr(tmp), 0);
		if (g_last_exit_code != 130)
			ft_putendl_fd(tmp, c->fd_heredoc);
		tmp = ft_free_ptr(tmp);
	}
	tmp = ft_free_ptr(tmp);
	close(c->fd_heredoc);
	return (ret);
}
