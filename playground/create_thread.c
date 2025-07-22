#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void	*routine()
{
	printf("Test from Thread 1\n");
	sleep(3);
	printf("Ending thread 1\n");
	return (NULL);
}

void	*routine2()
{
	printf("Test from Thread 2\n");
	sleep(3);
	printf("Ending thread 2\n");
	return (NULL);
}


int	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;

	(void)av;
	if (ac == 2)
	{
		if (pthread_create(&t1, NULL, &routine, NULL) != 0)
			return (1);
		if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
			return (2);
		if (pthread_join(t1, NULL) != 0)
			return (3);
		if (pthread_join(t2, NULL) != 0)
			return (4);
	}
	return (0);
}
