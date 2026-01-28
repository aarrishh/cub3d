/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:00:15 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:01:11 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_full_wall_line(char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '1' && !is_white_space(line[j]))
			return (ft_putstr_fd("Wall Error\n", 2), -1);
		j++;
	}
	return (0);
}

int	check_middle_wall_line(char *line)
{
	int	start;
	int	end;

	start = first_non_space(line);
	end = last_non_space(line);
	if (start > end)
		return (ft_putstr_fd("Wall Error\n", 2), -1);
	if (line[start] != '1' || line[end] != '1')
		return (ft_putstr_fd("Wall Error\n", 2), -1);
	return (0);
}

int	check_walls(char **str)
{
	int	i;

	if (check_full_wall_line(str[0]) == -1)
		return (-1);
	i = 1;
	while (str[i] && str[i + 1])
	{
		if (check_middle_wall_line(str[i]) == -1)
			return (-1);
		i++;
	}
	if (check_full_wall_line(str[i]) == -1)
		return (-1);
	return (0);
}

int	check_map(char **splitted_map, t_config *data, t_map **map)
{
	t_colflag	f;
	int			i;
	int			returned_found;

	i = 0;
	init_colflag(&f);
	while (data->splited_map[i])
	{
		returned_found = is_map_line(data->splited_map[i], &f);
		if (returned_found == -1)
			return (free_matrix(splitted_map), -1);
		i++;
	}
	if (((f.no_flag + f.so_flag + f.we_flag + f.ea_flag) != 1))
		return (free_matrix(splitted_map), -1);
	if (check_sequence(splitted_map) == -1)
		return (free_matrix(splitted_map), -1);
	if (check_walls(data->splited_map) == -1)
		return (free_matrix(splitted_map), -1);
	(*map)->grid = copy_map(data->splited_map, *map, 0);
	copy_number_two_in_map(map);
	free_matrix(splitted_map);
	return (0);
}
