/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:12 by arina             #+#    #+#             */
/*   Updated: 2025/12/02 21:16:20 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../get_next_line/get_next_line.h"

typedef struct s_texture
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
}   t_texture;

typedef struct s_color
{
    int     floor[3];
    int     ceiling[3];
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
    char		*hyusisharav;
    char		*map_before_split;
	char		**splited_hyusisharav;
	char		**splited_map;
}   t_config;

typedef struct s_colflag
{
    int no_flag;
    int so_flag;
    int we_flag;
    int ea_flag;
    int f_flag;
    int c_flag;
    int map_flag;
}   t_colflag;

#define MAX_SPLIT_CNT 0

char	*ft_strjoin_(char *s1, char *s2);
char	**ft_split(char const *s, char c, int split_count);
char	*ft_strdup(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
void	print_error(char *error, char **str);
int 	parse_elements(t_config **data);
int 	ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int 	is_white_space(char c);
void	free_matrix(char **buffer);
int	    is_map_line(char *str, t_colflag *f);
void    print_matrix(char **str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void    init_colflag(t_colflag *flag);
int	    is_map_line_second(char *str);
char	**copy_map(char **str, t_map *map, int i);
void    flood_fill(t_map *map);
int     is_there_nl_in_the_map(char *map);
int 	check_map(char **splitted_map, t_config *data, t_map **map);
void	check_file(char *file);
void 	copy_number_two_in_map(t_map **map);

#endif