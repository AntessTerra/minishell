/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:49:18 by jbartosi          #+#    #+#             */
/*   Updated: 2023/04/06 14:26:08 by jbartosi         ###   ########.fr       */
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
					ft_strlcpy(old_path, tmp, ft_strlen(tmp) + 1),
					print_pwd(shell), update_prompt(shell));
			else
				return (printf("NO old path set\n"), shell->exit_status = 1,
					update_prompt(shell));
		}
		else
			return (getcwd(old_path, 10000), chdir(command[1]),
				update_prompt(shell));
	}
	else
		return (getcwd(old_path, 10000), chdir(getenv("HOME")),
			update_prompt(shell));
}
