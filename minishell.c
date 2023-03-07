/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/07 16:40:08 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
/home/jbartosi/42/Curriculum/minishel
/home/jbartosi == 							~
/ == 										/
/home == 									/home
/home/jbartosi/42 == 						~/42
/home/jbartosi/42/Curriculum == 			~/4/Curriculum
/home/jbartosi/42/Curriculum/minishel ==	~/4/C/minishell
17 for one color
*/

void	ft_get_promt(char **shell_promt)
{
	char	pwd[10000];
	char	user[10000];
	char	name[10000];

	getcwd(pwd, 10000);
	ft_strlcpy(user, getenv("USER"), 10000);
	ft_strlcpy(name, getenv("NAME"), 10000);
	*shell_promt = (char *)malloc(ft_strlen(user)
			+ ft_strlen(name) + ft_strlen(pwd) + 14);
	if (!shell_promt)
		return ;
	ft_strlcpy(*shell_promt, "\033[0;35m", 8);
	ft_strlcat(*shell_promt, user, ft_strlen(*shell_promt)
		+ ft_strlen(user) + 1);
	ft_strlcat(*shell_promt, "\033[0m", ft_strlen(*shell_promt) + 5);
	ft_strlcat(*shell_promt, "@", ft_strlen(*shell_promt) + 2);
	ft_strlcat(*shell_promt, name, ft_strlen(*shell_promt)
		+ ft_strlen(name) + 1);
	ft_strlcat(*shell_promt, " \033[0;35m", ft_strlen(*shell_promt) + 9);
	ft_strlcat(*shell_promt, pwd, ft_strlen(*shell_promt) + ft_strlen(pwd) + 1);
	ft_strlcat(*shell_promt, "\033[0m> ", ft_strlen(*shell_promt) + 7);
}

int	main(void)
{
	//char	*line;
	char	*shell_promt;

	ft_get_promt(&shell_promt);
	if (!shell_promt)
		return (1);
	//line = readline(shell_promt);
	printf("%s\n", shell_promt);
	//free(line);
	free(shell_promt);
	return (0);
}
