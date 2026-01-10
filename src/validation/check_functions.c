/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:07:05 by arina             #+#    #+#             */
/*   Updated: 2026/01/10 19:23:50 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_file(char *file)
{
	int	i;
	int	res;

	i = 0;
	while (file[i])
	{
		while (file[i] != '.' && file[i])
			i++;
		res = ft_strcmp((file + i), ".cub");
		if (res != 0)
		{
			write(1, "Invalid map's name!\n", 20);
			exit(1);
		}
		else
			break ;
	}
}

int	check_tex_f(t_colflag *flag)
{
	if (flag->ea_flag == 1 && flag->no_flag == 1 && flag->so_flag == 1
		&& flag->we_flag == 1 && flag->c_flag == 1 && flag->f_flag == 1
		&& flag->map_flag == 1)
		return (2);
	if (flag->ea_flag == 1 && flag->no_flag == 1 && flag->so_flag == 1
		&& flag->we_flag == 1 && flag->c_flag == 1 && flag->f_flag == 1)
		return (1);
	if (flag->ea_flag == 1 && flag->no_flag == 1 && flag->so_flag == 1
		&& flag->we_flag == 1)
		return (0);
	return (-1);
}

int	check_sequence(char **str)
{
	int			i;
	t_colflag	flag;

	i = 0;
	init_colflag(&flag);
	while (str[i])
	{
		if (flag.c_flag != 1 && flag.f_flag != 1)
			str[i] = ft_strtrim(str[i], "\n\t\v\r\f ");
		if (ft_strncmp(str[i], "NO", 2) == 0)
			flag.no_flag = 1;
		else if (ft_strncmp(str[i], "SO", 2) == 0)
			flag.so_flag = 1;
		else if (ft_strncmp(str[i], "WE", 2) == 0)
			flag.we_flag = 1;
		else if (ft_strncmp(str[i], "EA", 2) == 0)
			flag.ea_flag = 1;
		else if (ft_strncmp(str[i], "F", 1) == 0 && check_tex_f(&flag) == 0)
			flag.f_flag = 1;
		else if (ft_strncmp(str[i], "C", 1) == 0 && check_tex_f(&flag) == 0)
			flag.c_flag = 1;
		else if (is_map_line_second(str[i]) == 1 && check_tex_f(&flag) == 1)
		{
			flag.map_flag = 1;
			break ;
		}
		else
			print_error("Invalid line in configurationnn\n", str);
		i++;
	}
	if (check_tex_f(&flag) != 2)
		return (-1);
	return (0);
}

void	check_walls(char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[0][j] != '\0')
	{
		if (str[0][j] != '1' && !(is_white_space(str[0][j])))
			print_error("Wall Error\n", str);
		j++;
	}
	while (str[i] && str[i + 1])
	{
		if (str[i][0] != '1' || str[i][ft_strlen(str[i]) - 1] != '1')
			print_error("Wall Error\n", str);
		i++;
	}
	j = 0;
	while (str[i] && str[i][j])
	{
		if (str[i][j] != '1' && !(is_white_space(str[i][j])))
			print_error("Wall Error\n", str);
		j++;
	}
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
			return (-1);
		i++;
	}
	if (((f.no_flag + f.so_flag + f.we_flag + f.ea_flag) != 1)) // && returned_found != 1
		return (-1);
	if (check_sequence(splitted_map) == -1)
		return (-1);
	check_walls(data->splited_map);
	(*map)->grid = copy_map(data->splited_map, *map, 0);
	copy_number_two_in_map(map);
	return (0);
}
