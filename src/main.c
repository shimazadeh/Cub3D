/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:58:52 by aguillar          #+#    #+#             */
/*   Updated: 2022/12/03 17:56:56 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub[1];

	init_cub_struct(cub);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
		ft_putstr_fd("Error\nMlx could not be initialized!\n", 2);
		cub->ret = 1;
	}
	else if (!arg_check(ac, av, &(cub->fd)))
		cub->ret = 1;
	else if (!parsing(cub->fd, cub))
		cub->ret = 1;
	else
		cub3d(cub);
	ft_exit(cub);
	return (0);
}
