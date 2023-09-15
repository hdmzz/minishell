/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:23:13 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/14 16:29:20 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_io(t_cmd *c)
{
	if (c != NULL)
	{
		if (c->fd_in != 0)
		{
			c->input_backup = dup(STDIN_FILENO);
			dup2(c->fd_in, STDIN_FILENO);
		}
		if (c->fd_out != 1)
		{
			c->output_backup = dup(STDOUT_FILENO);
			dup2(c->fd_out, STDOUT_FILENO);
		}
	}
}
