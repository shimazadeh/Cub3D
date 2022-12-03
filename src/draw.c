/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:59:27 by shabibol          #+#    #+#             */
/*   Updated: 2022/12/03 18:16:40 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pix_put(t_im *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bps - 8;
	pixel = img->addr + (y * img->line_length + x
			* (img->bps / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bps - 8 - i)) & 0xFF;
		i -= 8;
	}
	return ;
}

void	draw_line(int i, t_cub *cub)
{
	int		wall_height;
	int		start;
	int		j;

	wall_height = ((WINDOW_WIDTH / 2) / tan(33 * M_PI / 180)) / cub->pwdist;
	start = (WINDOW_LENGTH / 2) - wall_height / 2;
	j = 0;
	while (j < start)
	{
		if (i >= 0 && i < cub->width && j >= 0 && j < cub->height)
			img_pix_put(cub->img, i, j, cub->ce);
		j++;
	}
	j = draw_wall(cub, i, start, wall_height);
	while (j < 1080)
	{
		if (i >= 0 && i < cub->width && j >= 0 && j < cub->height)
			img_pix_put(cub->img, i, j, cub->fl);
		j++;
	}
}

int	draw_wall(t_cub *cub, int i, int start, int wall_height)
{
	int		j;
	double	offset;
	int		color;

	offset = 0;
	if (start < 0)
	{
		offset = (-start) * (64 / (double)wall_height);
		start = 0;
	}
	j = start - 1;
	while (++j < start + wall_height && j < 1080)
	{
		if (cub->cur_text == 'n')
			color = get_pix(cub->img_no, &offset, cub->text_offset);
		else if (cub->cur_text == 'e')
			color = get_pix(cub->img_ea, &offset, cub->text_offset);
		else if (cub->cur_text == 's')
			color = get_pix(cub->img_so, &offset, cub->text_offset);
		else
			color = get_pix(cub->img_we, &offset, cub->text_offset);
		img_pix_put(cub->img, i, j, color);
		offset += 64 / (double)wall_height;
	}
	return (j);
}

int	get_pix(t_im *img, double *offset, double text_offset)
{
	char	*pixel;

	pixel = img->addr + (((int)(*offset)) * img->line_length + \
	(int)text_offset * (img->bps / 8));
	return ((int)(((int *)pixel)[0]));
}
