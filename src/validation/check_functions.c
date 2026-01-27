/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:07:05 by arina             #+#    #+#             */
/*   Updated: 2026/01/27 19:34:03 by arimanuk         ###   ########.fr       */
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

static int	handle_sequence_line(char *line, t_colflag *flag)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		flag->no_flag = 1;
	else if (ft_strncmp(line, "SO", 2) == 0)
		flag->so_flag = 1;
	else if (ft_strncmp(line, "WE", 2) == 0)
		flag->we_flag = 1;
	else if (ft_strncmp(line, "EA", 2) == 0)
		flag->ea_flag = 1;
	else if (ft_strncmp(line, "F", 1) == 0 && check_tex_f(flag) == 0)
		flag->f_flag = 1;
	else if (ft_strncmp(line, "C", 1) == 0 && check_tex_f(flag) == 0)
		flag->c_flag = 1;
	else if (is_map_line_second(line) == 1 && check_tex_f(flag) == 1)
	{
		flag->map_flag = 1;
		return (1); // map started → stop parsing headers
	}
	else
		return (-1);
	return (0);
}


void	trim_if_needed(char **line, t_colflag *flag)
{
	if (flag->c_flag != 1 && flag->f_flag != 1)
		*line = ft_strtrim(*line, "\n\t\v\r\f ");
}

int	check_sequence(char **str)
{
	int			i;
	int			ret;
	t_colflag	flag;

	i = 0;
	init_colflag(&flag);
	while (str[i])
	{
		trim_if_needed(&str[i], &flag);
		ret = handle_sequence_line(str[i], &flag);
		if (ret == 1)
			break ;
		if (ret == -1)
			print_error("Invalid line in configuration\n", str);
		i++;
	}
	if (check_tex_f(&flag) != 2)
		return (-1);
	return (0);
}


// int	check_sequence(char **str)
// {
// 	int			i;
// 	t_colflag	flag;

// 	i = 0;
// 	init_colflag(&flag);
// 	while (str[i])
// 	{
// 		if (flag.c_flag != 1 && flag.f_flag != 1)
// 			str[i] = ft_strtrim(str[i], "\n\t\v\r\f ");
// 		if (ft_strncmp(str[i], "NO", 2) == 0)
// 			flag.no_flag = 1;
// 		else if (ft_strncmp(str[i], "SO", 2) == 0)
// 			flag.so_flag = 1;
// 		else if (ft_strncmp(str[i], "WE", 2) == 0)
// 			flag.we_flag = 1;
// 		else if (ft_strncmp(str[i], "EA", 2) == 0)
// 			flag.ea_flag = 1;
// 		else if (ft_strncmp(str[i], "F", 1) == 0 && check_tex_f(&flag) == 0)
// 			flag.f_flag = 1;
// 		else if (ft_strncmp(str[i], "C", 1) == 0 && check_tex_f(&flag) == 0)
// 			flag.c_flag = 1;
// 		else if (is_map_line_second(str[i]) == 1 && check_tex_f(&flag) == 1)
// 		{
// 			flag.map_flag = 1;
// 			break ;
// 		}
// 		else
// 			print_error("Invalid line in configuration\n", str);
// 		i++;
// 	}
// 	if (check_tex_f(&flag) != 2)
// 		return (-1);
// 	return (0);
// }

int	check_full_wall_line(char *line, char **map)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != '1' && !is_white_space(line[j]))
			return (print_error("Wall Error\n", map), -1);
		j++;
	}
	return (0);
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

int	check_middle_wall_line(char *line, char **map)
{
	int	start;
	int	end;

	start = first_non_space(line);
	end = last_non_space(line);
	if (start > end)
		return (print_error("Wall Error\n", map), -1);
	if (line[start] != '1' || line[end] != '1')
		return (print_error("Wall Error\n", map), -1);
	return (0);
}

int	check_walls(char **str)
{
	int	i;

	if (check_full_wall_line(str[0], str) == -1)
		return (-1);
	i = 1;
	while (str[i] && str[i + 1])
	{
		if (check_middle_wall_line(str[i], str) == -1)
			return (-1);
		i++;
	}
	if (check_full_wall_line(str[i], str) == -1)
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
		{
			free_matrix(splitted_map);
			return (-1);
		}	
		i++;
	}
	if (((f.no_flag + f.so_flag + f.we_flag + f.ea_flag) != 1)) // && returned_found != 1
	{
		free_matrix(splitted_map);
		return (-1);
	}
	if (check_sequence(splitted_map) == -1)
	{
		free_matrix(splitted_map);
		return (-1);
	}
	if (check_walls(data->splited_map) == -1)
	{
		free_matrix(splitted_map);
		return (-1);
	}
	(*map)->grid = copy_map(data->splited_map, *map, 0);
	copy_number_two_in_map(map);
	free_matrix(splitted_map);
	return (0);
}
