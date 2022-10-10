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

void    find_prog(t_vault *path_list, char **argv, char **envp)
{
    size_t  x;
    int y;
    char    **options;

    x = 0;
    y = 0;
    options = ft_split(argv[1], ' ');
    while(options[y])
    {
        printf("options #%d : %s\n", y, options[y]);
        y++;
    }
    options[y] = '\0';
    while (path_list->path_names[x])
    {
        path_list->prog_search = ft_strjoin(path_list->path_names[x], "/");
        path_list->prog_search = ft_strjoin(path_list->prog_search, options[0]);
        if (execve(path_list->prog_search, options, envp) == -1)
        {
            x++;
            printf("path for prog : %s - %s\n", path_list->path_names[x], path_list->prog_search);
        }
    }
    return ;
}

void    find_paths(t_vault *path_list, char **envp)
{
    size_t  x;
    size_t  slen;

    x = 0;
    while (envp[x])
    {
        if (ft_strnstr(envp[x], "PATH", 4) != NULL)
        {
            path_list->paths = ft_strdup(envp[x]);
            break ;
        }
        x++;
    }
    path_list->path_names = ft_split(path_list->paths, ':');
    slen = ft_strlen(path_list->path_names[0]);
    path_list->path_names[0] = ft_substr(path_list->path_names[0], 5, slen);
    return ;
}

int main(int argc, char **argv, char **envp)
{

    t_vault path_list;

    (void)argc;
    path_list.paths = NULL;
    find_paths(&path_list, envp);
    check_paths(&path_list); //DEBUG
    find_prog(&path_list, argv, envp);
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