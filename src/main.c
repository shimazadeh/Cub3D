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
	{
		set_map_size(cub);
		cub3d(cub);
	}
	ft_exit(cub);
	return (0);
}

void	set_map_size(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cub->map[i])
		i++;
	while (cub->map[0][j])
		j++;
	cub->maph = i;
	cub->mapw = j;
}

/*
1.uneven map size ==>limit the search to strlen of &map[i][j]
*/
