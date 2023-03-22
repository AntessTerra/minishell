/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:07:50 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/22 17:36:19 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Print_pwd

	Takes current working directory and displays it
*/
void	print_pwd(void)
{
	char	pwd[10000];

	getcwd(pwd, 10000);
	printf("%s\n", pwd);
}

/*	Handle_cd

	Takes splited line from readline and changes
	current working directory. Depending on
	number of arguments.
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
			if (i < split_len(command) - 1)
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
			if (i < split_len(command) - 1)
				printf(" ");
		}
	}
}

void	handle_variables(char **command, t_mshell *shell)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (command[++i])
	{
		len = ft_strlen(command[i]);
		if (command[i][0] == '$')
		{
			j = -1;
			while (shell->ennames[++j])
			{
				if (ft_strncmp(shell->ennames[j], command[i] + 1,
						ft_strlen(shell->ennames[j])) == 0)
				{
					free(command[i]);
					command[i] = malloc(ft_strlen(shell->envp[j]) - len + 1);
					ft_strlcpy(command[i], shell->envp[j] + len,
						ft_strlen(shell->envp[j]) + 1);
				}
			}
		}
	}
}

/*	Handle_commands

	Takes splited line from readline and launches coresponding functions
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
	return (tmp = ft_strtrim(line, " "), add_history(tmp),
		free(tmp), free_split(command));
}
