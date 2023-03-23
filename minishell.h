/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:16 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/23 12:29:00 by jbartosi         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <errno.h>

typedef struct s_mshell
{
	char	**envp;
	char	**ennames;
	char	*user;
	char	*home;
	char	*name;
	char	*shell_prompt;
}				t_mshell;

//	Enviroment.c

int		init_env(char **envp, t_mshell *shell);

//	Prompt.c

# define MAGENTA	"\033[0;35m"
# define END		"\033[0m"

void	ft_get_prompt(t_mshell *shell);
void	update_prompt(t_mshell *shell);

//	Commands.c

void	handle_commands(char **command, char *line, t_mshell *shell);

//	Commands_more.c

void	handle_env(t_mshell *shell);

//	Split_utils.c

void	free_split(char	**str);
int		split_len(char **str);

//	Animation.c

void	ft_animate(int exit);

//	Animation_utils.c

int		count_new_lines(char *str);
void	clean_terminal(int lines);

#endif
