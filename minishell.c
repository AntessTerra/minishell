/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:56:09 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/28 13:19:10 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Ft_exit

	Exits and frees stuff
*/
int	ft_exit(char *line, t_mshell *shell, char **command)
{
	free(line);
	free(shell->shell_prompt);
	if (command != NULL && *command != NULL)
		free_split(command);
	free(shell->home);
	free(shell->user);
	free(shell->name);
	free(shell->pipex_path);
	free_split(shell->ennames);
	ft_animate(1);
	return (0);
}

/*	Handle_signal

	Handles signals
	ioctl sends a fake input signal of \n
		https://man7.org/linux/man-pages/man2/ioctl_tty.2.html
	rl_replace_line replaces line in rdline buffer with 0
	rl_on_new_line begins reading a new line
*/
void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

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
int	main(int argc, char **argv, char **envp)
{
	static char		*line;
	static char		**command;
	t_mshell		shell;

	if ((void)argv, (void)argc, signal(SIGINT, handle_signal),
		signal(SIGQUIT, SIG_IGN), init_env(envp, &shell))
		return (printf("ERROR: missing enviromental variable\n"), 1);
	ft_animate(0);
	ft_get_prompt(&shell);
	line = readline(shell.shell_prompt);
	while (line != NULL)
	{
		if (ft_strlen(line) > 0)
		{
			command = ft_split(line, ' ');
			if (ft_strncmp(command[0], "exit", 5) == 0)
				return (ft_exit(line, &shell, command));
			else
				handle_commands(command, line, &shell);
		}
		free(line);
		line = readline(shell.shell_prompt);
	}
	return (command = NULL, ft_exit(line, &shell, command));
}
