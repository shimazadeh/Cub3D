/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_keycodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:59:41 by shabibol          #+#    #+#             */
/*   Updated: 2022/12/01 16:59:42 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_keycodes(t_cub *cub)
{
	int	dir;

	dir = cub->hookangle + 33;
	if (dir > 359)
		dir -= 360;
	update_keycodes_ns(dir, cub);
	update_keycodes_ew(dir, cub);
}

void	update_keycodes_ns(int dir, t_cub *cub)
{
	if ((dir > 45 && dir <= 135))
	{
		cub->xk_n = XK_w;
		cub->xk_s = XK_s;
		cub->xk_w = XK_a;
		cub->xk_e = XK_d;
	}
	else if (dir > 225 && dir <= 315)
	{
		cub->xk_n = XK_s;
		cub->xk_s = XK_w;
		cub->xk_w = XK_d;
		cub->xk_e = XK_a;
	}
}

void	update_keycodes_ew(int dir, t_cub *cub)
{
	if (dir > 135 && dir <= 225)
	{
		cub->xk_n = XK_d;
		cub->xk_s = XK_a;
		cub->xk_w = XK_w;
		cub->xk_e = XK_s;
	}
	else if (dir > 315 && dir <= 360)
	{
		cub->xk_n = XK_a;
		cub->xk_s = XK_d;
		cub->xk_w = XK_s;
		cub->xk_e = XK_w;
	}
}
