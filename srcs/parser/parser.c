/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/20 13:58:44 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_separator(char c)
{
	if (c == "")
}

/*
*	stock the command splitted in an array
*	then search the binary file in the PATH
*/
int	parser(t_shell *g_shell)
{
	g_shell->splitted_cmd = ft_split_charset(g_shell->start_buff, " \t\n");
	if (!g_shell->splitted_cmd)
	{
		perror("Wrong arguments");
		return (0);
	}
	//lexer(g_shell);
	exec(g_shell);
	ft_free_split(g_shell->splitted_cmd);
	return (1);
}
