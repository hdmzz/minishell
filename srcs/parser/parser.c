/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/14 10:34:36 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
*	stock the command splitted in an array
*	then search the binary file in the PATH
*/

int	parser(char *cmd)
{
	char	**split;

	split = ft_split_charset(cmd, " 	");
	if (!split)
	{
		perror("Wrong arguments");
		return (0);
	}
	exec(split);
	ft_free_split(split);
	return (1);
}
