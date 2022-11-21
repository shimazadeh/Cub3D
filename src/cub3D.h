/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:18:15 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/21 16:08:35 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_hit
{
	bool 			v_hit;
	bool			h_hit;
	double			v_hitX;
	double			v_hitY;
	char			v_text;
	double			h_hitX;
	double			h_hitY;
	char			h_text;

}				t_hit;


typedef	struct s_im
{
	void	*mlx_img;
	char	*addr;
	int		bps;
	int		line_length;
	int		endian;
}				t_im;

typedef struct s_cub
{
	int				maph;
	int				mapw;
	void			*line;
	double			hookX;
	double			hookY;
	double			hookangle;
	int				ret;
	int				fd;
	void			*mlx_ptr;
	void			*win_ptr;
	t_im			img[1];
	void			*no;
	void			*so;
	void			*ea;
	void			*we;
	int				fl;
	int				ce;
	char			**map;
	int				height;
	int				width;
	double			posX;
	double			posY;
	int				base_angle;
	double			cur_angle;
	double			hitX;
	double			hitY;
	double			pwdist;
	double			dist;
	char			prev_text;
	char			cur_text;
	int				text_offset;
	bool			right;
	bool			left;
	bool			up;
	bool			down;
	t_hit			*hit_str;
	
}				t_cub;


# define BUFFER_SIZE 100
# define WINDOW_WIDTH = 1920;
# define WINDOW_LENGTH = 1080;

# define WALL_STRIP_THICK = 1;
# define NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_THICK;

// arg_check.c
int		arg_check(int ac, char **av, int *fd_add);
int		open_file(char *str, int *fd_add);

// handle_cub_struct.c

void	init_cub_struct(t_cub *cub);
void	destroy_cub_struct(t_cub *cub);

// parsing.c

int		parsing(int fd, t_cub *cub);
int		get_texture(char *str, t_cub *cub);

// parse_graphic_elems.c

int		parse_graphic_elems(char *str, t_cub *cub);
int		parse_texture(char *str, void *mlx_ptr, void **image_add);
int		parse_color_code(char *str, int *color_code_add);
int		get_color(char *str, int *i, int *color);

// parse_map.c

void	parse_map(char *str, t_cub *cub);
int		map_pos_is_valid(int i, int j, int *flag, t_cub *cub);

// images.c

int		xpm_to_image(char *file, void *mlx_ptr, void **image_add);

// cub3D.c

void	cub3D(t_cub *cub);
void	cub3D_render_pos(t_cub *cub, t_hit *hit);


// get_next_line_bonus.c

char	*get_next_line(int fd);
char	*get_next_line_2(int fd, char **tab, t_list *first, t_list *last);
t_list	*ft_expand_list(t_list *first, t_list *last, char *str, int size);
char	*ft_join_contents(t_list *first);

// ft_exit.c

int		ft_exit(t_cub *cub);

// hooks.c

int		handle_no_event(void *data);
int		key_hook(int keycode, t_cub *cub);

// update_initial_pos.c

void	update_initial_pos(int i, int j, char dir, t_cub *cub);

// libft

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	free_list(t_list *list);
void	free_tab(char **tab);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstnew_regular(void *content);
int		ft_lstsize(t_list *lst);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(const char *str, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strndup(char *s1, int j);
char	*ft_strstr(const char *haystack, const char *needle);


// bordel

void	draw_line(int i, t_cub *cub);
void	get_perpwalldist(t_cub *cub);
void	init_hit_struct(t_hit *hit);
void	get_next_hitpoint(t_cub *cub, t_hit *hit);
void	get_cur_angle_and_dir(t_cub *cub, int i);
double	calculate_distance(double x1, double x2, double y1, double y2);
void	select_shortest_hitpoint(t_hit *hit, t_cub *cub);
void	check_if_hit_v(t_hit *hit, t_cub *cub);
void	check_if_hit_h(t_hit *hit, t_cub *cub);
void	get_initial_hhit(t_hit *hit, t_cub *cub);
void	get_initial_vhit(t_hit *hit, t_cub *cub);
void	update_data(t_hit *hit, t_cub *cub);

#endif
