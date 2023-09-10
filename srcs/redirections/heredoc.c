/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 03:15:14 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/10 14:41:31 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>

void	sig_heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

int	child_heredoc(t_cmd *c, int *pipe, char *delim)
{
	char	*tmp;
	int		ret;

	signal(SIGINT, sig_heredoc_handler);
	close(pipe[0]);
	ret = 0;
	while (1)
	{
		tmp = readline("> ");
		if (tmp == NULL)
		{
			ret = error_handler("warning", \
			"here doc delimited by end of file wanted", delim, 1);
			break ;
		}
		if (ft_strcmp(delim, tmp) == 0)
		{
			ret = 0;
			break ;
		}
		if (c->hd_delim_into_quotes == 0)
			tmp = heredoc_expanser(tmp, c, -1, 0);
		ft_putendl_fd(tmp, pipe[1]);
		tmp = ft_free_ptr(tmp);
	}
	tmp = ft_free_ptr(tmp);
	close(pipe[1]);
	exit(ret);
}
