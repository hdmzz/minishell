/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/11 20:01:46 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>

void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_last_exit_code = 130;
		close(0);
		write (1, "\n", 1);
	}
}

int	get_heredoc_line(t_cmd *c, char **line, char *delim, int pipe)
{
	int	ret;

	signal(SIGINT, sig_heredoc_handler);
	while (1)
	{
		*line = readline("> ");
		if (*line == NULL && g_last_exit_code == 130)
			return (g_last_exit_code);
		else if (*line == NULL)
		{
			ret = error_handler("warning", \
			"here doc delimited by end of file wanted", delim, 1);
			break ;
		}
		if (ft_strcmp(delim, *line) == 0)
		{
			ret = 0;
			close(pipe);
			break ;
		}
		if (c->hd_delim_into_quotes == 0)
			*line = heredoc_expanser(*line, c, -1, 0);
		ft_putendl_fd(*line, pipe);
		*line = ft_free_ptr(*line);
	}
	return (ret);
}

static void	close_prev_fd(t_cmd *c)
{
	t_cmd	*tmp;

	tmp = c;
	while (c && c->idx_cmd != -1)
		c = c->prev;
	if (c)
		c = c->next;
	while (c && c != tmp)
	{
		if (c->fd_in != 0)
		{
			close(c->fd_in);
			c->fd_in = 0;
		}
		if (c->fd_out != 1)
		{
			close(c->fd_out);
			c->fd_out = 1;
		}
		c = c->next;
	}
}


int	child_heredoc(t_cmd *c, int *pipe, char *delim)//il faut fermer les fd in des autres commanddes ici
{
	char	*tmp;
	int		ret;
	int		fd;

	fd = dup(pipe[1]);
	close_prev_fd(c);
	close(pipe[0]);
	close(pipe[1]);
	ret = get_heredoc_line(c, &tmp, delim, fd);
	close(fd);
	exit(ret);
}
