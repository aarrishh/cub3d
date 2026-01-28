/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2026/01/28 15:09:12 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**prepare_splits(char *res, t_config *data)
{
	char	**split;

	res = ft_strtrim(res, "\n\v\t\r\f ");
	find_index_after_colors(res, &data);
	data->splited_hyusisharav = ft_split(data->hyusisharav,
			'\n', MAX_SPLIT_CNT);
	free(data->hyusisharav);
	split = ft_split(res, '\n', MAX_SPLIT_CNT);
	free(res);
	return (split);
}

static int	parse_part(t_config *data, char **split)
{
	if (parse_elements(&data) == -1)
	{
		free_matrix(split);
		free(data->map_before_split);
		free_matrix(data->splited_hyusisharav);
		return (-1);
	}
	return (0);
}

static int	map_validation_part(t_config *data, char **split, t_map *map)
{
	if (is_there_nl_in_the_map(data->map_before_split) == -1)
	{
		free_textures(&data);
		free_matrix(split);
		free_matrix(data->splited_hyusisharav);
		free(data->map_before_split);
		return (-1);
	}
	data->splited_map = ft_split(data->map_before_split,
			'\n', MAX_SPLIT_CNT);
	if (check_map(split, data, &map) == -1)
	{
		free_matrix(data->splited_map);
		free_matrix(data->splited_hyusisharav);
		free(data->map_before_split);
		free_textures(&data);
		return (-1);
	}
	return (0);
}

int	start_validation(char *file, t_config *data, t_map *map)
{
	char	*res;
	char	**split;

	(void)map;
	(void)data;
	res = read_file(file);
	if (!res)
		return (-1);
	split = prepare_splits(res, data);
	if (parse_part(data, split) == -1)
		return (-1);
	if (map_validation_part(data, split, map) == -1)
		return (-1);
	free_matrix(data->splited_map);
	free_matrix(data->splited_hyusisharav);
	free(data->map_before_split);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		return_value;

	return_value = 1;
	if (argc == 2)
	{
		init_all(&game);
		check_file(argv[1]);
		return_value = start_validation(argv[1], &game.config,
				&game.config.map);
		if (return_value < 0)
			return (ft_putstr_fd("Validation error!\n", 2), -1);
		else
		{
			if ((flood_fill(&game.config.map, &game.config)) == -1)
				return (ft_putstr_fd("Map is not closed\n", 2), -1);
		}
	}
	else
		return (ft_putstr_fd("Error\n", 2), 1);
	start_game(&game);
	return (0);
}
