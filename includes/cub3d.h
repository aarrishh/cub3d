/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:15:12 by arina             #+#    #+#             */
/*   Updated: 2025/12/14 16:06:07 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 700

# define MAX_SPLIT_CNT 0

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_texture
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_texture;

typedef struct s_color
{
	int			floor[3];
	int			ceiling[3];
	int			floor_int;
	int			ceiling_int;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_config
{
	t_texture	textures;
	t_color		colors;
	t_map		map;
	t_player	player;
	char		*hyusisharav;
	char		*map_before_split;
	char		**splited_hyusisharav;
	char		**splited_map;
}				t_config;

typedef struct s_ray
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		deltaDistX;
	double		deltaDistY;
	double		sideDistX;
	double		sideDistY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	double		perpWallDist;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

}				t_ray;

typedef struct s_img
{
	void		*img;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_game
{
	t_config	config;
	void		*mlx;
	void		*window;
	t_img		img;
}				t_game;

typedef struct s_colflag
{
	int			no_flag;
	int			so_flag;
	int			we_flag;
	int			ea_flag;
	int			f_flag;
	int			c_flag;
	int			map_flag;
}				t_colflag;

char			*ft_strjoin_(char *s1, char *s2);
char			**ft_split(char const *s, char c, int split_count);
char			*ft_strdup(const char *s);
char			*ft_strtrim(char const *s1, char const *set);
void			print_error(char *error, char **str);
int				parse_elements(t_config **data);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				is_white_space(char c);
void			free_matrix(char **buffer);
int				is_map_line(char *str, t_colflag *f);
void			print_matrix(char **str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			init_colflag(t_colflag *flag);
int				is_map_line_second(char *str);
char			**copy_map(char **str, t_map *map, int i);
void			flood_fill(t_map *map);
int				is_there_nl_in_the_map(char *map);
int				check_map(char **splitted_map, t_config *data, t_map **map);
void			check_file(char *file);
void			copy_number_two_in_map(t_map **map);
void			check_textures(t_texture texture);
int				ft_atoi(const char *str);

void			start_game(t_game *game);
int				close_window(t_game *game);
int				key_handler(int keycode, t_game *game);
void			put_pixels(t_img *img, int x, int y, int color);
void			draw_wall_line(t_game *game, int x, int start, int end);
void			raycasting(t_game *game);
int				render(t_game *game);

void			set_dir_plane(t_config *config, char p);
void			init_player(t_config *config);
void			move_player(t_game *game, double dx, double dy);

void			init_ray(t_game *game, int x, t_ray *ray);
void			calc_step_and_side(t_game *game, t_ray *ray);
void			perform_dda(t_game *game, t_ray *ray);
void			calc_wall_height(t_ray *ray);

#endif