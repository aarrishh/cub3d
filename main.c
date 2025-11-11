/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2025/11/11 19:45:09 by mabaghda         ###   ########.fr       */
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
			write(1, "Invalid map's name!\n", 20);
			exit(1);
		}
		else
			break ;
	}
}

void	check_map(char **str)
{
	int		i;
	int		j;
	char	**split;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (is_white_space(str[i][j] == 1))
			j++;
		split = ft_split(str[i], ' ');
		while (split[count])
			count++;
		printf("count->%d\ntoxs->%d\n\n", count, i + 1);
		i++;
	}
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
	split = ft_split(res, '\n');
	free(res);
	parse_elements(&data, split);
	return (split);
}

int	main(int argc, char **argv)
{
	char	**res;

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
		return (write(2, "Error\n", 6), 1);
	return (0);
}
