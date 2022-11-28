/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cub_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:32 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/21 16:02:47 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub_struct(t_cub *cub)
{
	cub->hookx = 0;
	cub->hooky = 0;
	cub->hookangle = 0;
	cub->ret = 0;
	cub->fd = 0;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->fl = 0;
	cub->ce = 0;
	cub->map = NULL;
	cub->height = 1080;
	cub->width = 1920;
	cub->posx = 0;
	cub->posy = 0;

	cub->img->mlx_img = NULL;
	cub->img->addr = NULL;
	cub->img->bps = 0;
	cub->img->line_length = 0;
	cub->img->endian = 0;

	cub->base_angle = 0;
	cub->cur_angle = 0;
	cub->hitx = 0;
	cub->hity = 0;
	cub->pwdist = 0;
	cub->dist = 0;
	cub->cur_text = 0;
	cub->prev_text = 0;
	cub->text_offset = 0;
	cub->right = false;
	cub->left = false;
	cub->up = false;
	cub->down = false;

}

void	destroy_cub_struct(t_cub *cub)
{
	if (cub->win_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->no)
		mlx_destroy_image(cub->mlx_ptr, cub->no);
	if (cub->so)
		mlx_destroy_image(cub->mlx_ptr, cub->so);
	if (cub->ea)
		mlx_destroy_image(cub->mlx_ptr, cub->ea);
	if (cub->we)
		mlx_destroy_image(cub->mlx_ptr, cub->we);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	if (cub->map)
		free_tab(cub->map);
}
