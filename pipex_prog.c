/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:47:59 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/15 20:52:36 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	find_prog(t_vault *data, int argv_id)
{
	size_t	x;

	x = 0;
	data->cmd.options = ft_split(data->argv[argv_id], ' ');
	if (access(data->cmd.options[0], F_OK | X_OK) == 0)
		data->cmd.name = data->cmd.options[0];
	else if (access(data->cmd.options[0], F_OK | X_OK) != 0)
	{
		while (data->path_names[x])
		{
			data->cmd.name = ft_strjoin(data->path_names[x], "/");
			data->cmd.name = ft_strjoin(data->cmd.name, data->cmd.options[0]);
			if (access(data->cmd.name, F_OK | X_OK) == 0)
				execve(data->cmd.name, data->cmd.options, data->envp);
			x++;
		}
	}
	message("command not found", ": ", data->cmd.name, 0);
}

void	find_paths(t_vault *data)
{
	size_t	x;
	size_t	slen;

	x = 0;
	while (data->envp[x])
	{
		if (ft_strnstr(data->envp[x], "PATH=", 5) != NULL)
		{
			slen = ft_strlen(data->envp[x]);
			data->paths = ft_substr(data->envp[x], 5, slen);
			break ;
		}
		x++;
	}
	check_error();
	data->path_names = ft_split(data->paths, ':');
	free (data->paths);
	if (!data->path_names)
		message("unexpected error", "", "", 0);
}
