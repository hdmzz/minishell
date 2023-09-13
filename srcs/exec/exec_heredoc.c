/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:16:36 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/12 02:32:49 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(int pipe_fd[2], char *full_cmd_path, char **cmd_tab)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execve(full_cmd_path, cmd_tab, NULL);
	perror("exec pipes child heredoc");
	exit(1);
}

static char	*recompose_output(int fd)
{
	char	*big_line;
	char	*line;

	line = get_next_line(fd);
	big_line = NULL;
	while (line)
	{
		if (line)
			big_line = ft_join_shell(big_line, line);
		ft_free_ptr(line);
		line = get_next_line(fd);
	}
	return (big_line);
}

char	*exec_imbricated_cmd(char *cmd_str, t_shell *g)
{
	char	**cmd_tab;
	int		pid;
	int		pipe_fd[2];
	char	*output;
	char	*full_cmd_path;

	cmd_tab = ft_split(cmd_str, 32);
	full_cmd_path = get_cmd_path(cmd_tab, g);
	if (full_cmd_path == NULL)
		return (ft_free_split(cmd_tab), ft_strjoin(cmd_tab[0], \
		": command not found"));
	if (pipe(pipe_fd) == -1)
		return (ft_free_split(cmd_tab), NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
		child(pipe_fd, full_cmd_path, cmd_tab);
	close(pipe_fd[1]);
	output = recompose_output(pipe_fd[0]);
	close (pipe_fd[0]);
	if (output == NULL)
		return (ft_free_split(cmd_tab), NULL);
	waitpid(pid, &g_last_exit_code, 0);
	return (ft_free_ptr(full_cmd_path), ft_free_split(cmd_tab), output);
}
