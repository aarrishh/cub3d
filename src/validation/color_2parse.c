/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_2parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:52:26 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:14:50 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	color_value(char *s)
{
	int	value;

	value = ft_atoi(s);
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("RGB value out of range (0-255)\n", 2);
		return (-1);
	}
	return (value);
}

int	comma_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		ft_putstr_fd("Invalid RGB format\n", 2);
		return (-1);
	}
	return (0);
}

void	check_digits(const char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] < '0' || s[i] > '9')
	{
		ft_putstr_fd("RGB must contain only digits\n", 2);
		exit(1);
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			exit(1);
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
