/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:17:27 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/19 15:28:59 by hsilverb         ###   ########lyon.fr   */
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
