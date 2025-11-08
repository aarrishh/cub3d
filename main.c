/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 22:01:55 by arina             #+#    #+#             */
/*   Updated: 2025/11/07 21:25:46 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *error, char **str)
{
	(void)str;
	// free_matrix(str);
	write(1, "Error\n", 6);
	write(1, error, ft_strlen(error));
	exit(1);
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

int	check_symbols(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		// if ((str[i] != 'N' || str[i] != 'W' || 
		// 	str[i] != 'E' || str[i] != 'S' || 
		// 	str[i] != 0 || str[i] != 1) || 
		// 	(str[i] <= 9 || str[i] >= 12))
		// 	return (-1);
		if (str[i] <= 9 || str[i] >= 12)
			return (-2);
		i++;
	}
	return (0);
}

char **remove_spaces_and_tabs_line_from_map(char **split)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (split[i])
	{
		if (check_symbols(split[i]) == 0)
			
		i++;
	}
}


char	**start_validation(char *file)
{
	int		fd;
	char	*line;
	char	*res;
	char	**split;

	// res = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Can not open file\n", NULL);
	line = get_next_line(fd);
	res = ft_strdup("");
	while (line != NULL)
	{
		res = ft_strjoin_(res, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	split = ft_split(res, '\n');
	remove_spaces_and_tabs_line_from_map(split);
	int i = 0;
	while (split[i])
		printf("%s->>>\n", split[i++]);
	return (NULL);
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
