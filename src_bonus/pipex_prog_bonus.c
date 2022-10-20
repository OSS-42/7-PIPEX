/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_prog.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:47:59 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/18 14:58:34 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	cmd_path_check(t_vault *data)
{
	size_t	x;

	x = 0;
	while (data->path_names[x])
	{
		data->cmd.path = ft_strjoin(data->path_names[x], "/");
		data->cmd.name = ft_strjoin(data->cmd.path, data->cmd.options[0]);
		if (access(data->cmd.name, F_OK | X_OK) == 0)
			execve(data->cmd.name, data->cmd.options, data->envp);
		else
		{
			free(data->cmd.name);
			free(data->cmd.path);
		}
		x++;
	}
}

void	find_prog(t_vault *data, int argv_id)
{
	data->cmd.options = ft_split(data->argv[argv_id], ' ');
	if (!data->cmd.options)
		exit_on_error(data, message(data, "Unexpected error.", "", 0));
	if (access(data->cmd.options[0], F_OK | X_OK) == 0)
	{
		data->cmd.name = data->cmd.options[0];
		execve(data->cmd.name, data->cmd.options, data->envp);
	}
	else if (access(data->cmd.options[0], F_OK | X_OK) != 0)
		cmd_path_check(data);
	exit_on_error(data, message(data, "Command not found: ",
			data->cmd.options[0], 8));
}

void	find_paths(t_vault *data)
{
	size_t	x;
	size_t	slen;

	x = 0;
	while (data->envp[x] && data->envp[x][0])
	{
		if (ft_strnstr(data->envp[x], "PATH=", 5) != NULL)
		{
			slen = ft_strlen(data->envp[x]);
			data->paths = ft_substr(data->envp[x], 5, slen);
			break ;
		}
		x++;
	}
	data->path_names = ft_split(data->paths, ':');
	free (data->paths);
	if (!data->path_names)
		exit_on_error(data, message(data, "Unexpected error.", "", 0));
}
