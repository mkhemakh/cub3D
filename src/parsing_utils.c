/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <mkhemakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 06:17:12 by mkhemakh          #+#    #+#             */
/*   Updated: 2021/10/02 13:35:46 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen2(char *str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int	ft_charinstr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_depart(char c, t_recup *recup, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (recup->depart != 'x')
			recup->multijoueurs = 1;
		recup->depart = c;
		recup->dx = i;
		recup->dy = j;
		return (1);
	}
	return (0);
}

int	ft_murs_util(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		else
			i++;
	}
	return (0);
}

void	ft_initialisation(t_recup *recup)
{
	recup->no = NULL;
	recup->so = NULL;
	recup->we = NULL;
	recup->ea = NULL;
	recup->f = -1;
	recup->c = -1;
	recup->rx = 0;
	recup->ry = 0;
	recup->nblines = 0;
	recup->sizeline = 0;
	recup->map = NULL;
	recup->dx = 0;
	recup->dy = 0;
	recup->multijoueurs = 0;
	recup->lignevide = 0;
	recup->insidemap = 0;
	recup->count = 0;
	recup->sum = 0;
	recup->wrongcharmap = 0;
	ft_init_more(recup);
}
