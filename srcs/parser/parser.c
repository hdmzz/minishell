/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:47:34 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/13 16:20:12 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser(char *cmd)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_charset(cmd, " 	");
	if (!split)
	{
		perror("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	exec(split);
	ft_free_split(split);
}
