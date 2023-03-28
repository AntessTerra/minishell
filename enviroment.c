/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:00:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/28 18:02:54 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Check_env

	Makes sure that it has variable home
	Also if there is no user data, fills it with guest and
	name with computer
*/
int	check_env(t_mshell *shell)
{
	char	pwd[10000];

	if (shell->home == NULL)
		return (1);
	if (shell->user == NULL)
	{
		shell->user = malloc(6);
		ft_strlcpy(shell->user, "guest", 6);
	}
	if (shell->name == NULL)
	{
		shell->name = malloc(10);
		ft_strlcpy(shell->name, "computer", 10);
	}
	getcwd(pwd, 10000);
	shell->pipex_path = ft_strjoin(pwd, "/pipex/pipex");
	return (0);
}

/*	Init_vars


*/
void	init_vars(char **envp, t_mshell *shell)
{
	int		i;
	int		j;

	shell->vars = NULL;
	shell->vars = malloc((split_len(envp) + 1) * sizeof(t_var));
	i = -1;
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j])
			if (envp[i][j++] == '=')
				break ;
		shell->vars[i].name = malloc((j + 1) * sizeof(char));
		ft_strlcpy(shell->vars[i].name, envp[i], j);
		shell->vars[i].val = malloc((ft_strlen(envp[i])) - j + 1);
		ft_strlcpy(shell->vars[i].val, envp[i] + j,
			(ft_strlen(envp[i])) - j + 1);
	}
	shell->vars[i].name = NULL;
	shell->vars[i].val = NULL;
}

/*	Init_struct

	Takes pointer to structure and sets its values to NULL
	Plus adds array envp to the structure for future use
*/
void	init_struct(char **envp, t_mshell *shell)
{
	init_vars(envp, shell);
	shell->envp = envp;
	shell->home = NULL;
	shell->user = NULL;
	shell->name = NULL;
	shell->last_line = malloc(1);
	shell->last_line[0] = '\0';
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
