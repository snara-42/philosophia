#include <unistd.h>
#include <sys/time.h>

time_t	get_time(void)
{
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

void	msleep(time_t t)
{
	const time_t	end = get_time() + t;

	while (get_time() < end)
	{
		usleep(100);
	}
}

