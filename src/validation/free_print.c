/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:37 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 13:13:39 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_matrix(char **buffer)
{
	int	i;

	if (!buffer)
		return ;
	i = 0;
	while (buffer[i])
		free(buffer[i++]);
	free(buffer);
	buffer = NULL;
}

void	free_textures(t_config **t)
{
	if (((*t)->textures.no))
		free((*t)->textures.no);
	if (((*t)->textures.so))
		free((*t)->textures.so);
	if (((*t)->textures.we))
		free((*t)->textures.we);
	if (((*t)->textures.ea))
		free((*t)->textures.ea);
	(*t)->textures.no = NULL;
	(*t)->textures.so = NULL;
	(*t)->textures.we = NULL;
	(*t)->textures.ea = NULL;
}

void	free_array(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		free (buffer[i++]);
	free (buffer);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	a;

	a = 0;
	while (s[a])
	{
		write(fd, &s[a], 1);
		a++;
	}
}
