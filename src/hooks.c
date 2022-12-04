/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:51 by aguillar          #+#    #+#             */
/*   Updated: 2022/12/03 18:52:00 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_no_event(void *data)
{
	(void)data;
	return (0);
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == XK_Escape)
		ft_exit(cub);
	else if (keycode == XK_w || keycode == XK_s \
	|| keycode == XK_a || keycode == XK_d || \
	keycode == XK_Right || keycode == XK_Left)
	{
		if (keycode == XK_w || keycode == XK_s \
		|| keycode == XK_a || keycode == XK_d)
			update_positions(keycode, cub, norm(cub->hookangle + 33));
		else if (keycode == XK_Right)
		{
			cub->hookangle -= 1;
			if (cub->hookangle == -1)
				cub->hookangle = 359;
		}
		else if (keycode == XK_Left)
		{
			cub->hookangle += 1;
			if (cub->hookangle == 360)
				cub->hookangle = 0;
		}
		cub3d_render_pos(cub, cub->hit_str);
	}
	return (1);
}

int	norm(int theta)
{
	if (theta > 359)
		theta -= 360;
	else if (theta < 0)
		theta += 360;
	return (theta);
}

void	check_location(t_cub *cub, double x, double y)
{
	int	i;
	int	j;

	i = (int)(y + 0.000001);
	j = (int)(x + 0.000001);
	if (i >= 0 && i < cub->height && j >= 0 && j < cub->width)
	{
		if (cub->map[i][j] == '0')
		{
			cub->hookx = x;
			cub->hooky = y;
		}
	}
}

void	update_positions(int keycode, t_cub *cub, int n)
{
	double	tmpx;
	double	tmpy;
	int		angle;

	tmpx = 0;
	tmpy = 0;
	angle = n;
	if (keycode == XK_w)
		angle = n;
	else if (keycode == XK_s)
		angle = n + 180;
	else if (keycode == XK_d)
		angle = n - 90;
	else if (keycode == XK_a)
		angle = n + 90;
	tmpx = cub->hookx + 0.1 * (cos(angle * M_PI / 180));
	tmpy = cub->hooky - 0.1 * (sin(angle * M_PI / 180));
	check_location(cub, tmpx, tmpy);
}
