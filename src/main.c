/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:58:52 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 14:30:02 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub[1];
	int		fd;
	int		ret;

	fd = 0;
	ret = 0;
	init_cub_struct(cub);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
	{
		ft_putstr_fd("Error\nMlx could not be initialized!\n", 2);
		ret = 1;
	}
	else if (!arg_check(ac, av, &fd))
		ret = 1;
	else if (!parsing(fd, cub))
		ret = 1;
	else
		ret = cub3D(cub);
	return (destroy_cub_struct(cub), ret);
}
