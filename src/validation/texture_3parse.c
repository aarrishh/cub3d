/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_3parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:58:51 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:25:11 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		return (1);
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
			return (ft_putstr_fd("Invalid line in configuration\n", 2), -1);
		i++;
	}
	if (check_tex_f(&flag) != 2)
		return (-1);
	return (0);
}

int	loop_for_check_textures(char *file)
{
	if (!ends_with_xpm(file))
	{
		ft_putstr_fd("Invalid texture's name!\n", 2);
		return (-1);
	}
	return (0);
}
