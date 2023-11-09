#include "shell.h"

/**
 *main - The main function of the program.
 *@ac: The number of command-line arguments.
 *@av: An array of strings representing the command-line arguments.
 *
 *This function is the entry point of the program.
 *It reads command-line arguments, opens a file if provided,
 * and performs other tasks.
 *
 *Return: 0 on success, 1 on failure.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT
	};

	int fd = 2;

	/*Moved the assembly code to after checking the command-line argument. */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ePuts(av[0]);
				ePuts(": 0: Can't open ");
				ePuts(av[1]);
				ePutChar('\n');
				ePutChar(BUF_FLUSH);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->readfd = fd;
	}

	/*Moved the assembly code to here. */
	asm("mov %1, %0\n\t"
		"add $3, %0" : "=r"(fd) : "r"(fd));

	popuEnvList(info);
	readHistory(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
