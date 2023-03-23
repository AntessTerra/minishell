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

void	handle_env(t_mshell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
		printf("%s\n", shell->envp[i]);
}
