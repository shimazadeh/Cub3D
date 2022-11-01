/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:28:02 by aguillar          #+#    #+#             */
/*   Updated: 2022/10/26 12:59:58 by aguillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	arg_check(int ac, char **av, int *fd_add)
{
	int	i;

	if (ac != 2)
		return (ft_putstr_fd("Error\nInvalid number of argument!\n", 2), 0);
	i = ft_strlen(av[1]);
	if (i < 4 || ft_strncmp(&(av[1][i - 4]), ".cub", 4))
		return (ft_putstr_fd("Error\nInvalid file name!\n", 2), 0);
	if (!open_file(av[1], fd_add))
		return (0);
	return (1);
}

int	open_file(char *str, int *fd_add)
{
	int	fd;

	fd = open(str, O_DIRECTORY);
	if (fd != -1)
		return (close(fd), ft_putstr_fd("Error\n", 2), \
			ft_putstr_fd(str, 2), ft_putstr_fd(": is a directory\n", 2), 0);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\n", 2), ft_putstr_fd(str, 2), \
		 ft_putstr_fd(": ", 2), perror(NULL), 0);
	else
		*fd_add = fd;
	return (1);
}
