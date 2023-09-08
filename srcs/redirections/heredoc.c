/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/08 15:08:18 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>

//static void	close_heredoc_fds(t_cmd *c)
//{
//	if (c->fd_heredoc != -1)
//	{
//		close(c->fd_heredoc);
//		c->fd_heredoc = -1;
//	}
//	if (c->fd_in != -1)
//	{
//		close(c->fd_in);
//		c->fd_in = -1;
//	}
//	if (c->fd_out != -1)
//	{
//		close(c->fd_out);
//		c->fd_out = -1;
//	}
//	if (c->output_backup != -1)
//	{
//		close(c->output_backup);
//		c->output_backup = -1;
//	}
//	if (c->input_backup != -1)
//	{
//		close(c->input_backup);
//		c->input_backup = -1;
//	}
//}

void	handler(int signum, siginfo_t *info, void *other)
{
	(void)other;
	(void)info;
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
		exit(130);
	}
}

int	heredoc(t_cmd *c)//ici ds le child donc on doit fermer tout les fds
{
	char	*tmp;
	int		ret;
	struct sigaction action;
	int		fd_hd;

	fd_hd = 0;
	action.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	if (sigaction(SIGINT, &action, NULL) == -1)
		return (perror("sigaction"), 1);
	ret = 130;
	//close (c->g_shell->output_backup);
	//close (c->g_shell->input_backup);
	//close (c->fd_in);
	fd_hd = dup(c->fd_heredoc);
	//dup2(c->fd_heredoc, fd_hd);
	close (c->fd_heredoc);
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
		ft_putendl_fd(tmp, fd_hd);
		tmp = ft_free_ptr(tmp);
	}
	tmp = ft_free_ptr(tmp);
	close(c->fd_heredoc);
	exit(ret);
}
