/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_num2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:16:12 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:17:20 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

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
