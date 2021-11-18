/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <mkhemakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 07:58:21 by mkhemakh          #+#    #+#             */
/*   Updated: 2021/10/08 10:12:24 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture_adress(t_recup *recup)
{
	recup->texture[0].addr = (int *)mlx_get_data_addr(recup->texture[0].img,
			&recup->texture[0].bits_per_pixel,
			&recup->texture[0].line_length, &recup->texture[0].endian);
	recup->texture[1].addr = (int *)mlx_get_data_addr(recup->texture[1].img,
			&recup->texture[1].bits_per_pixel,
			&recup->texture[1].line_length, &recup->texture[1].endian);
	recup->texture[2].addr = (int *)mlx_get_data_addr(recup->texture[2].img,
			&recup->texture[2].bits_per_pixel,
			&recup->texture[2].line_length, &recup->texture[2].endian);
	recup->texture[3].addr = (int *)mlx_get_data_addr(recup->texture[3].img,
			&recup->texture[3].bits_per_pixel,
			&recup->texture[3].line_length, &recup->texture[3].endian);
}

void	ft_get_texture(t_recup *recup)
{
	recup->texture[0].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->no, &(recup->texture[0].width), &(recup->texture[0].height));
	if (!(recup->texture[0].img))
		ft_error(recup, "Texture SO\n");
	recup->texture[1].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->so, &(recup->texture[1].width), &(recup->texture[1].height));
	if (!(recup->texture[1].img))
		ft_error(recup, "Texture NO\n");
	recup->texture[2].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->we, &(recup->texture[2].width), &(recup->texture[2].height));
	if (!(recup->texture[2].img))
		ft_error(recup, "Texture EA\n");
	recup->texture[3].img = mlx_xpm_file_to_image(recup->data.mlx_ptr,
			recup->ea, &(recup->texture[3].width), &(recup->texture[3].height));
	if (!(recup->texture[3].img))
		ft_error(recup, "Texture WE\n");
	ft_get_texture_adress(recup);
}

int	ft_raycasting(t_recup *recup)
{
	recup->ray.x = 0;
	while (recup->ray.x < recup->rx)
	{
		ft_initialisation3(recup);
		ft_stepsidedist(recup);
		ft_color_column(recup);
		recup->ray.x++;
	}
	mlx_put_image_to_window(recup->data.mlx_ptr, recup->data.mlx_win,
		recup->data.img, 0, 0);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	ft_swap(recup);
	return (0);
}

void	ft_mlxhelp(t_recup *recup);

int	ft_mlx(t_recup *recup)
{
	ft_initialisation2(recup);
	recup->data.mlx_ptr = mlx_init();
	if (!(recup->data.mlx_ptr))
		ft_error(recup, "Mlx init impossible\n");
	mlx_get_screen_size(recup->data.mlx_ptr, &recup->screenx, &recup->screeny);
	ft_mlxhelp(recup);
	ft_get_texture(recup);
	recup->data.img = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr = (int *)mlx_get_data_addr(recup->data.img, &recup->data
			.bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	recup->data.mlx_win = mlx_new_window(recup->data.mlx_ptr, recup->rx,
			recup->ry, "cub3D");
	recup->data.img2 = mlx_new_image(recup->data.mlx_ptr, recup->rx, recup->ry);
	recup->data.addr2 = (int *)mlx_get_data_addr(recup->data.img2, &recup->data
			.bits_per_pixel, &recup->data.line_length, &recup->data.endian);
	ft_verify_errors(recup);
	mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
	mlx_hook(recup->data.mlx_win, 2, 1L << 0, ft_key_press, recup);
	mlx_loop_hook(recup->data.mlx_ptr, ft_raycasting, recup);
	mlx_hook(recup->data.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(recup->data.mlx_ptr);
	return (0);
}

void	ft_mlxhelp(t_recup *recup)
{
	if (recup->rx > recup->screenx)
		recup->rx = recup->screenx;
	if (recup->ry > recup->screeny)
		recup->ry = recup->screeny;
}
