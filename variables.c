/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:13:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/06 13:42:49 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Exit_status

	Checks for $? in echo command and fill it with the exit number
	And if $something doesnt exist, null terminates result
*/
void	exit_status(char **command, t_mshell *s, int len, int i)
{
	char	*exit_num;
	char	*tmp;

	if (command[i][0] == '$' && command[i][1] == '?')
	{
		tmp = malloc(ft_strlen(command[i]) + 1);
		ft_strlcpy(tmp, command[i], ft_strlen(command[i]) + 1);
		free(command[i]);
		exit_num = ft_itoa(s->exit_status);
		command[i] = malloc(ft_strlen(exit_num) + ft_strlen(tmp) + 1);
		ft_strlcpy(command[i], exit_num, ft_strlen(exit_num) + 1);
		ft_strlcat(command[i], tmp + 2, ft_strlen(command[i])
			+ ft_strlen(tmp) + 1);
		s->exit_status = 0;
		return (free(exit_num), free(tmp));
	}
	else if (command[i][0] == '$' && len > 1)
		command[i][0] = '\0';
}

/*	Handle_variable

	Just a helper function for handle_variables.
	Do not use outside of this scope
*/
void	handle_variable(char **command, t_mshell *s, int len, int i)
{
	int		j;

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
		exit_status(command, s, len, i);
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
