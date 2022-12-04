/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points_calculation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:30:27 by shabibol          #+#    #+#             */
/*   Updated: 2022/11/28 17:30:29 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_data(t_hit *hit, t_cub *cub)
{
	if (hit->v_hit)
	{
		cub->hitx = hit->v_hitx;
		cub->hity = hit->v_hity;
		cub->prev_text = cub->cur_text;
		cub->cur_text = hit->v_text;
		cub->text_offset = (hit->v_hity - floor(hit->v_hity)) * 64;
	}
	else
	{
		cub->hitx = hit->h_hitx;
		cub->hity = hit->h_hity;
		cub->prev_text = cub->cur_text;
		cub->cur_text = hit->h_text;
		cub->text_offset = (hit->h_hitx - floor(hit->h_hitx)) * 64;
	}
}

void	get_initial_vhit(t_hit *hit, t_cub *cub)
{
	double	delta_x;

	hit->v_hitx = floor(cub->posx);
	if (cub->right)
		hit->v_hitx += 1;
	delta_x = cub->posx - hit->v_hitx;
	hit->v_hity = cub->posy + (delta_x * tan(cub->cur_angle * M_PI / 180));
	check_if_hit_v(hit, cub);
}

void	get_initial_hhit(t_hit *hit, t_cub *cub)
{
	double	delta_y;

	hit->h_hity = floor(cub->posy);
	if (cub->down)
		hit->h_hity += 1;
	delta_y = cub->posy - hit->h_hity;
	hit->h_hitx = cub->posx + delta_y / tan(cub->cur_angle * (M_PI / 180));
	check_if_hit_h(hit, cub);
}

bool	check_if_hit_h(t_hit *hit, t_cub *cub)
{
	int		i;
	int		j;
	int		text;

	j = hit->h_hitx;
	i = 0;
	text = 0;
	if (cub->up)
	{
		i = hit->h_hity - 1;
		text = 'n';
	}
	else
	{
		i = hit->h_hity;
		text = 's';
	}
	if (i < 0 || i >= cub->maph || j < 0 || j >= cub->mapw)
		return (false);
	if (cub->map[i][j] == '1')
	{
		hit->h_hit = 1;
		hit->h_text = text;
	}
	return (true);
}

bool	check_if_hit_v(t_hit *hit, t_cub *cub)
{
	int		i;
	int		j;
	int		text;

	i = hit->v_hity;
	j = 0;
	text = 0;
	if (cub->left)
	{
		j = hit->v_hitx - 1;
		text = 'w';
	}
	else
	{
		j = hit->v_hitx;
		text = 'e';
	}
	if (i < 0 || i >= cub->maph || j < 0 || j >= cub->mapw)
		return (false);
	if (cub->map[i][j] == '1')
	{
		hit->v_hit = 1;
		hit->v_text = text;
	}
	return (true);
}
