/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2026/01/27 16:56:02 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	copy_number_two_in_map(t_map **map)
{
	int		i;
	int		j;
	char	**mapik;

	j = 0;
	i = 0;
	mapik = (*map)->grid;
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

void	find_index_after_colors(char *res, t_config **data)
{
	int	i;
	int	finish;

	i = 0;
	finish = 0;
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

int	start_validation(char *file, t_config *data, t_map *map)
{
	int		fd;
	char	*line;
	char	*res;
	char	**split;

	(void)map;
	(void)data;
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
	//(*data)->map_before_split     (*data)->hyusisharav
	data->splited_hyusisharav = ft_split(data->hyusisharav, '\n',
			MAX_SPLIT_CNT);
	free(data->hyusisharav);
	split = ft_split(res, '\n', MAX_SPLIT_CNT);
	free(res);
	if (parse_elements(&data) == -1)
	{
		free_matrix(split);
		free(data->map_before_split);
		free_matrix(data->splited_hyusisharav);
		return (-1);
	}
	if (is_there_nl_in_the_map(data->map_before_split) == -1)
	{
		free_matrix(split);
		free_matrix(data->splited_hyusisharav);
		free(data->map_before_split);
		return (-1);
	}
	data->splited_map = ft_split(data->map_before_split, '\n', MAX_SPLIT_CNT);
	if (check_map(split, data, &map) == -1)
	{
		free_matrix(data->splited_map);
		free_matrix(data->splited_hyusisharav);
		free(data->map_before_split);
		return (-1);
	}
	free_matrix(data->splited_map);
	free_matrix(data->splited_hyusisharav);
	free(data->map_before_split);
	free_matrix(map->grid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		return_value;

	return_value = 1;
	if (argc == 2)
	{
		(void)argv;
		init_all(&game);
		check_file(argv[1]);
		return_value = start_validation(argv[1], &game.config,
				&game.config.map);
		if (return_value < 0)
		{
			printf("Validation error!\n");
			exit(1);
		}
		else
			printf("Congratulations!\n");
		// flood_fill(&game.config.map);
		// free_matrix(res);
	}
	else
		return (write(2, "Error\n", 6), 1);
	// start_game(&game);
	return (0);
}
