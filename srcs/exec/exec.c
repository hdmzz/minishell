/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/13 17:18:23 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	found_cmd_path(char *cmd, char *to_comp)
{
	
}

static char	*get_cmd_path(char **to_search)
{
	char			*env;
	char			**split_env;
	DIR				*dir;
	struct dirent	*entry;
	int				i;

	env = getenv("PATH");//recover te variable $PATH
	i = 0;
	if (env == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);//we are in a child process so the exit could be fetched in te waitpid call
	}
	split_env = ft_split(env, 58);//58 is int for : in ascii
	//for each path we are gonna open the directory with opendir
	while (split_env[i])
	{
		dir = opendir(split_env[i]);
		if (dir != NULL)
		{
			while ((entry = readdir(dir)) != NULL)
				printf("%s\n", entry->d_name);
		}
		i++;
	}
}

void	exec(char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork issue");
	}
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		get_cmd_path(cmd);
		// if ((execve(cmd[0], cmd, NULL)) == -1)
		// 	perror("Exec");
		exit(EXIT_SUCCESS);
	}
}
