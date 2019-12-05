#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int ac, char** av)
{
	int a, b;

	a = 42;
	b = 21;
	printf("Smallest of %i and %i : %li\n", a, b, syscall(335, a, b));
}
