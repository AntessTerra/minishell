/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_more.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:24:21 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/23 12:28:40 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (shell->ennames[++i])
	{
		if (ft_strncmp(shell->ennames[i], command[1],
				ft_strlen(shell->ennames[i])) == 0
			&& shell->ennames[i][0] != '\0')
		{
			shell->envp[i][0] = '\0';
			shell->ennames[i][0] = '\0';
		}
	}
}

/*	Is_variable

	Just a helper function for handle_variables.
	Do not use outside of this scope
*/
void	is_variable(char **command, t_mshell *s, int len, int i)
{
	int	j;

	if (ft_strncmp(command[i], "$", 1) == 0)
	{
		j = -1;
		while (s->ennames[++j])
		{
			if (ft_strncmp(s->ennames[j], command[i] + 1,
					ft_strlen(s->ennames[j])) == 0
				&& s->ennames[j][0] != '\0')
			{
				free(command[i]);
				command[i] = malloc(ft_strlen(s->envp[j]) - len + 1);
				ft_strlcpy(command[i], s->envp[j] + len,
					ft_strlen(s->envp[j]) + 1);
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
		is_variable(command, s, len, i);
	}
	return (0);
}
