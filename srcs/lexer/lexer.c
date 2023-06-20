/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:07:12 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/20 12:25:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



/*
*	The function recovers the splittedd command then for each
*	create a token with the value and the token type
*/
void	lexer(t_shell *g_shell)
{
	int		i;
	char	**tab;

	i = 0;
	tab = g_shell->splitted_cmd;
	while (tab[i])
	{
		
	}
}
