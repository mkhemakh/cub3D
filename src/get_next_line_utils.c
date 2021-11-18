/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhemakh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:06:23 by mkhemakh          #+#    #+#             */
/*   Updated: 2020/01/23 18:46:09 by mkhemakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strdup(char *str)
{
	int		i;
	char	*dest;

	i = ft_strlen(str);
	dest = (char *)malloc(sizeof(*str) * (i + 1));
	if (!dest)
		return (0);
	while (i >= 0)
	{
		dest[i] = str[i];
		i--;
	}
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_helper(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*tab;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	tab = (char *)malloc(i * sizeof(char));
	if (!tab)
		return (NULL);
	i = -1;
	while (s1[++i])
		tab[i] = s1[i];
	j = -1;
	while (s2[++j])
		tab[i + j] = s2[j];
	tab[i + j] = '\0';
	free(s1);
	return (tab);
}
