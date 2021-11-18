/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <mkhemakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 09:48:41 by mkhemakh          #+#    #+#             */
/*   Updated: 2021/10/11 16:32:07 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_parsing_map(char *fichier, t_recup *recup)
{
	int			fd;
	char		*str;

	str = NULL;
	fd = open(fichier, O_RDONLY);
	recup->map = malloc(sizeof(char *) * recup->nblines);
	if (!(recup->map))
		return (0);
	while (get_next_line(fd, &str))
	{
		if (recup->insidemap == 1 && ft_lignevide(str) == 0
			&& recup->count < recup->nblines)
			recup->lignevide = 1;
		recup->insidemap = ft_is_map(str, recup);
		if (recup->insidemap == 1)
		{
			recup->count++;
			ft_copy_map(str, recup);
		}
		free(str);
	}
	free(str);
	close(fd);
	ft_mlx(recup);
	return (0);
}

void	ft_free_parsing(t_recup *recup, char *buff, char *error)
{
	int	i;

	i = -1;
	write(1, error, ft_strlen(error));
	if (buff)
		free(buff);
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
	exit(0);
}

void	ft_parsing(char *fichier, t_recup *recup)
{
	int			fd;
	char		*str;

	str = NULL;
	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		ft_error(recup, "Invalide : is a directory\n");
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		ft_error(recup, "Fichier .cub invalide\n");
	recup->erreur = 0;
	while (get_next_line(fd, &str))
	{
		if (recup->erreur == 2)
			ft_free_parsing(recup, str, "Parsing Invalide!\n");
		ft_color_resolution(&str, recup);
		ft_texture(str, recup);
		ft_map(str, recup);
		free(str);
	}
	free(str);
	close(fd);
	if (recup->sizeline == 0 || recup->nblines == 0 || recup->erreur == 2)
		ft_free_parsing(recup, NULL, "Map vide!\n");
	ft_parsing_map(fichier, recup);
}

int	ft_cub(char *str, t_recup *recup)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			write(1, "Argument Invalide!\n", 19);
			exit(0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, recup);
	else
	{
		write(1, "Argument Invalide!\n", 19);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_recup	recup;

	ft_initialisation(&recup);
	if (argc == 2)
		ft_cub(argv[1], &recup);
	else
		write(1, "Error\nArguments invalides\n", 30);
}
