/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/15 13:14:13 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*	stock the command splitted in an array
*	then search the binary file in the PATH
*/

int	parser(t_shell *g_shell)
{
	g_shell->splitted_cmd = ft_split_charset(g_shell->start_buff, " 	");
	if (!g_shell->splitted_cmd)
	{
		perror("Wrong arguments");
		return (0);
	}
	exec(g_shell);
	ft_free_split(g_shell->splitted_cmd);
	return (1);
}
