/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_hd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:59:17 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/18 20:59:17 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_env(t_vault *data, char **envp)
{
	if (!envp || envp[0][0] == '\0')
	{
		data->argc = 0;
		message(data, "Unexpected error.", "", 0);
		return ;
	}
	return ;
}

void	detect_heredoc(t_vault *data)
{
	int		fd_tmp;
	int		fd_stdin;
	char	*line;

	fd_tmp = open(".hd.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
		exit_on_error(data, message(data, "FD error (heredoc).", "", 0));
	line = "";
	while (1)
	{
		write(1, "hd> ", 4);
		line = get_next_line(fd_stdin);
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, data->argv[2], ft_strlen(data->argv[2]) + 1))
			close(fd_stdin);
		else
			ft_putstr_fd(line, fd_tmp);
		free(line);
	}
	close(fd_tmp);
}