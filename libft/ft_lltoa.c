/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:21:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/18 16:21:42 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numberlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_lltoa(long long n)
{
	long long	newnmbr;
	long long	nbrlen;
	char		*res;

	nbrlen = ft_numberlen(n);
	res = (char *)malloc(sizeof(char) * (nbrlen + 1));
	newnmbr = n;
	if (newnmbr < 0)
		newnmbr *= -1;
	if (!res)
		return (NULL);
	res[nbrlen] = '\0';
	if (newnmbr == 0)
		res[0] = '0';
	else
	{
		while (nbrlen-- && newnmbr != 0)
		{
			res[nbrlen] = (newnmbr % 10) + '0';
			newnmbr = newnmbr / 10;
		}
		if (n < 0)
			res[nbrlen] = '-';
	}
	return (res);
}
