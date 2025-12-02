/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:10:28 by arina             #+#    #+#             */
/*   Updated: 2025/12/02 21:41:08 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

void	init_colflag(t_colflag *flag)
{
	flag->ea_flag = 0;
	flag->we_flag = 0;
	flag->so_flag = 0;
	flag->no_flag = 0;
	flag->f_flag = 0;
	flag->c_flag = 0;
	flag->map_flag = 0;
}

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
		if (map[i] && map[i + 1] && map[i] == '\n'
			&& map[i + 1] == '\n')
			return (-1);
		i++;
	}
	return (0);
}
