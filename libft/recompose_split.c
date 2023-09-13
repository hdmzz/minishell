/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recompose_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:44:53 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/13 14:45:10 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*recompose_split(char **tab)
{
	char	*new_input;
	int		total_len;
	int		tab_len;
	int		i;

	total_len = 0;
	i = -1;
	while (tab[++i])
		total_len += ft_strlen(tab[i]);
	tab_len = i;
	total_len += i - 1;
	new_input = ft_calloc(total_len + 1, sizeof(char));
	if (!new_input)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		ft_strlcat(new_input, tab[i], total_len + 1);
		if (i < tab_len - 1)
			ft_strlcat(new_input, " ", total_len + 1);
		i++;
	}
	ft_free_split(tab);
	return (new_input);
}
