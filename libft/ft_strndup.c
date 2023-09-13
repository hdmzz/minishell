/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:54:28 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/13 16:35:15 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	length;
	char	*duplicate;

	length = ft_strnlen(str, n);
	duplicate = malloc(length + 1);
	if (duplicate != NULL)
	{
		ft_memcpy(duplicate, str, length);
		duplicate[length] = '\0';
	}
	return (duplicate);
}
