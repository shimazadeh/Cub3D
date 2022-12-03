/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigonometry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:04:03 by aguillar          #+#    #+#             */
/*   Updated: 2022/12/03 18:13:09 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	ft_tan(int angle, t_cub *cub)
{
	return (cub->tan[angle]);
}

double	ft_sin(int angle, t_cub *cub)
{
	return (cub->sin[angle]);
}

double	ft_cos(int angle, t_cub *cub)
{
	return (cub->cos[angle]);
}