/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:07:12 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/20 14:20:00 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *value, int type, int pos)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	token_add_back(t_token **lst, t_token *to_add)
{
	t_token	*start;

	start = *lst;
	if (start == NULL)
	{
		*lst = to_add;
		return ;
	}
	if (lst && *lst && to_add)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = to_add;
	}
}

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
