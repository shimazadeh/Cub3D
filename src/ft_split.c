/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:48:29 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 13:58:50 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	ft_wc(char *str, char c)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == c))
			i++;
		if (str[i] && (str[i] != c))
		{
			wc++;
			while (str[i] && (str[i] != c))
				i++;
		}
	}
	return (wc);
}

static int	ft_wl(char *str, char c)
{
	int	i;
	int	wl;

	i = 0;
	wl = 0;
	while (str[i] && (str[i] == c))
		i++;
	while (str[i] && (str[i] != c))
	{
		wl++;
		i++;
	}
	return (wl);
}

static void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_fill_tab(char **tab, int wc, const char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < wc)
	{
		j = 0;
		tab[i] = malloc(sizeof(char) * (ft_wl((char *)&str[k], c) + 1));
		if (!tab[i])
		{
			ft_free_tab(tab);
			return (0);
		}
		while (str[k] && (str[k] == c))
			k++;
		while (str[k] && (str[k] != c))
			tab[i][j++] = str[k++];
		tab[i][j] = '\0';
		i++;
	}
	tab[i] = 0;
	return (1);
}

char	**ft_split(const char *str, char c)
{
	char	**tab;
	int		wc;

	if (!str)
		return (0);
	wc = ft_wc((char *)str, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (0);
	if (!ft_fill_tab(tab, wc, str, c))
		return (0);
	return (tab);
}
