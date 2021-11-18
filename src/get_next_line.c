/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 17:18:54 by mkhemakh          #+#    #+#             */
/*   Updated: 2020/02/18 15:36:06 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	has_new_line(char *saved)
{
	int	i;

	if (!saved)
		return (0);
	i = 0;
	while (saved[i])
	{
		if (saved[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_until_newline(char *saved)
{
	int		i;
	char	*line;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_after_newline(char *saved)
{
	int		i;
	int		j;
	char	*new_line;

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] != '\n' && saved[i])
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!new_line)
		return (NULL);
	i++;
	j = 0;
	while (saved[i])
		new_line[j++] = saved[i++];
	new_line[j] = '\0';
	free(saved);
	return (new_line);
}

int	return_value(int reader)
{
	if (reader == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*saved[1024];
	char		*buf;
	int			reader;

	if ((read(fd, 0, 0) == -1) || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	reader = 1;
	while (!has_new_line(saved[fd]) && reader != 0)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buf);
			return (-1);
		}
		buf[reader] = '\0';
		saved[fd] = ft_strjoin_helper(saved[fd], buf);
	}
	free(buf);
	*line = get_until_newline(saved[fd]);
	saved[fd] = get_after_newline(saved[fd]);
	return (return_value(reader));
}
