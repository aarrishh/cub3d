/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:01:13 by arimanuk          #+#    #+#             */
/*   Updated: 2025/11/22 15:30:48 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*simulation(int fd, char **result, char *buffer, ssize_t *count_bytes)
{
	char	*str_join;

	str_join = NULL;
	while (nl_exists(buffer) == 0 && *count_bytes != 0)
	{
		free(buffer);
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return (NULL);
		*count_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*count_bytes == -1)
			return (free_func(buffer, result));
		buffer[*count_bytes] = '\0';
		str_join = ft_strjoin(*result, buffer);
		if (*result)
		{
			free (*result);
			*result = NULL;
		}
		*result = str_join;
	}
	free(buffer);
	return (*result);
}

int	nl_exists(char *buffer)
{
	int	i;

	i = 0;
	if (buffer == NULL)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*left_over(char *str_join)
{
	int		i;
	int		j;
	int		malloc_len;
	char	*res;

	j = 0;
	i = 0;
	while (str_join[i] && str_join[i] != '\n')
		i++;
	if (!str_join[i])
		return (NULL);
	malloc_len = ft_strlen(str_join) - i;
	if (malloc_len <= 0)
		return (NULL);
	res = (char *)malloc((malloc_len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i++;
	while (str_join[i])
		res[j++] = str_join[i++];
	res[j] = '\0';
	return (res);
}

char	*cur_line(char *str_join)
{
	int	i;

	i = 0;
	while (str_join[i] && str_join[i] != '\n')
		i++;
	if (str_join[i] && str_join[i] == '\n')
		return (ft_substr(str_join, 0, i + 1));
	return (ft_substr(str_join, 0, i));
}

char	*get_next_line(int fd)
{
	static char			*result;
	ssize_t				count_bytes;
	char				*return_str;
	char				*str_join;
	char				*buffer;

	str_join = NULL;
	buffer = NULL;
	count_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (check_read(&result));
	str_join = simulation(fd, &result, buffer, &count_bytes);
	if (result != NULL && *result == '\0' && count_bytes == 0)
		return (free_func(buffer, &result));
	if (!result)
		return (NULL);
	result = left_over(str_join);
	return_str = cur_line(str_join);
	free(str_join);
	return (return_str);
}
