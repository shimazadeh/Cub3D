/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shabibol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 19:16:07 by shabibol          #+#    #+#             */
/*   Updated: 2022/12/04 19:16:12 by shabibol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_col_row(char **map, int *col, int *row)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = ft_strlen(map[i]);
		if (j > *col)
			*col = j;
	}
	*row = i;
}

int	convert_map(char **map, int i, int j, t_cub *cub)
{
	char	**new_map;

	get_col_row(map, &cub->mapw, &cub->maph);
	new_map = malloc(sizeof(char *) * (cub->maph + 1));
	if (!new_map)
		ft_exit(cub);
	new_map[cub->maph] = NULL;
	while (++i < cub->maph)
	{
		j = -1;
		new_map[i] = malloc(sizeof(char) * (cub->mapw + 1));
		if (!new_map[i])
			return (free_tab(new_map), ft_exit(cub));
		while (++j < cub->mapw)
		{
			if (j < (int)ft_strlen(map[i]) \
				&& (map[i][j] == '0' || map[i][j] == '1'))
				new_map[i][j] = map[i][j];
			else
				new_map[i][j] = '1';
		}
		new_map[i][j] = '\0';
	}
	cub->map = new_map;
	return (free_tab(map), 1);
}
