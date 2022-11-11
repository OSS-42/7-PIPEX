/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/11 15:07:21 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipe_ends(t_vault *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_cmd - 1)
	{
		close (data->pipe_ends[x][p_write]);
		close (data->pipe_ends[x][p_read]);
		free (data->pipe_ends[x]);
		x++;
	}
	free(data->pipe_ends);
	return ;
}

void	forking(t_vault *data)
{
	int	y;

	y = 0;
	while (y < data->nbr_cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			exit_on_error(data, message(data, "PID creation error.", "", 0));
		else if (data->pid == 0)
		{
			if (dup_fds(data, y) == 0)
			{
				close_pipe_ends(data);
				find_prog(data, y + 2);
			}
			else
				exit_on_error(data, message(data, "FD error.", "", 9));
		}
		y++;
	}
	return ;
}

void	piping(t_vault *data)
{
	int	x;

	x = 0;
	data->pipe_ends = malloc(sizeof(int *) * (data->nbr_cmd - 1) + 1);
	if (!data->pipe_ends)
		message(data, "Unexpected error. #1", "", 0);
	while (x < data->nbr_cmd - 1)
	{
		data->pipe_ends[x] = malloc(sizeof(int) * 2);
		if (pipe(data->pipe_ends[x]) == -1)
			exit_on_error(data, message(data, "Pipe creation error.", "", 0));
		x++;
	}
	forking(data);
	close_pipe_ends(data);
	data->child_id = waitpid(0, &data->status, 0);
	while (data->child_id != -1)
		data->child_id = waitpid(0, &data->status, 0);
	return ;
}

void	init_vault(t_vault *data, int argc, char **argv, char **envp)
{
	data->paths = NULL;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->nbr_cmd = argc - 3;
	data->error_flag = 0;
	data->fd_in = -1;
	data->fd_out = -1;
	find_paths(data);
	piping(data);
	free_dbl_ptr((void **)data->path_names);
}

int	main(int argc, char **argv, char **envp)
{
	t_vault	data;

	if ((argc != 5) || (!envp || !envp[0]))
	{
		data.argc = 0;
		data.fd_in = -1;
		data.fd_out = -1;
		if (argc != 5)
			message(&data, "Usage: ", "./pipex file1 cmd1 cmd2 file2.", 0);
		else
			message(&data, "Unexpected error. #2", "", 0);
		return (0);
	}
	init_vault(&data, argc, argv, envp);

	return (0);
}
