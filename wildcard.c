/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:32:00 by jbartosi          #+#    #+#             */
/*   Updated: 2023/05/22 15:47:59 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <dirent.h>
#include <stdio.h>

int	single_star(char *before, char *after)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			if (ft_strlen(dir->d_name) >= ft_strlen(before) + ft_strlen(after))
				if (ft_strnstr(dir->d_name, before, ft_strlen(before)) != NULL)
					if (ft_strnstr(dir->d_name + ft_strlen(dir->d_name)
							- ft_strlen(after), after,
							ft_strlen(after)) != NULL)
						if ((ft_strncmp(dir->d_name, ".", 2))
							&& (ft_strncmp(dir->d_name, "..", 3)))
							printf("%s\n", dir->d_name);
			dir = readdir(d);
		}
		closedir(d);
	}
	return (0);
}

char	*ft_strnstr_shifted(const char *big, const char *little, size_t len)
{
	size_t	little_counter;

	if (!*little)
		return ((char *) big);
	if (!big && !len)
		return (NULL);
	while ((*big || *(big - 1)) && len)
	{
		little_counter = 0;
		if (*big == little[little_counter]
			&& ft_strlen(little) <= len)
		{
			while (big[little_counter] == little[little_counter]
				&& little[little_counter])
				little_counter++;
			if (little_counter == ft_strlen(little))
				return ((char *)big + 1);
		}
		big++;
		len--;
	}
	return (0);
}

int	more_star(char ****split, int nstar)
{
	DIR				*d;
	struct dirent	*dir;
	char			*tmp;
	int				i;

	d = opendir(".");
	if (d)
	{
		dir = readdir(d);
		while (dir)
		{
			tmp = ft_strnstr_shifted(dir->d_name, split[0][0][0],
					ft_strlen(dir->d_name));
			tmp = ft_strnstr_shifted(tmp, split[0][0][1], ft_strlen(tmp));
			i = 1;
			while (i < nstar)
				tmp = ft_strnstr_shifted(tmp, split[0][i++][1], ft_strlen(tmp));
			if ((ft_strncmp(dir->d_name, ".", 2)) && tmp
				&& (ft_strncmp(dir->d_name, "..", 3)))
				printf("%s\n", dir->d_name);
			dir = readdir(d);
		}
		closedir(d);
	}
	return (0);
}

int	count_stars(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '*')
			count++;
	return (count);
}

int	count_nonstars(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] != '*')
			count++;
	return (count);
}

int	count_slashes(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
		if (str[i] == '/')
			count++;
	return (count);
}

void	allocate(char *str, char ****split, int nstar, int x)
{
	split[0] = malloc(nstar * sizeof(char *));
	x = -1;
	while (x++ < nstar - 1)
	{
		split[0][x] = malloc(2 * sizeof(char *));
		split[0][x][0] = malloc(ft_strlen(str) + 1);
		split[0][x][1] = malloc(ft_strlen(str) + 1);
	}
}

void	single_split(char *str, char ****split)
{
	int			i;
	int			x;
	static int	star;
	static int	a;
	static int	b;

	x = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
			star = 1;
		else if (!star)
			split[0][x][0][b++] = str[i];
		else if (star)
			split[0][x][1][a++] = str[i];
	}
	split[0][x][1][a] = 0;
	split[0][x][0][b] = 0;
}

void	split_by_star(char *str, char ****split, int nstar)
{
	int	i;
	int	x;
	int	star;
	int	a;
	int	b;

	allocate(str, split, nstar, x);
	if (nstar == 1)
		return (single_split(str, split));
	i = -1;
	x = -1;
	a = 0;
	b = 0;
	star = 0;
	while (++x < nstar)
	{
		while (str[++i])
		{
			if (str[i] == '*' && star)
			{
				split[0][x][0][b] = 0;
				split[0][x][1][a] = 0;
				a = 0;
				b = 0;
				x++;
			}
			else if (str[i] == '*')
			{
				star = 1;
				split[0][x][0][b] = 0;
				b = 0;
			}
			else if (!star && x == 0)
				split[0][x][0][b++] = str[i];
			else if (star && x == nstar - 1)
				split[0][x][1][a++] = str[i];
			else if (star)
			{
				split[0][x][1][a++] = str[i];
				split[0][x + 1][0][b++] = str[i];
			}
		}
		split[0][x][1][a] = 0;
	}
}

void	free_split(char ****split, int nstar)
{
	int	n;

	n = -1;
	while (++n < nstar)
	{
		free(split[0][n][0]);
		free(split[0][n][1]);
		free(split[0][n]);
	}
	free(split[0]);
}

int	main(int argc, char **argv)
{
	char	***split;
	int		nstar;
	int		n;

	if (argc == 2)
	{
		nstar = count_stars(argv[1]);
		if (nstar == 1)
			return (split_by_star(argv[1], &split, nstar),
				single_star(split[0][0], split[0][1]),
				free_split(&split, nstar), 0);
		else if (nstar == ft_strlen(argv[1]) && argv[1][0])
			single_star("\0", "\0");
		else if (nstar > 1 && count_nonstars(argv[1]) > 0)
			return (split_by_star(argv[1], &split, nstar),
				more_star(&split, nstar),
				free_split(&split, nstar), 0);
	}
}
