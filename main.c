/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2025/11/26 21:30:21 by arina            ###   ########.fr       */
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
		else if (is_map_line(str[i]) == 1 && check_tex_f(&flag) == 1)
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

int check_map(char **splitted_map, char **sr)
{
	int	i;

	i = 0;
	while(sr[i])
	{
		if (is_map_line(sr[i]) == -1){
			printf("stuc\n");
			return (-1);
		}
		i++;
	}
	if (check_sequence(splitted_map) == -1)
	{
			printf("aaystuc\n");
		return (-1);
	}
	
	return (0);
}

void find_index_after_colors(char *res, t_config *data)
{
	int i = 0;
	int finish = 0;
	
	while (res[i])
		i++;
	while (i >= 0 && res[i] != 'F' && res[i] != 'C')
		i--;
	while (i >=0 && res[i] && res[i] != '\n')
		i++;
	finish = i;
	printf("finish...%d\n", finish);
	while (i >=0 && res[finish])
		finish++;
	data->hyusisharav = ft_substr(res, 0, i);
	data->map_before_split = ft_substr(res, i + 1, finish);
	printf("*****%s\n", data->hyusisharav);
	printf("*****%s\n", data->map_before_split);
}


char	**start_validation(char *file)
{
	int			fd;
	char		*line;
	char		*res;
	char		**split;
	t_config	data;

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
	data.splited_hyusisharav = ft_split(data.hyusisharav, '\n', MAX_SPLIT_CNT);
	split = ft_split(res, '\n', MAX_SPLIT_CNT);
	// print_matri/x(split);
	free(res);
	if (parse_elements(&data) == -1)
		return(NULL);
	//vrdoi mtacac checky anel
	data.splited_map = ft_split(data.map_before_split, '\n', MAX_SPLIT_CNT);
	if (check_map(split, data.splited_map) == -1)
		return (NULL);
		// free_matrix(split);
	// *split = NULL;
	return (data.splited_map);//chshtel inch return anel
}


int	main(int argc, char **argv)
{
	char		**res;

	res = NULL;
	if (argc == 2)
	{
		check_file(argv[1]);
		res = start_validation(argv[1]);
		if (!res || !(*res))
			print_error("Validation error\n", res);
		// check(res, &map);
		// free_matrix(res);
	}
	else
		return (write (2, "Error\n", 6), 1);
	return (0);
}
