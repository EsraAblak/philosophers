/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eablak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:37:50 by eablak            #+#    #+#             */
/*   Updated: 2023/01/31 11:29:39 by eablak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_destroy(philo[i].left_fork);
		pthread_mutex_destroy(philo[i].right_fork);
		i++;
	}
}

void	create_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_create(&philo[i].thread, NULL, &get_room, &philo[i]);
		i++;
		usleep(100);
	}
	if (philo->num_of_philos == 1)
	{
		i = 0;
		while (i < philo->num_of_philos)
		{
			pthread_join(philo[i].thread, NULL);
			i++;
		}
	}
	while (1)
	{
		check_cases(philo);
		if (*philo->is_death == 1)
			break ;
	}
}

void	create_mutex(t_philo *philo)
{
	int				i;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*death;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * philo->num_of_philos);
	death = malloc(sizeof(pthread_mutex_t));
	while (i < philo->num_of_philos)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->num_of_philos];
		i++;
	}
	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		philo[i].death = death;
		i++;
	}
	pthread_mutex_init(philo->death, NULL);
}

void	fill_philo(t_philo *philo, char **av, int ac, int *is_all_dead)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].num_of_philos = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		philo[i].last_eat = get_current_time();
		philo[i].start_time = get_current_time();
		philo[i].is_death = is_all_dead;
		philo[i].each_time = 0;
		if (ac == 6)
			philo[i].must_eat = ft_atoi(av[5]);
		else
			philo[i].must_eat = -1;
		i++;
	}
}

int	main(int ac, char **av)
{
	int		*is_all_dead;
	t_philo	*philo;

	if ((ac != 5 && ac != 6) || check_av(ac, av) == 1)
	{
		printf("invalid arugument\n");
		return (1);
	}
	is_all_dead = malloc(sizeof(int));
	*is_all_dead = 0;
	philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	fill_philo(philo, av, ac, is_all_dead);
	create_mutex(philo);
	create_thread(philo);
	ft_free(philo);
	return (1);
}
