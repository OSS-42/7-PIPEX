/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:28:38 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/11 11:08:27 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_clean(char *string)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free (string);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_lenght(string) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	while (string[i])
		temp[j++] = string[i++];
	temp[j] = '\0';
	free (string);
	return (temp);
}

char	*ft_linetoprint(char *string)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (!string[i])
		return (NULL);
	temp = (char *)malloc(sizeof(char) * (ft_lenght(string) + 1));
	if (!temp)
		return (NULL);
	while (string[i] && string[i] != '\n')
	{
		temp[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		temp[i] = string[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*get_next_line(int fd, t_vault *data)
{
	char		*line;
	int			i;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	i = 1;
	while (!ft_search(data->gnl_stash, '\n') && i != 0)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		line[i] = '\0';
		data->gnl_stash = ft_join(data->gnl_stash, line);
	}
	free (line);
	line = ft_linetoprint(data->gnl_stash);
	data->gnl_stash = ft_clean(data->gnl_stash);
	return (line);
}
