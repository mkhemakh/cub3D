/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <mkhemakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:32:18 by mkhemakh          #+#    #+#             */
/*   Updated: 2021/10/10 14:29:34 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_verify_errors(t_recup *recup)
{
	if (ft_murs(recup) == 1)
		ft_error(recup, "Map non entouree de 1\n");
	if (recup->depart == 'x')
		ft_error(recup, "Pas de joueur\n");
	if (recup->indicateur2 != 6)
		ft_error(recup, "Mauvaises donnees F ou C\n");
	if (recup->multijoueurs == 1)
		ft_error(recup, "Plus d'un joueur\n");
	if (recup->lignevide == 1)
		ft_error(recup, "Ligne vide dans la map\n");
	if (recup->wrongcharmap == 2)
		ft_error(recup, "Caractere incorrect dans la map\n");
}

void	ft_error2(t_recup *recup)
{
	if (recup->map)
		free(recup->map);
	ft_exit(recup);
}

void	ft_error(t_recup *recup, char *str)
{
	int	i;

	i = -1;
	recup->indicateur3 = 1;
	write(1, "Starting game...\n", 18);
	write(1, str, ft_strlen(str));
	if (recup->no)
		free(recup->no);
	if (recup->so)
		free(recup->so);
	if (recup->we)
		free(recup->we);
	if (recup->ea)
		free(recup->ea);
	if (recup->map)
	{
		while (++i < recup->nblines)
			free(recup->map[i]);
	}
	ft_error2(recup);
}

int	ft_exit(t_recup *recup)
{
	if (recup->indicateur3 == 0)
		ft_error(recup, "CUB3D closed\n");
	if (recup->data.img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->data.img);
	if (recup->texture[0].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[0].img);
	if (recup->texture[1].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[1].img);
	if (recup->texture[2].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[2].img);
	if (recup->texture[3].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[3].img);
	if (recup->data.mlx_win)
		mlx_destroy_window(recup->data.mlx_ptr, recup->data.mlx_win);
	if (recup->data.img2)
		mlx_destroy_image(recup->data.mlx_ptr, recup->data.img2);
	if (recup->data.mlx_ptr)
	{
		mlx_destroy_display(recup->data.mlx_ptr);
		free(recup->data.mlx_ptr);
	}
	exit(0);
}

int	ft_nb_virgule(const char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
	}
	return (j);
}
