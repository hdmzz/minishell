/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:51:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/12 02:33:27 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_heredoc(pid_t pid, t_cmd *c, int *pipe)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	status = get_exit_status(status);
	if (status == 0)
		c->fd_in = dup(pipe[0]);
	close(pipe[1]);
	close(pipe[0]);
	return (status);
}

static int	prep_heredoc(t_cmd *c, char *delim)
{
	int	pid;
	int	heredoc_pipe[2];
	int	ret;

	if (pipe(heredoc_pipe) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		child_heredoc(c, heredoc_pipe, delim);
	ret = parent_heredoc(pid, c, heredoc_pipe);
	return (ret);
}

static int	left_redir(t_cmd *c, int i, int split_len)
{
	char	**cmd;
	int		ret;

	c->heredoc = 0;
	ret = 0;
	cmd = c->cmd;
	split_len = split_lenght(cmd);
	if (!cmd)
		return (1);
	while (++i < split_len && cmd[i])
	{
		if (cmd[i][0] == '<')
		{
			if (ft_strcmp(cmd[i], "<<") == 0)
				ret = prep_heredoc(c, cmd[i + 1]);
			else
				c->fd_in = open(cmd[i + 1], O_RDONLY, NULL);
			if (c->fd_in == -1)
				return (1);
			cmd[i] = ft_free_ptr(cmd[i]);
			cmd[i + 1] = ft_free_ptr(cmd[i + 1]);
			i++;
		}
	}
	return (ret);
}

static int	right_redir(t_cmd *c, int i)
{
	int		fd;
	int		oflag;
	char	**cmd;
	int		split_len;

	oflag = O_WRONLY | O_CREAT | O_TRUNC;
	cmd = c->cmd;
	split_len = split_lenght(c->cmd);
	while (++i < split_len)
	{
		if (cmd[i][0] == '>' && ft_strlen(cmd[i]) <= 2)
		{
			if (!ft_strcmp(cmd[i], ">>"))
				oflag = O_WRONLY | O_APPEND | O_CREAT;
			fd = open(cmd[i + 1], oflag, 0644);
			if (fd == -1)
				return (-1);
			c->fd_out = fd;
			cmd[i] = ft_free_ptr(cmd[i]);
			cmd[i + 1] = ft_free_ptr(cmd[i + 1]);
			i++;
		}
	}
	return (0);
}

int	prepare_io(t_cmd *c)
{
	t_cmd	*tmp;
	int		ret;

	tmp = c;
	ret = 0;
	while (tmp && ret == 0)
	{
		if (ret == 0)
			ret = left_redir(tmp, -1, 0);
		if (ret == 0)
			ret = right_redir(tmp, -1);
		tmp = tmp->next;
	}
	return (ret);
}
