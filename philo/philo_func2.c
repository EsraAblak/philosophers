/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:20 by eablak            #+#    #+#             */
/*   Updated: 2023/01/26 14:50:32 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	any_death(t_philo *philo, long long tttt)
{
	if (tttt > philo->time_to_die)
	{
		printf("%lld %d %s", tttt, philo->id, "died\n");
		*philo->is_death = 1;
		return (1);
	}
	return (0);
}

int	total_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->must_eat == -1)
		return (0);
	else
	{
		while (i < philo->num_of_philos)
		{
			if (philo[i].each_time < philo[i].must_eat)
				return (0);
			i++;
		}
	}
	*philo->is_death = 1;
	return (1);
}

void	check_cases(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo->death);
		if (any_death(philo, (get_current_time() - philo[i].last_eat))
			|| total_eat(philo))
			break ;
		i++;
		pthread_mutex_unlock(philo->death);
	}
}

void	ft_clean(t_philo *philo)
{
	philo->id = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	philo->must_eat = 0;
	philo->last_eat = 0;
	philo->start_time = 0;
	philo->each_time = 0;
	philo->num_of_philos = 0;
}

int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	long	sayi;

	i = 0;
	neg = 1;
	sayi = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sayi = sayi * 10 + (str[i] - 48);
		if (sayi * neg < -2147483648)
			return (0);
		else if (sayi * neg > 2147483647)
			return (-1);
		i++;
	}
	return (sayi * neg);
}
