/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:59:27 by shabibol          #+#    #+#             */
/*   Updated: 2022/12/01 16:59:30 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	img_pix_put(t_cub *cub, t_im *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x >= 0 && x < cub->width && y >= 0 && y < cub->height)
	{
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
	}
	return ;
}

void	draw_line(int i, t_cub *cub)
{
	int		wall_height;
	int		start;
	int		j;
	int		k;
	double	offset;
	double	ratio;

	offset = 0;
	k = i + 1;
	wall_height = ((WINDOW_WIDTH / 2) / tan(33 * M_PI / 180)) / cub->pwdist;
	start = (WINDOW_LENGTH / 2) - wall_height / 2;
	ratio = 64 / (double)wall_height;
	if (cub->prev_text == cub->cur_text)
	{
		cub->text_offset += ratio;
		if (cub->text_offset >= 64)
			cub->text_offset = 0;
	}
	else
		cub->text_offset = 0;
	while (i < k)
	{
		j = 0;
		while (j < start)
		{
			img_pix_put(cub, cub->img, i, j, cub->fl);
			j++;
		}
		while (j < start + wall_height)
		{
			if (cub->cur_text == 'n')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->img_no, ratio, &offset, cub->text_offset));
			else if (cub->cur_text == 'e')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->img_ea, ratio, &offset, cub->text_offset));
			else if (cub->cur_text == 's')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->img_so, ratio, &offset, cub->text_offset));
			else if (cub->cur_text == 'w')
				img_pix_put(cub, cub->img, i, j, get_pix(cub->img_we, ratio, &offset, cub->text_offset));
			j++;
		}
		while (j < 1080)
		{
			img_pix_put(cub, cub->img, i, j, cub->ce);
			j++;
		}
		i++;
	}
//	exit(1);
}

int	get_pix(t_im *img, double ratio, double *offset, double text_offset)
{
	char	*pixel;

	pixel = img->addr + ((int)(*offset) * img->line_length + (int)text_offset * (img->bps / 8));
	*offset += ratio;
//	printf("img add %s, pixel  value %d with line per length %d bps of %d\n",img->addr, (unsigned int)(*pixel), img->line_length, img->bps);
//	printf("endian %d\n", img->endian);
	return ((int)(((int *)pixel)[0]));
}
