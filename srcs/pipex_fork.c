/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:32:55 by plau              #+#    #+#             */
/*   Updated: 2022/12/16 21:00:11 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Create pipe and fork */
/* dup2 - duplicate fd */
/* 1st parameter- fd to be duplicated (3)- input file */
/* 2nd parameter- fd of the newcopy */
/* redirect output of stdout to pipe */
/* redirect output of stdin to infile */
/* Create a pipe that can be used to communicate between the */
/* 		parent and child processes */
/* Fork - create a child process */
/* Fork() returns PID of the child process to the parent process */
/* 		returns 0 to the child process */
/* If in child process
	- close input side of the pipe, 
	- redirect std output to the output side of the pipe
	- execute the program that will write to the pipe - fd[1] write - child (cmd1)
	If in parent process
	- close output side of the pipe
	- redirect std input to the input side of the pipe
	- execute the program that will read from the pipe - fd[0] read - parent (cmd2)
*/
void	child_two(t_prg *prg, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_error("Fork two failed");
	if (pid == 0)
	{
		dup2(prg->fd_out, STDOUT_FILENO);
		dup2(prg->fd[0], STDIN_FILENO);
		close(prg->fd[1]);
		execve(prg->cmd_2nd, prg->cmd2, envp);
	}
}

void	create_child(t_prg *prg, char **envp)
{
	pid_t	pid;

	if (pipe(prg->fd) == -1)
		exit_error("Pipe failed");
	pid = fork();
	if (pid == -1)
		exit_error("Fork one failed");
	if (pid == 0)
	{
		dup2(prg->fd_in, STDIN_FILENO);
		dup2(prg->fd[1], STDOUT_FILENO);
		close(prg->fd[0]);
		execve(prg->cmd_1st, prg->cmd1, envp);
	}
	child_two(prg, envp);
	close(prg->fd[0]);
	close(prg->fd[1]);
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}
