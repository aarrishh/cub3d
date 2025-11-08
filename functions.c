/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:41:46 by arina             #+#    #+#             */
/*   Updated: 2025/10/01 21:06:45 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*a;
	int		i;
	int		j;
	int		s_len;

	i = 0;
	j = 0;
	s_len = (ft_strlen(s1) + ft_strlen(s2));
	a = (char *)malloc((s_len + 1) * sizeof(char));
	if (a == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		a[i + j] = s2[j];
		j++;
	}
	a[i + j] = '\0';
	if (s1)
		free (s1);
	return (a);
}

char	*ft_strdup(const char *s)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	i = 0;
	while (s[i])
	{
		buffer[i] = s[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
