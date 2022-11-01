/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:18:15 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/01 16:07:04 by aguillar         ###   ########.fr       */
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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;	
}				t_list;

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*no;
	void			*so;
	void			*ea;
	void			*we;
	int				fl;
	int				ce;
	char			**map;		
}				t_cub;

# define BUFFER_SIZE 100

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

void		parse_map(char *str, t_cub *cub);
int			map_pos_is_valid(int i, int j, int *flag, char **map);

// images.c

int		xpm_to_image(char *file, void *mlx_ptr, void **image_add);

// cub3D.c

int		cub3D(t_cub *cub);

// get_next_line_bonus.c

char		*get_next_line(int fd);
char		*get_next_line_2(int fd, char **tab, t_list *first, t_list *last);
t_list		*ft_expand_list(t_list *first, t_list *last, char *str, int size);
char		*ft_join_contents(t_list *first);

// libft

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		free_list(t_list *list);
void		free_tab(char **tab);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstnew_regular(void *content);
int			ft_lstsize(t_list *lst);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(const char *str, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(char *s1, int j);

#endif
