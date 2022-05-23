#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void test1(char *argv)
{
	int	fd1;
	char	*line;
	int	ret;

	printf("\nReading file '%s' and printing return values from every call:\n", argv);
	ret = 1;
	fd1 = open(argv, O_RDONLY);
	while (ret == get_next_line(fd1, &line))
	{
		printf("%d '%s'\n", ret, line);
		ft_strdel(&line);
	}
	printf("%d\n", get_next_line(fd1, &line));
	ft_strdel(&line);
	close(fd1);
}

void	test4()
{
	char 	*line = NULL;

    printf("\nTrying negative or non-opened file descriptors, should be all -1:\n");
	printf("%d\n", get_next_line(-99, NULL));
	printf("%d\n", get_next_line(-1, NULL));
	printf("%d\n", get_next_line(20000, NULL));
	printf("%d\n", get_next_line(-1, NULL));
	printf("%d\n", get_next_line(-99, NULL));
	printf("%d\n", get_next_line(-99, &line));
	printf("%d\n", get_next_line(-1, &line));
	printf("%d\n", get_next_line(20000, &line));
	printf("%d\n", get_next_line(42, &line));
}

void	test5()
{
	char	*line_fd0;
	int		p_fd0[2];
	int		fd0 = 0;
	int		out_fd0 = dup(fd0);

	char	*line_fd1;
	int		p_fd1[2];
	int		fd1 = 1;
	int		out_fd1 = dup(fd1);

	char	*line_fd2;
	int		p_fd2[2];
	int		fd2 = 2;
	int		out_fd2 = dup(fd2);

	char	*line_fd3;
	int		p_fd3[2];
	int		fd3 = 3;
	int		out_fd3 = dup(fd3);

	printf("\nRunning bonus test...\n\nTrying to read from different file descriptors, strcmp should return 0 everywhere:\n");
	pipe(p_fd0);
	dup2(p_fd0[1], fd0);
	write(fd0, "aaa\nbbb\n", 8);
	dup2(out_fd0, fd0);
	close(p_fd0[1]);

	pipe(p_fd1);
	dup2(p_fd1[1], fd1);
	write(fd1, "111\n222\n", 8);
	dup2(out_fd1, fd1);
	close(p_fd1[1]);

	pipe(p_fd2);
	dup2(p_fd2[1], fd2);
	write(fd2, "www\nzzz\n", 8);
	dup2(out_fd2, fd2);
	close(p_fd2[1]);

	pipe(p_fd3);
	dup2(p_fd3[1], fd3);
	write(fd3, "888\n999\n", 8);
	dup2(out_fd3, fd3);
	close(p_fd3[1]);

	get_next_line(p_fd0[0], &line_fd0);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd0, "aaa"), line_fd0);

	get_next_line(p_fd1[0], &line_fd1);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd1, "111"), line_fd1);

	get_next_line(p_fd2[0], &line_fd2);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd2, "www"), line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd3, "888"), line_fd3);

	get_next_line(p_fd0[0], &line_fd0);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd0, "bbb"), line_fd0);

	get_next_line(p_fd1[0], &line_fd1);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd1, "222"), line_fd1);

	get_next_line(p_fd2[0], &line_fd2);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd2, "zzz"), line_fd2);

	get_next_line(p_fd3[0], &line_fd3);
	printf("Strcmp returns %d, line is '%s'\n", strcmp(line_fd3, "999"), line_fd3);
}

void	test6()
{
	int	fd;
	char *line;
	int ret;

	fd = 0;
	ret = 1;
	while (ret == get_next_line(fd, &line))
	{
		printf("fd %d ret  %d  %s\n", fd, ret, line);
	}
}

int		main(int argc, char *argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
			test1(argv[i]);
	}
	else
	{
		// test4();
		// test5();
		test6();
	}
	return (0);
}
