/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/15 17:45:49 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_fds(t_vault *data, int y)
{
	if (y == 0)
	{
		check_fd_in(data);
		dup2(data->fd_in, STDIN_FILENO);
		dup2(data->pipe_ends[y][p_write], STDOUT_FILENO);
		close(data->fd_in);
	}
	else if (y < data->nbr_cmd - 1)
	{
		dup2(data->pipe_ends[y - 1][p_read], STDIN_FILENO);
		dup2(data->pipe_ends[y][p_write], STDOUT_FILENO);
	}
	else if (y == data->nbr_cmd - 1)
	{
		check_fd_out(data);
		dup2(data->pipe_ends[y - 1][p_read], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		close (data->fd_out);
	}
	return (0);
}

void	forking(t_vault *data, int y)
{
	while (y < data->nbr_cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			check_error();
		else if (data->pid == 0)
		{
			if (dup_fds(data, y) == 0)
			{
				close_pipe_ends(data);
				find_prog(data, y + 2);
			}
			exit (0);
		}
		y++;
	}
}

int	piping(t_vault *data)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < data->nbr_cmd - 1)
	{
		data->pipe_ends[x] = malloc(sizeof(int) * 2);
		if (pipe(data->pipe_ends[x]) == -1)
			check_error();
		x++;
	}
	forking(data, y);
	close_pipe_ends(data);
	data->child_id = waitpid(0, &data->status, 0);
	while (data->child_id != -1)
		data->child_id = waitpid(0, &data->status, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_vault	data;

	if (argc < 5)
		return (0);
	data.paths = NULL;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.nbr_cmd = argc - 3;
	data.error_flag = 0;
	find_paths(&data);
	piping(&data);
	free_dbl_ptr((void **)data.path_names);
	return (0);
}
