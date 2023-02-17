/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:39:43 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 11:41:13 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_print(t_philo *philo, char *str)
{
	long long	tt;

	sem_wait(philo->mutual->print);
	if (philo->mutual->is_dead == 1)
	{
		sem_post(philo->mutual->print);
		return ;
	}
	tt = get_passed_time(philo->mutual->start_time);
	printf ("%llu %d %s\n", tt, philo->id, str);
	sem_post(philo->mutual->print);
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

void	time_pass(int time, t_philo *philo)
{
	unsigned long	now;

	now = get_current_time();
	while (get_passed_time(now) <= (unsigned long)time
		&& philo->mutual->is_dead == 0)
		usleep(100);
}
