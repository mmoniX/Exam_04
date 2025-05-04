/*
Write a program that will behave like executing a shell command
- The command line to execute will be the arguments of this program
- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
- You must implement "|" and ";" like in bash
	- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
	- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
	- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
	- a cd command will never be immediately followed or preceded by a "|"
- You don't need to manage any type of wildcards (*, ~ etc...)
- You don't need to manage environment variables ($BLA ...)
- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.
*/

#include <stdlib.h>		//malloc, free, exit
#include <unistd.h>		//write, close, fork, chdir, execve, dup, dup2, pipe
#include <sys/wait.h>	//waitpid
#include <signal.h>		//signal, kill
#include <string.h>		//strcmp, strncmp

void	error_txt(char *s, char *arg)
{
	while (*s)
		write (2, s++, 1);
	if (arg)
		while (*arg)
			write (2, arg++, 1);
	write (2, "\n", 1);
}

int	ft_cd(char **args, int arg_count)
{
	if (arg_count != 2)
	{
		error_txt("error: cd: bad arguments", NULL);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		error_txt("error: cd: cannot change directory to ", args[1]);
		return (1);
	}
	return (0);
}

void	pipe_setup(int has_pipe, int *fd, int val)
{
	if (has_pipe && (dup2(fd[val], val) < 0 || close(fd[0]) < 0 || close(fd[1]) < 0))
	{
		error_txt("error: fatal", NULL);
		exit (1);
	}
}

int	ft_execute(char **args, char **envs, int i)
{
	int		has_pipe;
	int		fd[2];
	pid_t	pid;
	int		exit_code;

	has_pipe = args[i] && !strcmp(args[i], "|");
	if (!has_pipe && !strcmp(*args, "cd"))
		return (exit_code = ft_cd(args, i));
	if (has_pipe && pipe(fd) < 0)
	{
		error_txt("error: fatal", NULL);
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		error_txt("error: fatal", NULL);
		exit (1);
	}
	if (pid == 0)
	{
		args[i] = 0;
		pipe_setup(has_pipe, fd, 1);
		if (!strcmp(*args, "cd"))
			exit (exit_code = ft_cd(args, i));
		execve(*args, args, envs);
		error_txt("error: cannot execute ", *args);
		exit (1);
	}
	waitpid(pid, &exit_code, 0);
	pipe_setup(has_pipe, fd, 0);
	return (WIFEXITED(exit_code) && WEXITSTATUS(exit_code));
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	(void) ac;
	while (av[i])
	{
		av += i + 1;
		i = 0;
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (i)
			exit_code = ft_execute(av, env, i);
	}
	return (exit_code);
}
