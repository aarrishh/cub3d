/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_trim.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:57:56 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/10 18:26:43 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	free_matrix(char **buffer)
{
	int	ind;

	ind = 0;
	if (buffer)
	{
		while (buffer[ind])
			free(buffer[ind++]);
		free(buffer);
		buffer = NULL;
	}
	*buffer = NULL;
}

static int	check(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s1[i])
			return (0);
		j++;
	}
	return (-1);
}

static int	cal_ind(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (check(s1, set, i) == 0)
			i++;
		else if (check(s1, set, i) == -1)
			break ;
	}
	return (i);
}

static int	cal_end(const char *s1, const char *set, int end, int i)
{
	while (end >= i)
	{
		if (check(s1, set, end) == 0)
			end--;
		else if (check(s1, set, end) == -1)
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int i;
	char *a;
	int end;
	int malloc_i;

	if (!s1 || !set)
		return (NULL);
	i = cal_ind(s1, set);
	end = ft_strlen(s1) - 1;
	end = cal_end(s1, set, end, i);
	malloc_i = 0;
	a = (char *)malloc((end - i + 2) * sizeof(char));
	if (a == NULL)
		return (NULL);
	while (i < end + 1)
		a[malloc_i++] = s1[i++];
	a[malloc_i] = '\0';
	return (a);
}