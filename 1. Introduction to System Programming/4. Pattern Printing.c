#include <unistd.h>

void write_triangle(int n)
{
	int count;
	for (count = 1; count <= n; count++)
	{
		for (int j = 1; j <= count; j++)
			write(1, "*", 1);

		write(1, "\n", 1);
	}

}

int main(int argc, char const *argv[])
{
	write_triangle(3);
	return 0;
}