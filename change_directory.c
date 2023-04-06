/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:49:18 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/06 17:31:59 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Go_back

	Previous directory
*/
void	go_back(t_mshell *shell, char **old_path)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	chdir(*old_path);
	free(*old_path);
	*old_path = malloc(ft_strlen(tmp) + 1);
	ft_strlcpy(*old_path, tmp, ft_strlen(tmp) + 1);
	print_pwd(shell);
	shell->exit_status = 0;
}

/*	Go_home

	Home directory
*/
void	go_home(t_mshell *shell, char **old_path)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	free(*old_path);
	*old_path = malloc(ft_strlen(tmp) + 1);
	ft_strlcpy(*old_path, tmp, ft_strlen(tmp) + 1);
	chdir(getenv("HOME"));
	shell->exit_status = 0;
}

/*	Ft_chdir

	Relative or absolute path
*/
void	ft_chdir(char **command, t_mshell *shell, char **old_path)
{
	char	tmp[10000];

	getcwd(tmp, 10000);
	free(*old_path);
	*old_path = malloc(ft_strlen(tmp) + 1);
	ft_strlcpy(*old_path, tmp, ft_strlen(tmp) + 1);
	if (chdir(command[1]) != 0)
	{
		printf("cd: %s: No such file or directory\n", command[1]);
		shell->exit_status = 1;
	}
	else
		shell->exit_status = 0;
}

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
	if (split_len(command) == 2)
	{
		if (ft_strncmp(command[1], "~", ft_strlen(command[1])) == 0)
			go_home(shell, &shell->old_path);
		else if (ft_strncmp(command[1], "-", ft_strlen(command[1])) == 0)
		{
			if (shell->old_path[0] != '\0')
				go_back(shell, &shell->old_path);
			else
				return (printf("NO old path set\n"), shell->exit_status = 1,
					update_prompt(shell));
		}
		else
			ft_chdir(command, shell, &shell->old_path);
	}
	else
		go_home(shell, &shell->old_path);
}
