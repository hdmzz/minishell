/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/13 15:42:31 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//il faut recuperer la commande donc faire un split et ensuite executer
int	main(int ac, char **av, char **env)
{
	char	*buff;

	buff = ft_calloc(sizeof(char), 2048);
	if (!buff)
	{
		perror("Error calloc");
		return (1);
	}
	while ((buff = readline("$> ")) != NULL)
	{
		parser(buff);
	}
}
