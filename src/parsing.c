/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:55:32 by aguillar          #+#    #+#             */
/*   Updated: 2022/11/29 13:37:11 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(int fd, t_cub *cub)
{
	int		flag;
	char	*str;
	char	*tmp;
	char	*map_str;
	int		ret;

	ret = 0;
	flag = 0;
	map_str = NULL;
	tmp = NULL;
	str = get_next_line(fd);
	while (str)
	{
		if (!ret && str[0] != '\n' && flag < 6)
		{
			if (!parse_graphic_elems(str, cub))
				ret = 1;
			flag++;
		}
		else if (!ret)
		{
			tmp = map_str;
			map_str = ft_strjoin(tmp, str);
			free(tmp);
		}
		free(str);
		str = get_next_line(fd);
	}
	if (ret)
	{
		close(fd);
		return (ret);
	}
	if (map_str)
		flag++;
	if (!parse_map(map_str, cub))
		return (0);
	if (flag < 6)
		return (close(fd), \
			ft_putstr_fd("Error\nMissing texture element in file!\n", 2), 0);
	else if (flag != 7)
		return (close(fd), \
			ft_putstr_fd("Error\nMissing map element in file!\n", 2), 0);
	return (1);
}
