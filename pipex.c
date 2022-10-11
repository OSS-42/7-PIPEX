/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/09 21:48:06 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_vault *data)
{
	find_paths(data);
	check_paths(data); //DEBUG
	find_prog(data);
}



int	main(int argc, char **argv, char **envp)
{
	t_vault data;

	data.paths = NULL;
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	exec_cmd(&data);
	return (0);
}

/*
void	find_path(void)
{
	char *options;

	options = ;
	execve("/usr/bin/env", options, envp);
	return (0);
}
*/

// void	pipex(int fd1, int fd2)
// {
// 	int end[2];

// 	pipe(end);
// }

/*
int main(int argc, char **argv, char **envp)
{
	char *options[3] = {"ls", "-la", NULL};

	(void)argc;
	(void)argv;
	execve("/usr/bin/ls", options, envp);
	return (0);
}
*/