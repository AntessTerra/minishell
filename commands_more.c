/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:24:21 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/28 17:56:50 by jbartosi         ###   ########.fr       */
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

/*	Handle_env

	Prints out all enviromental variables
*/
void	handle_env(t_mshell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
	{
		if (shell->envp[i][0] != '\0')
			printf("%s\n", shell->envp[i]);
	}
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
}

/*	Handle_variable

	Just a helper function for handle_variables.
	Do not use outside of this scope
*/
void	handle_variable(char **command, t_mshell *s, int len, int i)
{
	int	j;

	if (ft_strncmp(command[i], "$", 1) == 0)
	{
		j = -1;
		while (s->vars[++j].name)
		{
			if (ft_strncmp(s->vars[j].name, command[i] + 1,
					ft_strlen(s->vars[j].name)) == 0
				&& s->vars[j].name[0] != '\0')
			{
				free(command[i]);
				command[i] = malloc(ft_strlen(s->vars[j].val) + 1);
				ft_strlcpy(command[i], s->vars[j].val,
					ft_strlen(s->vars[j].val) + 1);
			}
		}
		if (command[i][0] == '$' && len > 1)
			command[i][0] = '\0';
	}
}

/*	Handle_variables

	Loops through the splited command line
	and replaces valid variable names with their value
	If its not valid, replaces it with empty string
	echo $asdas -> \n
	echo $USER -> jbartosi\n
	echo -n $use d -> d
*/
int	handle_variables(char **command, t_mshell *s)
{
	int	i;
	int	len;

	i = -1;
	while (command[++i])
	{
		len = ft_strlen(command[i]);
		handle_variable(command, s, len, i);
	}
	return (0);
}
