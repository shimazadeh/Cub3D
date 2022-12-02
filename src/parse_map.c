/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:31:53 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 13:41:17 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_map(char *str, t_cub *cub)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] == '\n')
		i++;
	j = ft_strlen(str) - 1;
	while (j > 0 && str[j] == '\n')
		j--;
	str[j + 1] = '\0';
	if (ft_strstr(&str[i], "\n\n"))
	{
		ft_putstr_fd("Error\nMap is invalid!\n", 2);
		return (0);
	}
	cub->map = ft_split(&str[i], '\n');
	free(str);
	if (!parse_map2(i, j, flag, cub))
		return (0);
	return (1);
}

int	parse_map2(int i, int j, int flag, t_cub *cub)
{
	i = 0;
	while ((cub->map)[i])
	{
		j = 0;
		while ((cub->map)[i][j])
		{
			if (!map_pos_is_valid(i, j, &flag, cub))
			{
				ft_putstr_fd("Error\nMap is invalid!\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	map_pos_is_valid(int i, int j, int *flag, t_cub *cub)
{
	char	**map;

	map = cub->map;
	if (!map_pos_space(i, j, map))
		return (0);
	else if (!map_pos_zero(i, j, map))
		return (0);
	else if (!map_pos_pos(i, j, flag, map))
		return (0);
	else if (!ft_strchr("01 NESW", map[i][j]))
		return (0);
	if (ft_strchr("NESW", map[i][j]))
	{
		update_initial_pos(i, j, map[i][j], cub);
		map[i][j] = '0';
		*flag = 1;
	}
	return (1);
}
