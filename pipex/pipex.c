/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:37:05 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/02/01 17:16:38 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialise(int argc, char *argv[], t_pipe *data)
{
	int heredoc = 0;
	data->args = NULL;
	//data->path = NULL;
	data->path = NULL;
	data->pipe_fd = NULL;
	if (argc < 5)
		free_struct(data, errno);
	// if (data->path == NULL)
	// 	data->input_fd = open(argv[1], O_RDONLY);
	else
	{
		data->input_fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		heredoc++;
	}
	if (data->input_fd < 0)
		perror(argv[1]);
	data->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->output_fd < 0)
	{
		perror(argv[argc - 1]);
		close(data->input_fd);
		free_struct(data, 1);
	}
	data->cmdcount = argc - 3 - heredoc;
}

void	create_cmd(t_pipe *data, char *argv[], int i)
{
	if (data->args)
		ft_freedata(data->args);
	if (data->path)
	{
		free(data->path);
		data->path = NULL;
	}
	data->args = ft_split(argv[i + 2], ' ');
	if (!data->args || data->args[0] == NULL)
		free_struct(data, errno);
	data->path = ft_strjoin("/bin/", data->args[0]);
	if (!data->path)
		free_struct(data, errno);
	if (access(data->path, R_OK | X_OK) == -1)
		perror(data->args[0]);
}

void	first_child(t_pipe *data, char *argv[], char *envp[])
{
	create_cmd(data, argv, 0);
	data->pid[0] = fork();
	if (data->pid[0] == 0)
	{
		if (dup2(data->input_fd, STDIN_FILENO) == -1)
			free_struct(data, errno);
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
			free_struct(data, errno);
		ft_close(data);
		execve(data->path, data->args, envp);
		strerror(errno);
		free_struct(data, 127);
	}
}

void	middle_child(t_pipe *data, char *argv[], int i, char *envp[])
{
	create_cmd(data, argv, i);
	data->pid[i] = fork();
	if (data->pid[i] == 0)
	{
		if (dup2(data->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
			free_struct(data, errno);
		if (i == data->cmdcount - 1)
		{
			if (dup2(data->output_fd, STDOUT_FILENO) == -1)
				free_struct(data, errno);
		}
		else
		{
			if (dup2(data->pipe_fd[(i * 2) + 1], STDOUT_FILENO) == -1)
				free_struct(data, errno);
		}
		ft_close(data);
		execve(data->path, data->args, envp);
		free_struct(data, 127);
	}
}

void	handle_heredoc(int argc, char *argv[], t_pipe *data)
{
    char buffer[1024];
    ssize_t bytes_read;
    char *delimitor;
    (void)argc;
    delimitor = ft_strdup(argv[2]);
    while (1)
    {
        write(0, "> ", 2);
        bytes_read = read(0, buffer, sizeof(buffer - 1)); // use gnl instead?
        if (bytes_read <= 0)
            break;
        buffer[bytes_read - 1] = '\0';
        if (ft_strcmp(buffer, delimitor) == 0)
            break;
		buffer[bytes_read - 1] = '\n';
		buffer[bytes_read] = '\0';
		write(data->input_fd, &buffer, strlen(buffer));
    }
    free (delimitor);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	*data;
	int		i;

	i = 0;
	if (argc < 5)
		exit(errno);
	data = malloc(sizeof(t_pipe) + (sizeof(pid_t) * (argc - 3)));
	if (!data)
		exit(errno);
	initialise(argc, argv, data);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		i = 1;
		handle_heredoc(argc, argv, data);
	}
	return (0);
	data->pipe_fd = malloc(sizeof(int) * (data->cmdcount - 1) * 2);
	if (!data->pipe_fd)
		free_struct(data, errno);
	while (i < (data->cmdcount - 1))
	{
		if (pipe(&data->pipe_fd[i++ *2]) == -1)
			free_struct(data, errno);
	}
	first_child(data, argv, envp);
	i = 1 + 1;
	while (i < data->cmdcount)
		middle_child(data, argv, i++, envp);
	ft_close(data);
	ft_wait(data);
}
