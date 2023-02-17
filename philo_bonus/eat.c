/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <eablak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:37:14 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 11:55:18 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->mutual->forks);
	my_print(philo, "has taken a fork");
	sem_wait(philo->mutual->forks);
	my_print(philo, "has taken a fork");
	sem_wait(philo->mutual->eat);
	my_print(philo, "is eating");
	philo->last_eat = get_current_time();
	philo->each_time++;
	sem_post(philo->mutual->eat);
	time_pass(philo->mutual->time_to_eat, philo);
	sem_post(philo->mutual->forks);
	sem_post(philo->mutual->forks);
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
