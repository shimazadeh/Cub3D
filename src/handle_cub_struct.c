/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cub_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:32 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 14:39:49 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_cub_struct(t_cub *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->fl = 0;
	cub->ce = 0;
	cub->map = NULL;
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
