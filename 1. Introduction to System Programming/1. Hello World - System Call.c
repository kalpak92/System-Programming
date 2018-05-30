#include <unistd.h>

int main()
{
	write(1, "Hello\n", 6);
	write(1, "World\n", 6);
	return 0;
}