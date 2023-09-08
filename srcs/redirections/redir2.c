/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 02:51:58 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/08 17:47:08 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_mkstemp(char *filename)
{
	int	try_max;
	int	fd;
	int	i;

	i = 0;
	try_max = 0;
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
	while (fd == -1 && try_max <= 15)
	{
		while (filename[i] && filename[i] != '0')
			i += 1;
		if (filename[i] && ft_isalnum(filename[i] + 1))
			filename[i] = filename[i] + 1;
		else
			filename[i] = 'a';
		fd = open(filename, O_CREAT | O_EXCL | O_RDWR | O_TRUNC, 0600);
		try_max++;
	}
	if (try_max == 15)
		return (-1);
	return (fd);
}

static int	prep_heredoc(t_cmd *c, char *delim)
{
	static char	tmpfile[] = "tmpfile0";
	int			i;
	pid_t		pid;
	int			status;
	int			ret;

	i = 0;
	c->heredoc = 1;
	c->fd_heredoc = ft_mkstemp(tmpfile);
	if (c->fd_heredoc == -1)
		return (perror("too many temporary files"), 1);
	c->fd_in = open(tmpfile, O_RDONLY, NULL);
	unlink(tmpfile);
	c->heredoc_delim = delim;
	pid = fork();
	if (pid == 0)
		heredoc(c);
	else
		waitpid(pid, &status, 0);
	ret = get_exit_status(status);
	while (tmpfile[i] && !ft_isdigit(tmpfile[i]))
		i++;
	if (tmpfile[i] == '9')
		tmpfile[i] = '0';
	return (tmpfile[i] = tmpfile[i] + 1, ret);
}

static int	left_redir(t_cmd *c, int i)
{
	char	**cmd;
	int		split_len;
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
	while (tmp)
	{
		if (ret == 0)
			ret = left_redir(tmp, -1);
		if (ret == 0)
			ret = right_redir(tmp, -1);
		tmp = tmp->next;
	}
	return (ret);
}
