/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/10 11:40:44 by hdamitzi         ###   ########.fr       */
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

void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

int	child_heredoc(t_cmd *c, int *pipe, char *delim)
{
	char	*tmp;
	int		ret;

	signal(SIGINT, sig_heredoc_handler);
	close(pipe[0]);
	ret = 0;
	while (1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ret = error_handler("warning", \
			"here doc delimited by end of file wanted", delim, 1);
			break ;
		}
		if (ft_strcmp(delim, tmp) == 0)
		{
			ret = 0;
			break ;
		}
		if (c->hd_delim_into_quotes == 0)
			tmp = heredoc_expanser(tmp, c, -1, 0);
		ft_putendl_fd(tmp, pipe[1]);
		tmp = ft_free_ptr(tmp);
	}
	tmp = ft_free_ptr(tmp);
	close(pipe[1]);
	exit(ret);
}
