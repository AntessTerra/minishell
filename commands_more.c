/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:24:21 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/06 13:26:33 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Print_pwd

	Takes current working directory and displays it
*/
void	print_pwd(t_mshell *shell)
{
	char	pwd[10000];

	getcwd(pwd, 10000);
	printf("%s\n", pwd);
	shell->exit_status = 0;
}

/*	Handle_env

	Prints out all enviromental variables
*/
void	handle_env(t_mshell *shell)
{
	int	i;

	i = 0;
	while (shell->vars[i].name && shell->vars[i].val)
	{
		if (shell->vars[i].name[0] != '\0' && shell->vars[i].val[0] != '\0')
			printf("%s=%s\n", shell->vars[i].name, shell->vars[i].val);
		i++;
	}
	shell->exit_status = 0;
}

/*	Handle_unset

	Takes second word and compares it against the list
	of all variables. If it finds a match, sets the record
	to null terminator.
*/
void	handle_unset(char **command, t_mshell *shell)
{
	int		i;

	i = -1;
	while (shell->vars[++i].name)
	{
		if (ft_strncmp(shell->vars[i].name, command[1],
				ft_strlen(shell->vars[i].name)) == 0
			&& shell->vars[i].name[0] != '\0')
		{
			shell->vars[i].val[0] = '\0';
			shell->vars[i].name[0] = '\0';
		}
	}
	shell->exit_status = 0;
}
