/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:49:37 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/18 10:49:37 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	io_redirection(t_vault *data, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit_on_error(data, 1);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_on_error(data, 1);
}

int	dup_fds(t_vault *data, int y)
{
	if (y == 0)
	{
		check_fd_in(data);
		io_redirection(data, data->fd_in, data->pipe_ends[y][p_write]);
		close(data->fd_in);
	}
	else if (y < data->nbr_cmd - 1)
		io_redirection(data, data->pipe_ends[y - 1][p_read],
			data->pipe_ends[y][p_write]);
	else if (y == data->nbr_cmd - 1)
	{
		check_fd_out(data);
		io_redirection(data, data->pipe_ends[y - 1][p_read], data->fd_out);
		close (data->fd_out);
	}
	return (0);
}
