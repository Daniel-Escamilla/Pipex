# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>


int main(void)
{
	if (access("a.out", X_OK) == 0)
		printf("Si\nasd\n");
	else
		printf("No\n");
}