/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:12:32 by jbartosi          #+#    #+#             */
/*   Updated: 2023/03/09 16:45:44 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strtrim_begin(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*out;

	if (!s1 || !set)
		return (0);
	if (set[0] == '\0')
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	if (start > end)
		end = start;
	out = malloc(end - start + 1);
	if (!out)
		return (0);
	ft_memcpy(out, s1 + start, end - start);
	out[end - start] = 0;
	return (out);
}

static char	*shorten_pwd(void)
{
	char	pwd[10000];
	char	*swd;
	char	*tmp;

	getcwd(pwd, 10000);
	tmp = malloc(ft_strlen(pwd));
	if (ft_strnstr(pwd, getenv("HOME"), ft_strlen(pwd)))
	{
		tmp[0] = '~';
		tmp[1] = '\0';
		if (ft_strlen(pwd) != ft_strlen(getenv("HOME")))
		{
			tmp[1] = '/';
			tmp[2] = '\0';
			swd = ft_strtrim_begin(pwd, getenv("HOME"));
			ft_strlcat(tmp, swd, ft_strlen(tmp) + ft_strlen(swd) + 1);
			free(swd);
		}
	}
	else
		ft_strlcpy(tmp, pwd, ft_strlen(pwd) + 1);
	return (tmp);
}

void	ft_get_promt(char **shell_promt)
{
	char	user[10000];
	char	*name;
	char	*swd;

	swd = shorten_pwd();
	ft_strlcpy(user, getenv("USER"), 10000);
	name = malloc(100);
	ft_strlcpy(name, getenv("SESSION_MANAGER"), 100);
	*shell_promt = (char *)malloc(ft_strlen(user)
			+ ft_strlen(name) + 14);
	ft_strlcpy(*shell_promt, "\033[0;35m", 8);
	ft_strlcat(*shell_promt, user, ft_strlen(*shell_promt)
		+ ft_strlen(user) + 1);
	ft_strlcat(*shell_promt, "\033[0m", ft_strlen(*shell_promt) + 5);
	ft_strlcat(*shell_promt, "@", ft_strlen(*shell_promt) + 2);
	ft_strlcat(*shell_promt, name + 6, ft_strlen(*shell_promt)
		+ 7);
	ft_strlcat(*shell_promt, " \033[0;35m", ft_strlen(*shell_promt) + 9);
	ft_strlcat(*shell_promt, swd, ft_strlen(*shell_promt) + ft_strlen(swd) + 1);
	ft_strlcat(*shell_promt, "\033[0m> ", ft_strlen(*shell_promt) + 7);
	return (free(name), free(swd));
}
