/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/15 13:15:19 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
*	strlcat of the dir name + / + entrypath(the command name like ls) + \0
 */
static char	*concat_cmd(char *dir_path, char *entry_path)
{
	char	*cmd;
	int		total_lenght;

	total_lenght = ft_strlen(dir_path) + ft_strlen(entry_path) + 2;

	cmd = ft_calloc(sizeof(char), total_lenght);
	if (!cmd)
		return (NULL);
	ft_strlcat(cmd, dir_path, total_lenght);
	ft_strlcat(cmd, "/", total_lenght);
	ft_strlcat(cmd, entry_path, total_lenght);
	return (cmd);
}

static bool	found_cmd_path(char *cmd, char *to_comp)
{
	if (ft_strncmp(cmd, to_comp, ft_strlen(to_comp)) == 0)
		return (true);
	return (false);
}

static char	*get_cmd_path(char **to_search)
{
	char			**split_env;
	DIR				*dir;
	struct dirent	*entry;
	int				i;
	int				j;

	i = 0;
	split_env = ft_split(getenv("PATH"), 58);//58 is int for : in ascii
	if (split_env[0] == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);//we are in a child process so the exit could be fetched in te waitpid call
	}
	//for each path we are gonna open the directory with opendir
	while (split_env[i])
	{
		dir = opendir(split_env[i]);
		if (dir != NULL)
		{
			j = 0;
			while ((entry = readdir(dir)) != NULL)
			{
				if (found_cmd_path(to_search[j], entry->d_name) == true)
					return (concat_cmd(split_env[i], entry->d_name));
			}
		}
		i++;
	}
	return (NULL);
}

void	exec(t_shell *g_shell)
{
	pid_t	pid;
	char	**split_cmd;

	split_cmd = g_shell->splitted_cmd;
	if (access(split_cmd[0], X_OK) == 0)
		g_shell->full_cmd_path = split_cmd[0];
	else
		g_shell->full_cmd_path = get_cmd_path(split_cmd);
	pid = fork();
	if (pid == -1)
		perror("Fork issue");
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
	else if (pid == 0)
	{
		if ((execve(g_shell->full_cmd_path, split_cmd, NULL)) == -1)
			perror("Exec");
		exit(EXIT_SUCCESS);
	}
}
