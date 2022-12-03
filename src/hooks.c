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
	int		i;
	int		j;

	i = (int)floor(y);
	j = (int)floor(x);
	if (map[i][j] == '0')
	{
		cub->hookx = x;
		cub->hooky = y;
	}
}

void	update_positions(int keycode, t_cub *cub, int n)
{
	double tmpX;
	double tmpY;

	if (keycode == XK_w)
	{
		tmpX = cub->hookx + 0.1 * (cos(n * M_PI / 180));
		tmpY = cub->hooky - 0.1 * (sin(n * M_PI / 180));
		check_location(cub, tmpX, tmpY);
	}
	else if (keycode == XK_s \
		&& cub->map[(int)(cub->posy + 0.100001)][(int)(cub->posx)] == '0')
	{
		cub->hooky -= 0.1 * (sin(norm(n + 180) * M_PI / 180));
		cub->hookx += 0.1 * (cos(norm(n + 180) * M_PI / 180));
	}
	else if (keycode == XK_d \
		&& cub->map[(int)(cub->posy)][(int)(cub->posx + 0.100001)] == '0')
	{
		cub->hooky -= 0.1 * (sin(norm(n - 90) * M_PI / 180));
		cub->hookx += 0.1 * (cos(norm(n - 90) * M_PI / 180));
	}
	else if (keycode == XK_a \
		&& cub->map[(int)(cub->posy)][(int)(cub->posx - 0.100001)] == '0')
	{
		cub->hooky -= 0.1 * (sin(norm(n + 90) * M_PI / 180));
		cub->hookx += 0.1 * (cos(norm(n + 90) * M_PI / 180));
	}
}
