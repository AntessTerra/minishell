/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/09 17:01:30 by jbartosi         ###   ########.fr       */
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
*/

void	free_split(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	return (free(str));
}

int	split_len(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i++])
		len++;
	return (len);
}

int	main(void)
{
	char	*line;
	char	**command;
	char	*shell_promt;
	char	pwd[10000];

	line = NULL;
	ft_get_promt(&shell_promt);
	line = readline(shell_promt);
	while (line)
	{
		command = ft_split(line, ' ');
		if (ft_strncmp(command[0], "exit", ft_strlen(line)) == 0 && line[0])
			break ;
		else if (ft_strncmp(command[0], "cd", ft_strlen(line)) == 0
			&& command[1] && split_len(command) == 2)
		{
			if (ft_strncmp(command[1], "~", ft_strlen(line)) == 0)
				chdir(getenv("HOME"));
			else
				chdir(command[1]);
			free(shell_promt);
			ft_get_promt(&shell_promt);
		}
		else if (ft_strncmp(command[0], "pwd", ft_strlen(line)) == 0)
		{
			getcwd(pwd, 10000);
			printf("%s\n", pwd);
		}
		add_history(line);
		free_split(command);
		free(line);
		line = readline(shell_promt);
	}
	return (rl_clear_history(), free(line), free(shell_promt),
		free_split(command), 0);
}
