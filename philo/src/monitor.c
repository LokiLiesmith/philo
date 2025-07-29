#include "philo.h"

int	create_monitor(t_table *table)
{
	if (pthread_create(&table->monitor, NULL, &monitor_routine, (void *)table) != 0)
	{
		table->init_flags.monitor_flag = 0;
		return (1);
	}
	table->init_flags.monitor_flag = 1;
	return (0);
}

void *monitor_routine(void *arg)
{
	t_table *table;

	table = (t_table*) arg;
	printf("Monitor created.\n");
	printf("Monitor_flag = %d\n", table->init_flags.monitor_flag);
	wait_for_start(table);
	while(!has_sim_ended(table))
	{
		usleep(500);
		pthread_mutex_lock(&table->sim_end_lock);
		table->simulation_ended = 1;
		pthread_mutex_unlock(&table->sim_end_lock);
	}
	return (NULL);
}
