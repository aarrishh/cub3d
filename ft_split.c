/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 20:33:09 by arina             #+#    #+#             */
/*   Updated: 2025/10/01 20:49:11 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*my_strncpy(char *dest, const char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	foo_sum_tar(char const *s, char c)
{
	int	sum_tar;

	sum_tar = 0;
	while (*s == c)
		s++;
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (sum_tar);
		}
		else
		{
			s++;
			sum_tar++;
		}
	}
	return (sum_tar);
}

int	check(char **arr, const char *s, char c, int count)
{
	int	i;
	int	len_word;

	i = 0;
	while (i < count)
	{
		while (*s == c)
			s++;
		len_word = foo_sum_tar(s, c);
		arr[i] = malloc(sizeof(char) * (len_word + 1));
		if (!arr[i])
		{
			while (i >= 0)
				free(arr[i--]);
			free(arr);
			return (1);
		}
		my_strncpy(arr[i], s, len_word);
		arr[i][len_word] = '\0';
		s += (len_word + 1);
		i++;
	}
	return (0);
}

int	func_count_word(const char *s, char c)
{
	int	i;
	int	count;
	int	ban;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
		{
			i++;
			ban = 0;
		}
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			ban = 1;
		}
		if (ban == 1)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		count_word;
	char	**arr;

	if (s == NULL)
		return (NULL);
	count_word = func_count_word(s, c);
	arr = malloc(sizeof(char *) * (count_word + 1));
	if (!arr)
		return (NULL);
	arr[count_word] = NULL;
	if (check(arr, s, c, count_word))
		return (NULL);
	return (arr);
}