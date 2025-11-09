/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:12 by arina             #+#    #+#             */
/*   Updated: 2025/11/09 18:53:33 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"

typedef struct s_texture
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
}   t_texture;

typedef struct s_color
{
    int     floor[3];   //(RGB)
    int     ceiling[3]; //(RGB)
}   t_color;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
}   t_map;

typedef struct s_config
{
    t_texture   textures;
    t_color     colors;
    t_map       map;
}   t_config;
   

char	*ft_strjoin_(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
void	print_error(char *error, char **str);
void	parse_elements(t_config *data, char **file);
int 	ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int 	is_white_space(char c);


#endif