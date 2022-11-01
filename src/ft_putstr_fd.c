/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:55:05 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 12:51:34 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = ft_strlen(str);
	if (!write(fd, str, i))
		return ;
}
