/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:18:49 by arina             #+#    #+#             */
/*   Updated: 2026/01/28 13:19:32 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	change_flag_and_found_value(int *found, int *flag_plus_plus)
{
	(*found) = 2;
	(*flag_plus_plus)++;
}

int	is_map_line_second(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}

static void	update_found_for_digit(int *found)
{
	if (*found == 2 || *found == 3)
		*found = 3;
	else
		*found = 1;
}

int	is_map_line(char *str, t_colflag *f)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0')
			update_found_for_digit(&found);
		else if (str[i] == 'N')
			change_flag_and_found_value(&found, &f->no_flag);
		else if (str[i] == 'W')
			change_flag_and_found_value(&found, &f->we_flag);
		else if (str[i] == 'E')
			change_flag_and_found_value(&found, &f->ea_flag);
		else if (str[i] == 'S')
			change_flag_and_found_value(&found, &f->so_flag);
		else if (!is_white_space(str[i]))
			return (-1);
		i++;
	}
	return (found);
}

int	check_textures(t_texture texture)
{
	if (loop_for_check_textures(texture.no) == -1)
		return (-1);
	if (loop_for_check_textures(texture.so) == -1)
		return (-1);
	if (loop_for_check_textures(texture.we) == -1)
		return (-1);
	if (loop_for_check_textures(texture.ea) == -1)
		return (-1);
	return (0);
}
