/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:16 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/10 15:01:40 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

//	Prompt.c

void	ft_get_prompt(char **shell_promt);
void	update_prompt(char **shell_promt);

//	Commands.c

void	handle_commands(char **command, char *line, char **shell_prompt);

//	Split_utils.c

void	free_split(char	**str);
int		split_len(char **str);

#endif
