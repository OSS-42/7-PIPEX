/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 11:07:16 by ewurstei          #+#    #+#             */
/*   Updated: 2022/10/06 16:52:57 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    size_t  x;
    size_t  y;

    x = 0;
    y = 0;
    (void)argc;
    (void)argv;
 
    char *paths;
    char **path_names;
    paths = NULL;
    while (envp[x])
    {
        if (ft_strnstr(envp[x], "PATH", 4) != NULL)
        {
            while (envp[x][y])
                y++;
            paths = ft_strdup(envp[x]);
            break ;
        }
        x++;
    }
    printf("paths : %s\n", paths);
    path_names = ft_split(paths, ':');
    x = 0;
    while (path_names[x])
    {
        printf("Path_name #%zu : %s\n", x, path_names[x]);
        x++;
    }
    //execve("/usr/bin/env", options, envp);
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