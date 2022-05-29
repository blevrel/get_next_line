/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:29:13 by blevrel           #+#    #+#             */
/*   Updated: 2022/05/03 13:44:48 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*stock_excess(char *stock, char *src)
{
	char	*dest;
	int		total_size;
	int		i;
	int		size;

	size = 0;
	if (stock == NULL)
		stock = ft_calloc(1, sizeof(char));
	i = 0;
	total_size = ft_strlen(src);
	while (src[size] != '\n' && src[size])
		size++;
	dest = ft_calloc((total_size - size + 1), sizeof(char));
	while (src[size])
	{
		size++;
		dest[i] = src[size];
		i++;
	}
	dest = ft_strjoin(dest, stock);
	free(stock);
	stock = NULL;
	return (dest);
}

char	*fill_dest(char *str)
{
	char	*dest;
	int		size;

	size = 0;
	if (*str == '\0')
	{
		free(str);
		return (NULL);
	}
	if (str == NULL)
		return (NULL);
	while (str[size] != '\n' && str[size])
		size++;
	if (str[size] == '\n')
		size++;
	dest = ft_calloc(size + 1, sizeof(char));
	size = -1;
	while (str[++size] != '\n' && str[size])
		dest[size] = str[size];
	if (str[size] == '\n')
		dest[size] = '\n';
	free(str);
	return (dest);
}

char	*add_stock(char	*stock)
{
	int		i;
	char	*dest;

	i = 0;
	while (stock[i])
		i++;
	dest = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (stock[i])
	{
		dest[i] = stock[i];
		i++;
	}
	return (dest);
}

char	*read_line(char *buff, char *dest, int fd)
{
	int			read_ret;

	if (dest == NULL)
		dest = ft_calloc(1, sizeof(char));
	read_ret = 1;
	while (check_eol(buff) == 0 && read_ret != 0)
	{
		read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(buff);
			free(dest);
			return (NULL);
		}
		buff[read_ret] = '\0';
		dest = ft_strjoin(dest, buff);
	}
	free(buff);
	return (dest);
}

char	*get_next_line(int fd)
{
	char			*dest;
	char			*buff;
	static char		*stock;

	dest = NULL;
	if (stock != NULL)
	{
		dest = add_stock(stock);
		free(stock);
		stock = NULL;
	}
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	dest = read_line(buff, dest, fd);
	if (dest == NULL)
		return (NULL);
	stock = stock_excess(stock, dest);
	dest = fill_dest(dest);
	if (*stock == '\0')
	{
		free(stock);
		stock = NULL;
	}
	return (dest);
}
