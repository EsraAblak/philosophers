/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:47:01 by eablak            #+#    #+#             */
/*   Updated: 2023/01/26 14:47:35 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_printf(philo, "has taken a fork\n");
	if (philo->num_of_philos == 1)
	{
		time_pass(philo->time_to_die);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	ft_printf(philo, "has taken a fork\n");
	ft_printf(philo, "is eating\n");
	return (0);
}

int	eat2(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	philo->each_time++;
	philo->last_eat = get_current_time();
	pthread_mutex_unlock(philo->death);
	time_pass(philo->time_to_eat);
	ft_printf(philo, "is sleeping\n");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	time_pass(philo->time_to_sleep);
	ft_printf(philo, "is thinking\n");
	return (0);
}

void	*get_room(void *philo)
{
	t_philo	*pp;
	int		i;

	pp = philo;
	i = 0;
	if (pp->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (eat(pp))
			break ;
		if (eat2(pp))
			break ;
	}
	return (NULL);
}
