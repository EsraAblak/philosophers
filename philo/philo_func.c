/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:49:06 by eablak            #+#    #+#             */
/*   Updated: 2023/01/26 14:49:10 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_printf(t_philo *philo, char *str)
{
	long long	tt;

	tt = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->death);
	if (*philo->is_death != 1)
		printf("%lld %d %s", tt, philo->id, str);
	pthread_mutex_unlock(philo->death);
	return (0);
}

int	check_av(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}

unsigned long	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

unsigned long	get_passed_time(unsigned long time)
{
	return (get_current_time() - time);
}

void	time_pass(int time)
{
	unsigned long	now;

	now = get_current_time();
	while (get_passed_time(now) < (unsigned long)time)
		usleep(100);
}
