/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:48:11 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/14 10:33:57 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//il faut recuperer la commande donc faire un split et ensuite executer
int	main(void)
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
