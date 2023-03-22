/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/22 17:33:44 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Check_env

	Makes sure that it has variable home
	and the name of the pc
	Also if there is no user data, fills it with guest
*/
int	check_env(t_mshell *shell)
{
	if (shell->home == NULL || shell->name == NULL)
		return (1);
	if (shell->user == NULL)
	{
		shell->user = malloc(6);
		shell->user = "guest";
	}
	return (0);
}

/*	Init_struct

	Takes pointer to structure and sets its values to NULL
	Plus adds array envp to the structure for future use
*/
void	init_struct(char **envp, t_mshell *shell)
{
	int		i;
	int		j;
	char	tmp[100000];

	shell->ennames = NULL;
	shell->ennames = malloc((split_len(envp) + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j])
			if (envp[i][j++] == '=')
				break ;
		shell->ennames[i] = malloc((j + 1) * sizeof(char));
		ft_strlcpy(shell->ennames[i], envp[i], j);
	}
	shell->ennames[i] = NULL;
	shell->envp = envp;
	shell->home = NULL;
	shell->user = NULL;
	shell->name = NULL;
}

/*	Init_env

	Loops through all the envirimental variables and gathers
	HOME, USER and SESSION_MANAGER for creating the command prompt
*/
int	init_env(char **envp, t_mshell *shell)
{
	int	i;

	init_struct(envp, shell);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			shell->home = malloc(ft_strlen(envp[i]) - 4 * sizeof(char));
			ft_strlcpy(shell->home, envp[i] + 5, ft_strlen(envp[i]) - 4);
		}
		else if (ft_strncmp(envp[i], "USER=", 5) == 0)
		{
			shell->user = malloc(ft_strlen(envp[i]) - 4 * sizeof(char));
			ft_strlcpy(shell->user, envp[i] + 5, ft_strlen(envp[i]) - 4);
		}
		else if (ft_strncmp(envp[i], "SESSION_MANAGER=", 16) == 0)
		{
			shell->name = malloc(7);
			ft_strlcpy(shell->name, envp[i] + 22, 7);
		}
	}
	return (check_env(shell));
}
