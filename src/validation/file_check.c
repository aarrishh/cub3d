/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:08:37 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:48:06 by arimanuk         ###   ########.fr       */
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
			ft_putstr_fd("Invalid map's name!\n", 2);
			exit(1);
		}
		else
			break ;
	}
}

char	*read_file(char *file)
{
	int		fd;
	char	*line;
	char	*res;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_putstr_fd("Cannot open file\n", 2);
	line = get_next_line(fd);
	if (!line)
		return (ft_putstr_fd("Empty file\n", 2), NULL);
	res = ft_strdup("");
	while (line != NULL)
	{
		res = ft_strjoin_(res, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (res);
}
