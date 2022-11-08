/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_hd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:59:17 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/07 14:01:39 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
	char	*p_line;

	fd_tmp = open(".hd.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
		exit_on_error(data, message(data, "FD error (heredoc).", "", 9));
	p_line = "";
	while (data->end_hd == 0)
	{
		ft_putstr_fd("hd> ", 1);
		p_line = get_next_line(fd_stdin);
		if (p_line == NULL)
			break ;
		if (ft_strlen(data->argv[2]) + 1 == ft_strlen(p_line)
			&& !ft_strncmp(p_line, data->argv[2], ft_strlen(data->argv[2] + 1)))
			data->end_hd = 1;
		else
			ft_putstr_fd(p_line, fd_tmp);
		free(p_line);
	}
	close(fd_stdin);
	close(fd_tmp);
}
