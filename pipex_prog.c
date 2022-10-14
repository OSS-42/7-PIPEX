/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:47:59 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/14 11:00:49 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_prog(t_vault *data, int argv_id)
{
	size_t	x;

	x = 0;
	data->cmd.options = ft_split(data->argv[argv_id], ' ');
	while (data->path_names[x])
	{
		data->cmd.name = ft_strjoin(data->path_names[x], "/");
		data->cmd.name = ft_strjoin(data->cmd.name, data->cmd.options[0]);
		if (access(data->cmd.name, F_OK | X_OK) == 0)
		{
//			printf("path for prog : %s - %s\n", data->path_names[x], data->cmd.name); // pour debug
			execve(data->cmd.name, data->cmd.options, data->envp);
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
//	check_paths(data); //DEBUG
	return ;
}