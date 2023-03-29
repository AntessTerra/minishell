/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:07:50 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/29 13:03:24 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Handle_cd

	Takes splited line from readline and changes
	current working directory. Depending on
	arguments.
	Cases:
		~ || blank
			home directory
		-
			previous directory
		relative or absolute path
*/
void	handle_cd(char **command, t_mshell *shell)
{
	static char	old_path[10000];
	char		tmp[10000];

	if (split_len(command) == 2)
	{
		if (ft_strncmp(command[1], "~", ft_strlen(command[1])) == 0)
			return (getcwd(old_path, 10000), chdir(getenv("HOME")),
				update_prompt(shell));
		else if (ft_strncmp(command[1], "-", ft_strlen(command[1])) == 0)
		{
			if (old_path[0] != '\0')
				return (getcwd(tmp, 10000), chdir(old_path),
					ft_strlcpy(old_path, tmp, ft_strlen(tmp) + 1), print_pwd(),
					update_prompt(shell));
			else
				printf("NO old path set\n");
		}
		else
			return (getcwd(old_path, 10000), chdir(command[1]),
				update_prompt(shell));
	}
	else
		return (getcwd(old_path, 10000), chdir(getenv("HOME")),
			update_prompt(shell));
}

/*	Handle_echo

	Replicates the functionality of echo in bash
	Takes splited command line and prints stuff
	echo -> \n
	echo sd asd -> sd asd\n
	echo -n -> Nothing
	echo -n asd -> asd

*/
void	handle_echo(char **command)
{
	int	i;

	if (split_len(command) == 1)
		printf("\n");
	else if (!(ft_strncmp(command[1], "-n", 3) == 0))
	{
		i = 0;
		while (command[++i])
		{
			printf("%s", command[i]);
			if (i < split_len(command) - 1 && command[i][0] != '\0')
				printf(" ");
		}
		printf("\n");
	}
	else if (ft_strncmp(command[1], "-n", 3) == 0)
	{
		i = 1;
		while (command[++i])
		{
			printf("%s", command[i]);
			if (i < split_len(command) - 1 && command[i][0] != '\0')
				printf(" ");
		}
	}
}

/*	Handle_pipex

	Pipex by nroth
*/
void	handle_pipex(char **command, t_mshell *shell)
{
	char	**cmd;
	pid_t	child;

	cmd = ft_calloc(ft_arrlen((void **) command) + 2, sizeof (char *));
	cmd[0] = "./pipex";
	ft_cpyarr(&cmd[1], command);
	child = fork();
	if (child == 0)
		execve(shell->pipex_path, cmd, shell->envp);
	waitpid(child, NULL, 0);
	free(cmd);
}

/*	Add_to_history

	Checks if the now entered line is different from the last one
	if so, then it adds it to the history.
*/
void	add_to_history(char *trimed_line, t_mshell *shell)
{
	if (ft_strncmp(shell->last_line, trimed_line,
			ft_strlen(trimed_line) + 1) != 0)
	{
		add_history(trimed_line);
		free(shell->last_line);
		shell->last_line = (char *)malloc(ft_strlen(trimed_line) + 1);
		ft_strlcpy(shell->last_line, trimed_line, ft_strlen(trimed_line) + 1);
	}
}

/*	Hanle_commands

	Takes splited line from readline and launches coresponding functions
	In the end, trims the line of whitespace and adds it to the history
*/
void	handle_commands(char **command, char *line, t_mshell *shell)
{
	char	*tmp;

	handle_variables(command, shell);
	if (ft_strncmp(command[0], "cd", 3) == 0 && split_len(command) < 3)
		handle_cd(command, shell);
	else if (ft_strncmp(command[0], "pwd", 4) == 0)
		print_pwd();
	else if (ft_strncmp(command[0], "echo", 5) == 0)
		handle_echo(command);
	else if (ft_strncmp(command[0], "env", 4) == 0 && split_len(command) == 1)
		handle_env(shell);
	else if (ft_strncmp(command[0], "unset", 6) == 0 && split_len(command) == 2)
		handle_unset(command, shell);
	else if (ft_strncmp(command[0], "export", 7) == 0 && split_len(command) < 3)
		handle_export(command, shell);
	else
		handle_pipex(command, shell);
	return (tmp = ft_strtrim(line, " "), add_to_history(tmp, shell),
		free(tmp), free_split(command));
}
