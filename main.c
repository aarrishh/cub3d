/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2025/11/30 18:00:15 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

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
			write (1, "Invalid map's name!\n", 20);
			exit(1);
		}
		else
			break ;
	}
}

void init_colflag(t_colflag *flag)
{
	flag->ea_flag = 0;
	flag->we_flag = 0;
	flag->so_flag = 0;
	flag->no_flag = 0;
	flag->f_flag = 0;
	flag->c_flag = 0;
	flag->map_flag = 0;
}

int check_tex_f(t_colflag *flag)
{
	if (flag->ea_flag == 1 && flag->no_flag == 1
		&& flag->so_flag == 1 && flag->we_flag == 1
		&& flag->c_flag == 1 && flag->f_flag == 1 
		&& flag->map_flag == 1)
		return (2);
	if (flag->ea_flag == 1 && flag->no_flag == 1
		&& flag->so_flag == 1 && flag->we_flag == 1
		&& flag->c_flag == 1 && flag->f_flag == 1)
		return (1);
	if (flag->ea_flag == 1 && flag->no_flag == 1
		&& flag->so_flag == 1 && flag->we_flag == 1)
		return (0);
	return (-1);
}

int check_sequence(char **str)
{
	int	i;
	t_colflag flag;

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

int matrix_len(char **m)
{
    int i = 0;
    while (m[i])
        i++;
    return (i);
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

void copy_number_two_in_map(t_map **map)
{
	int i = 0;
	int j  = 0;
	char **mapik = (*map)->grid;
	
	while (mapik[i])
	{
		j = 0;
		while (mapik[i][j])
		{
			if (is_white_space(mapik[i][j]) && mapik[i][j] != '1' 
				&& mapik[i][j] != '0' && mapik[i][j] != 'N' 
				&& mapik[i][j] != 'W' && mapik[i][j] != 'E'
				&& mapik[i][j] != 'S')
				mapik[i][j] = '2';
			j++;
		}
		i++;
	}
}

int check_map(char **splitted_map, t_config *data, t_map **map)
{
	int	i;
	t_colflag f;
	int returned_found;

	i = 0;
	init_colflag(&f);
	while(data->splited_map[i])
	{
		returned_found = is_map_line(data->splited_map[i], &f);
		if (returned_found == -1)
			return (-1);
		i++;
	}
	if (((f.no_flag + f.so_flag + f.we_flag + f.ea_flag) != 1))// && returned_found != 1
		return (-1);
	if (check_sequence(splitted_map) == -1)
		return (-1);
	check_walls(data->splited_map);
	(*map)->grid = copy_map(data->splited_map, *map, 0);
	copy_number_two_in_map(map);
	return (0);
}

void find_index_after_colors(char *res, t_config **data)
{
	int i = 0;
	int finish = 0;
	
	while (res[i])
		i++;
	while (i >= 0 && res[i] != 'F' && res[i] != 'C')
		i--;
	while (i >= 0 && res[i] && res[i] != '\n')
		i++;
	finish = i;
	while (i >= 0 && res[finish])
		finish++;
	(*data)->hyusisharav = ft_substr(res, 0, i);
	(*data)->map_before_split = ft_substr(res, i + 1, finish);
}

int is_there_nl_in_the_map(char *map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i] && map[i + 1] && map[i] == '\n' && map[i + 1] == '\n')
			return (-1);
		i++;
	}
	return (0);
}

int start_validation(char *file, t_config *data, t_map *map)
{
	int			fd;
	char		*line;
	char		*res;
	char		**split;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Cannot open file\n", NULL);
	line = get_next_line(fd);
	res = ft_strdup("");
	while (line != NULL)
	{
		res = ft_strjoin_(res, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	res = ft_strtrim(res, "\n\t\v\r\f ");
	find_index_after_colors(res, &data);
	data->splited_hyusisharav = ft_split(data->hyusisharav, '\n', MAX_SPLIT_CNT);
	split = ft_split(res, '\n', MAX_SPLIT_CNT);
	free(res);
	if (parse_elements(&data) == -1)
		return(-1);
	if (is_there_nl_in_the_map(data->map_before_split) == -1)
		return (-1);
	data->splited_map = ft_split(data->map_before_split, '\n', MAX_SPLIT_CNT);
	if (check_map(split, data, &map) == -1)
		return (-1);
		// free_matrix(split);
	// *split = NULL;
	return (0);
}


int	main(int argc, char **argv)
{
	t_config		data;
	t_map			map;
	int				return_value;

	return_value = 1;
	// res = NULL;
	if (argc == 2)
	{
		check_file(argv[1]);
		return_value = start_validation(argv[1], &data, &map);
		if (return_value < 0)
			printf("Validation error!\n");
		else
			printf("Congratulations!\n");
		flood_fill(&map);
		// print_matrix(map.grid);
		
		// check(res, &map);
		// free_matrix(res);
	}
	else
		return (write (2, "Error\n", 6), 1);
	return (0);
}
