/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_for_trim.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:57:56 by arimanuk          #+#    #+#             */
/*   Updated: 2025/11/09 14:23:33 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

void	print_error(char *error, char **str)
{
	free_matrix(str);
	write(1, "Error\n", 6);
	write(1, error, ft_strlen(error));
	exit(1);
}

int	check_trim(char const *s1, char const *set, int i)
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

int	check_new_line_1(char const *s1, char c, int i)
{
	while (i > 0 && s1[i] != c)
		i--;
	return (i);
}

int	cal_ind(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (check_trim(s1, set, i) == 0)
			i++;
		else if (check_trim(s1, set, i) == -1)
			return (check_new_line_1(s1, '\n', i));
	}
	return (i);
}

int	cal_end(const char *s1, const char *set, int end, int i)
{
	while (end >= i)
	{
		if (check_trim(s1, set, end) == 0)
			end--;
		else if (check_trim(s1, set, end) == -1)
			break ;
	}
	return (end);
}

void	check_new_line(char *res)
{
	int	i;

	i = 0;
	if (res)
	{
		while (res[i] && res[i + 1])
		{
			if (res[i] == '\n' && res[i + 1] == '\n')
			{
				free(res);
				print_error("Validation error\n", NULL);
			}
			i++;
		}
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*a;
	int		end;
	int		malloc_i;

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
	if (s1)
		free ((char *)s1);
	return (a);
}
