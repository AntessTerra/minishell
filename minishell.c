/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/10 15:05:06 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Main

	Main function for the project.
	Displays prompt when waiting for input.
	Stores entered line and splits it into words.
	Handles entered commands.
	Frees prompt, line and splited line.
	Can handle:
		cd
			Changind the current working directory
		pwd
			Display the current working directory
		exit
			Exits the shell
*/

int	main(void)
{
	char	*line;
	char	**command;
	char	*shell_prompt;

	line = NULL;
	ft_get_prompt(&shell_prompt);
	line = readline(shell_prompt);
	while (line)
	{
		if (ft_strlen(line) > 0)
		{
			command = ft_split(line, ' ');
			if (ft_strncmp(command[0], "exit", 4) == 0)
				break ;
			else
				handle_commands(command, line, &shell_prompt);
		}
		free(line);
		line = readline(shell_prompt);
	}
	return (rl_clear_history(), free(line), free(shell_prompt),
		free_split(command), 0);
}
