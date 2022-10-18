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

void	io_redirection(t_vault *data, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit_on_error(data, 1);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_on_error(data, 1);
}

void	close_pipe_ends(t_vault *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_cmd - 1 + 2)
	{
		close (data->pipe_ends[x][p_write]);
		close (data->pipe_ends[x][p_read]);
		free (data->pipe_ends[x]);
		x++;
	}
	free(data->pipe_ends);
	return ;
}

int	dup_fds(t_vault *data, int y)
{
	if (y == 0)
	{
		check_fd_in(data);
		io_redirection(data, data->fd_in, data->pipe_ends[y][p_write]);
//		io_redirection(data, data->fd_in, STDIN_FILENO);
//		io_redirection(data, data->pipe_ends[y][p_write], STDOUT_FILENO);
		close(data->fd_in);
	}
	else if (y < data->nbr_cmd - 1 + 2)
	{
		io_redirection(data, data->pipe_ends[y - 1][p_read], data->pipe_ends[y][p_write]);
//		io_redirection(data, data->pipe_ends[y - 1][p_read], STDIN_FILENO);
//		io_redirection(data, data->pipe_ends[y][p_write], STDOUT_FILENO);
	}
	else if (y == data->nbr_cmd - 1 + 2)
	{
		check_fd_out(data);
		io_redirection(data, data->pipe_ends[y - 1][p_read], data->fd_out);
//		io_redirection(data, data->pipe_ends[y - 1][p_read], STDIN_FILENO);
//		io_redirection(data, data->fd_out, STDOUT_FILENO);
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
			exit_on_error(data, message(data, "PID creation error.", "", 0));
		else if (data->pid == 0)
		{
			if (dup_fds(data, y) == 0)
			{
				close_pipe_ends(data);
				find_prog(data, y + 2);
			}
			exit_on_error(data, 0);
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
	data->pipe_ends = malloc(sizeof(int *) * (data->nbr_cmd - 1 + 2));
	while (x < data->nbr_cmd - 1 + 2)
	{
		data->pipe_ends[x] = malloc(sizeof(int) * 2);
		if (pipe(data->pipe_ends[x]) == -1)
			exit_on_error(data, message(data, "Pipe creation error.", "", 0));
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
	int		last_exit_code;

	if (argc < 5)
		exit_on_error(&data, message(&data, "Usage: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2.", 0));
	if (!envp || envp[0][0] == '\0')
		exit_on_error(&data, message(&data, "Unexpected error.", "", 0));
	init_vault(&data, argc, argv, envp);
	find_paths(&data);
	last_exit_code = piping(&data);
	free_dbl_ptr((void **)data.path_names);
	return (last_exit_code);
}