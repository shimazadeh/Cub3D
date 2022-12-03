/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:55:32 by aguillar          #+#    #+#             */
/*   Updated: 2022/12/03 17:30:48 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_parsing_str(t_pars *pars)
{
	pars->ret = 0;
	pars->flag = 0;
	pars->map_str = NULL;
	pars->tmp = NULL;
	pars->str = 0;
}

int	parsing(int fd, t_cub *cub)
{
	t_pars	pars[1];

	init_parsing_str(pars);
	pars->str = get_next_line(fd);
	while (pars->str)
	{
		if (!pars->ret && pars->str[0] != '\n' && pars->flag < 6)
		{
			if (!parse_graphic_elems(pars->str, cub))
				pars->ret = 1;
			pars->flag++;
		}
		else if (!pars->ret)
		{
			pars->tmp = pars->map_str;
			pars->map_str = ft_strjoin(pars->tmp, pars->str);
			free(pars->tmp);
		}
		free(pars->str);
		pars->str = get_next_line(fd);
	}
	return (parsing_2(pars, fd, cub));
}

int	parsing_2(t_pars *pars, int fd, t_cub *cub)
{
	if (pars->ret)
	{
		close(fd);
		return (pars->ret);
	}
	if (pars->map_str)
		pars->flag++;
	if (!parse_map(pars->map_str, cub))
		return (0);
	if (pars->flag < 6)
		return (close(fd), \
			ft_putstr_fd("Error\nMissing texture element in file!\n", 2), 0);
	else if (pars->flag != 7)
		return (close(fd), \
			ft_putstr_fd("Error\nMissing map element in file!\n", 2), 0);
	return (1);
}
