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

void	close_pipe_ends(t_vault *data)
{
	int	x;

	x = 0;
	while (x < data->nbr_cmd - 1)
	{
		close (data->pipe_ends[x][p_read]);
		close (data->pipe_ends[x][p_write]);
		free (data->pipe_ends[x]);
		x++;
	}
	return ;
}

int	dup_fds(t_vault *data, int y)
{
	int		fd_in;
	int		fd_out;

	if (y == 0)
	{
		fd_in = open("test.txt", O_RDONLY);
		if (fd_in == -1)
			return (-1);
		dup2(fd_in, STDIN_FILENO);
		dup2(data->pipe_ends[y][p_write], STDOUT_FILENO);
		close(fd_in);
	}
	else if (y < data->nbr_cmd - 1)
	{
		dup2(data->pipe_ends[y - 1][p_read], STDIN_FILENO);
		dup2(data->pipe_ends[y][p_write], STDOUT_FILENO);
	}
	else if (y == data->nbr_cmd - 1)
	{
		fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (!fd_out)
			return (-1);
		dup2(data->pipe_ends[y - 1][p_read], STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
	}
	return (0);
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
			return (0);
		x++;
	}
	while (y < data->nbr_cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (0);
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
	find_paths(&data);
	piping(&data);
	free_dbl_ptr((void **)data.path_names);
	return (0);
}
