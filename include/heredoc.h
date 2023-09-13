/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:13:28 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/13 15:52:02 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include <unistd.h>
# include "typedef.h"

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);
char	*var_xpanser(char *input, t_shell *g_shell);

int		prepare_io(t_cmd *c);

//parser/parser_heredoc.c
char	*heredoc_expanser(char *input, t_cmd *c, int i, int y);

//heredoc_parser.c
int		heredoc_first_analyzer(t_shell *g_shell);

//exec/exec_heredoc.c
char	*exec_imbricated_cmd(char *cmd_str, t_shell *g_shell);

char	*heredoc_cmd_parser(char *input, t_cmd *c);
int		first_heredoc_verif(char **line, char *delim, int pipe);
char	**tab_expanded(char **tab, t_cmd *c);

char	*recompose_input(char **tab, int total_len, int tab_len, int i);


#endif
