/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:47:59 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/13 09:50:21 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_prog(t_vault *data)
{
	size_t	x;
	int		y;
	char	**options;

	x = 0;
	y = 0;
	options = malloc(sizeof(char *) * data->argc + 1);
	if (!options)
		return ;
	while (data->argv[y])
	{
		options[y] = data->argv[y + 1];
		printf("options #%d : %s\n", y, options[y]); // pour debug
		y++;
	}
	while (data->path_names[x])
	{
		data->prog_search = ft_strjoin(data->path_names[x], "/");
		data->prog_search = ft_strjoin(data->prog_search, options[0]);
		if (access(data->prog_search, F_OK | X_OK) == 0)
		{
			printf("path for prog : %s - %s\n", data->path_names[x], data->prog_search); // pour debug
			execve(data->prog_search, options, data->envp);
		}
		x++;
	}
	return ;
}

void	find_paths(t_vault *data)
{
	size_t	x;
	size_t	slen;

	x = 0;
	while (data->envp[x])
	{
		if (ft_strnstr(data->envp[x], "PATH", 4) != NULL)
		{
			data->paths = ft_strdup(data->envp[x]);
			break ;
		}
		x++;
	}
	data->path_names = ft_split(data->paths, ':');
	slen = ft_strlen(data->path_names[0]);
	data->path_names[0] = ft_substr(data->path_names[0], 5, slen);
	return ;
}