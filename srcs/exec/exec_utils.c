/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:17:27 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/08 16:03:05 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
