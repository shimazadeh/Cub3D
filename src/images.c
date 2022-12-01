/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:17:46 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 14:39:17 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	xpm_to_image(char *file, void *mlx_ptr, void **image_add, t_im *img)
{
	int	i;
	int	j;

	i = 64;
	j = 64;
	*image_add = mlx_xpm_file_to_image(mlx_ptr, file, &i, &j);
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bps, \
	&img->line_length, &img->endian);
	if (!image_add)
	{
		ft_putstr_fd("Error\nImpossible to create image from file!\n", 2);
		return (0);
	}
	return (1);
}
