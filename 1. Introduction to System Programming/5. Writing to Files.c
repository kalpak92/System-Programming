#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	mode_t mode = S_IRUSR | S_IWUSR;
	int fildes = open("output.txt", O_CREAT | O_TRUNC | O_RDWR, mode);
	write(fildes, "Great!\n", 7);
	close(fildes);
	
	return 0;
}