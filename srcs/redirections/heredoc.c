/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/16 21:01:45 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_heredoc_verif(char **line, char *delim, int pipe)
{
	int	ret;

	ret = 2;
	if (*line == NULL && g_last_exit_code == 130)
		return (g_last_exit_code);
	else if (*line == NULL)
		ret = error_handler("warning", HD_CTLD, delim, 1);
	if (ft_strcmp(delim, *line) == 0)
	{
		ret = 0;
		close(pipe);
	}
	return (ret);
}

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
	int	y;

	scanf("%d", &y);
	signal(SIGINT, sig_heredoc_handler);
	while (1)
	{
		*line = readline("> ");
		ret = first_heredoc_verif(line, delim, pipe);
		if (ret != 2)
			break ;
		if (c->hd_delim_into_quotes == 0)
			*line = heredoc_cmd_parser(*line, c);
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

int	child_heredoc(t_cmd *c, int *pipe, char *delim)
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
