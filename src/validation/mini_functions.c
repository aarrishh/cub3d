/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:10:28 by arina             #+#    #+#             */
/*   Updated: 2026/01/28 13:25:55 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	matrix_len(char **m)
{
	int	i;

	i = 0;
	while (m[i])
		i++;
	return (i);
}

int	is_there_nl_in_the_map(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] && map[i + 1] && map[i] == '\n' && map[i + 1] == '\n')
			return (-1);
		i++;
	}
	return (0);
}

int	ends_with_xpm(char *file)
{
	int	len;
	int	last_dot;
	int	i;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	last_dot = len - 4;
	if (ft_strcmp(file + last_dot, ".xpm") != 0)
		return (0);
	i = last_dot - 1;
	while (i >= 0)
	{
		if (file[i] == '/')
			break ;
		if (file[i] == '.')
			return (0);
		i--;
	}
	return (1);
}

int	first_non_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_white_space(s[i]))
		i++;
	return (i);
}

int	last_non_space(char *s)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0 && is_white_space(s[i]))
		i--;
	return (i);
}
