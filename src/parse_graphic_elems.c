/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_graphic_elems.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:17:11 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 15:51:57 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_graphic_elems(char *str, t_cub *cub)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (parse_texture(&str[2], cub->mlx_ptr, &cub->no));
	if (!ft_strncmp(str, "SO ", 3))
		return (parse_texture(&str[2], cub->mlx_ptr, &cub->so));
	if (!ft_strncmp(str, "EA ", 3))
		return (parse_texture(&str[2], cub->mlx_ptr, &cub->ea));
	if (!ft_strncmp(str, "WE ", 3))
		return (parse_texture(&str[2], cub->mlx_ptr, &cub->we));
	if (!ft_strncmp(str, "F ", 2))
		return (parse_color_code(&str[1], &cub->fl));
	if (!ft_strncmp(str, "C ", 2))
		return (parse_color_code(&str[1], &cub->ce));
	else
		return (ft_putstr_fd("Error\nIncorrect graphic element syntax!\n", 2), 0);
}

int	parse_texture(char *str, void *mlx_ptr, void **image_add)
{
	char	**tab;
	int		fd;
	int		len;

	fd = 0;
	tab = ft_split(str, ' ');
	if (!tab || !tab[0] || (tab[0] && tab[1]))
		return (ft_putstr_fd("Error\nIncorrect texture path syntax!\n", 2), 0);
	len = ft_strlen(tab[0]);
	if (len && tab[0][len - 1] == '\n')
		tab[0][len - 1] = '\0';
	if (!open_file(tab[0], &fd))
	{
		free_tab(tab);
		return (0);
	}
	close (fd);
	if (!xpm_to_image(tab[0], mlx_ptr, image_add))
	{
		free_tab(tab);
		return (0);
	}
	free_tab(tab);
	return (1);
}

int	parse_color_code(char *str, int *color_code_add)
{
	int	flag;
	int	color;
	int	i;

	i = 1;
	flag = 2;
	while (str[i] == ' ')
		i++;
	while (flag >= 0)
	{
		color = 0;
		if (!get_color(str, &i, &color))
			return (ft_putstr_fd("Error\nInvalid color code syntax!\n", 2), 0);
		if ((flag && str[i] != ',') || (!flag && str[i] != '\n'))
			return (ft_putstr_fd("Error\nInvalid color code syntax!\n", 2), 0);
		i++;
		if (flag)
			*color_code_add += color * 256 * flag;
		else
			*color_code_add += color;
		flag--;
	}
	return (1);
}

int	get_color(char *str, int *i, int *color)
{
	if (!str[*i] || str[*i] == '\n')
		return (0);
	*color = ft_atoi(&str[*i]);
	if (*color < 0 || *color > 255)
		return (0);
	(*i)++;
	if (*color >= 10)
		(*i)++;
	if (*color >= 100)
		(*i)++;
	return (1);
}
