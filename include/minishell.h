/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:45:59 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/06/20 12:35:16 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>

typedef enum e_tokens_type
{
	literal,
	single_quote,
	doule_quote,
	simple_redir_left,
	simple_redir_right,
	double_redir_left,
	double_redir_right,
	pipeline,
	dollar,
	space,
}			t_tokens_type;

typedef struct s_token
{
	void			*value;
	t_tokens_type	type;
}				t_token;

typedef struct s_shell
{
	char	*start_buff;
	char	*full_cmd_path;
	char	**splitted_cmd;
}				t_shell;

//srcs/parser/parser.c
int		parser(t_shell *g_shell);

//srcs/exec/exec.c
void	exec(t_shell *g_shell);

//srcs/lexer/lexer.c
void	lexer(t_shell *g_shell);

//src/utils/utils.c
void	ft_free_shell(t_shell *g_shell);

#endif
