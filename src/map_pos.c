/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:31:53 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 13:41:17 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	map_pos_zero(int i, int j, char **map)
{
	if (map[i][j] == '0' \
		&& (!i || !((int)ft_strlen(map[i - 1]) > j) \
		|| !j \
		|| !map[i + 1] || !((int)ft_strlen(map[i + 1]) > j) \
		|| !map[i][j + 1] || !ft_strchr("01NESW", map[i - 1][j]) \
		|| !ft_strchr("01NESW", map[i][j + 1]) \
		|| !ft_strchr("01NESW", map[i + 1][j]) \
		|| !ft_strchr("01NESW", map[i][j - 1])))
		return (0);
	return (1);
}

int	map_pos_pos(int i, int j, int *flag, char **map)
{
	if (ft_strchr("NESW", map[i][j]) \
		&& (*flag || !i || !((int)ft_strlen(map[i - 1]) > j) \
		|| !j || !map[i + 1] \
		|| !((int)ft_strlen(map[i + 1]) > j) || !map[i][j + 1] \
		|| !ft_strchr("01NESW", map[i - 1][j]) \
		|| !ft_strchr("01NESW", map[i][j + 1]) \
		|| !ft_strchr("01NESW", map[i + 1][j]) \
		|| !ft_strchr("01NESW", map[i][j - 1])))
		return (0);
	return (1);
}

int	map_pos_space(int i, int j, char **map)
{
	if (map[i][j] == ' ' \
		&& ((i && ((int)ft_strlen(map[i - 1]) > j) \
		&& !ft_strchr("1 ", map[i - 1][j])) \
		|| (map[i][j + 1] && !ft_strchr(" 1", map[i][j + 1])) \
		|| (map[i + 1] && ((int)ft_strlen(map[i + 1]) > j) \
		&& !ft_strchr(" 1", map[i + 1][j])) \
		|| (j && map[i][j - 1] && !ft_strchr(" 1", map[i][j - 1]))))
		return (0);
	return (1);
}
