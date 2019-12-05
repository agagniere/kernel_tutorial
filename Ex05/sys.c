/* in kernel/sys.c */

SYSCALL_DEFINE2(my_smallest, long int, a, long int, b)
{
	return a < b ? a : b;
}
