/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:02:26 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/13 14:43:12 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (ft_strchr("><\t\n |$\\\"\'", input[i]))
			count++;
		i++;
	}
	return (count);
}

void	fill_tab(char **input_tab, char *input)
{
	size_t	len;
	int		i;

	i = 0;
	while (*input != 0)
	{
		len = token_len(input);
		if (len == 0)
			return ;
		input[i] = ft_strndup(*input, len);
		if (input[i] == 0)
			return ;
		input += len;
		i++;
	}
	input[i] = '\0';
}

char	*heredoc_cmd_parser(char *input, t_shell *g, t_cmd *c)
{
	int		i;
	char	**input_tab;
	int		tab_size;
	char	*new_input;

	tab_size = count_words(input);
	input_tab = ft_calloc(tab_size + 1, sizeof(char *));
	if (input_tab == NULL)
		return (NULL);
	fill_tab(input_tab, input);
	//manque l'expnsion des variables
	//on va recomposer l'input en traduisant les variable
	
	new_input = recompose_input(input_tab);
	input = ft_free_ptr(input);

	return (new_input);
}
