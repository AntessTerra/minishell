/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_more2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:40:02 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/29 15:29:03 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Print_export

	Display all env variables in export format
	declare -x NAME="val"
*/
void	print_export(t_mshell *shell)
{
	int	i;

	i = 0;
	while (shell->vars[i].name)
	{
		if (shell->vars[i].name[0] != '\0' && shell->vars[i].val[0] != '\0')
			printf("declare -x %s=\"%s\"\n", shell->vars[i].name,
				shell->vars[i].val);
		else if (shell->vars[i].name[0] != '\0'
			&& shell->vars[i].val[0] == '\0')
			printf("declare -x %s=\"\"\n", shell->vars[i].name);
		else if (shell->vars[i].name[0] != '\0')
			printf("declare -x %s\n", shell->vars[i].name);
		i++;
	}
}

/*	Export_name

	Creates a new env variable with
*/
void	export_name(char **command, t_mshell *shell)
{
	int	j;
	int	i;

	j = 0;
	while (command[1][j])
		if (command[1][j++] == '=')
			break ;
	i = -1;
	while (shell->vars[++i].name)
		if (shell->vars[i].name[0] == '\0')
			break ;
	if (shell->vars[i].name == NULL)
	{
		printf("OOPS\n");
		//Create new variable with empty val
	}
	else if (shell->vars[i].name[0] == '\0')
	{
		printf("%i: CHANGING\n", i);
		free(shell->vars[i].name);
		shell->vars[i].name = malloc((j + 1) * sizeof(char));
		ft_strlcpy(shell->vars[i].name, command[1], j + 1);
	}
}

void	export_both(char **command, t_mshell *shell)
{
	int	j;
	int	i;

	j = 0;
	while (command[1][j])
		if (command[1][j++] == '=')
			break ;
	i = -1;
	while (shell->vars[++i].name)
		if (shell->vars[i].name[0] == '\0')
			break ;
	if (shell->vars[i].name == NULL)
	{
		printf("OOPS BOTH\n");
		//Create new variable with given val
	}
	else if (shell->vars[i].name[0] == '\0')
	{
		printf("%i: CHANGING BOTH\n", i);
		free(shell->vars[i].name);
		shell->vars[i].name = malloc((j + 1) * sizeof(char));
		ft_strlcpy(shell->vars[i].name, command[1], j);
		free(shell->vars[i].val);
		shell->vars[i].val = malloc((ft_strlen(command[1])) - j + 1);
		ft_strlcpy(shell->vars[i].val, command[1] + j,
			(ft_strlen(command[1])) - j + 1);
	}
}

/*	Change_val

	Checks if the variable name exists, if so then changes its value
	and returns 0, else returns 1
*/
int	change_val(char **command, t_mshell *shell)
{
	int	i;
	int	j;

	j = 0;
	while (command[1][j])
		if (command[1][j++] == '=')
			break ;
	i = -1;
	while (shell->vars[++i].name)
		if (ft_strncmp(shell->vars[i].name, command[1], j - 1) == 0)
			break ;
	if (shell->vars[i].name != NULL)
	{
		free(shell->vars[i].val);
		shell->vars[i].val = malloc((ft_strlen(command[1])) - j + 1);
		ft_strlcpy(shell->vars[i].val, command[1] + j,
			(ft_strlen(command[1])) - j + 1);
	}
	else
		return (1);
	return (0);
}

/*	Handle_export

	Replicates the function of export from bash
	Cases:
		export - prints env variables
		export NAME - set only variable name
		export NAME= - set name and empty val
		export NAME=val - set name and value
*/
void	handle_export(char **command, t_mshell *shell)
{
	if (split_len(command) == 1)
		print_export(shell);
	else if (split_len(command) == 2)
	{
		if (ft_strchr(command[1], '='))
		{
			printf("SAVE NAME AND VAL\n");
			if (!change_val(command, shell))
				return ;
			export_both(command, shell);
		}
		else
			return (printf("SAVE ONLY NAME\n"), export_name(command, shell));
	}
}
