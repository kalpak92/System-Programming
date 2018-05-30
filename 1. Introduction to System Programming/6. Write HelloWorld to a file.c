#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	mode_t mode = S_IRUSR | S_IWUSR;

	int fildes = open("hello_world.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
	if (fildes == -1)
	{
		perror("Open Failed");
		exit(1);
	}
	write(fildes, "Hello World!\n", 13);
	close(fildes);
	return 0;
}
