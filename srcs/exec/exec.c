/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:43:43 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/13 16:21:49 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec(char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork issue");
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		if ((execve(cmd[0], cmd, NULL)) == -1)
			perror("Exec");
		exit(EXIT_SUCCESS);
	}
}
