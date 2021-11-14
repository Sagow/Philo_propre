/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:07:24 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 23:56:45 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	suicide(t_philosopher *philo)
{
	if (!get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		return (0);
	set_val(&(philo->life_mutex), 0, &(philo->alive));
	return (1);
}

void	my_sleep(int target, t_data *data)
{
	while (current_time(data) < target &&
		!get_val(&(data->death_mutex), &(data->dead)))
		usleep(15);
}

void	*philosophing(void *philo)
{
	t_data	*data;

	data = ((t_philosopher *)philo)->data;
	
	while (data->maxtime.max_meals == -1 ||
	((t_philosopher *)philo)->nb_meals
		< data->maxtime.max_meals)
	{
		if (suicide(((t_philosopher *)philo)))
			return (NULL);
		take_forks((t_philosopher *)philo);
		thinking_to_eating((t_philosopher *)philo);
		my_sleep(current_time(data) + data->maxtime.eat, data);
		put_forks((t_philosopher *)philo);
		if (suicide(((t_philosopher *)philo)))
			return (NULL);
		talk((t_philosopher *)philo, "is sleeping");
		my_sleep(current_time(data) + data->maxtime.sleep, data);
		if (suicide(((t_philosopher *)philo)))
			return (NULL);
		talk((t_philosopher *)philo, "is thinking");
	}
	return (NULL);
}

void	start_philos(t_philosopher **philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		printf("naissance ph%d\n", i + 1);
		(*philos)[i].id = i + 1;
		(*philos)[i].alive = 1;
		(*philos)[i].nb_meals = 0;
		set_forks((*philos) + i, data);
		(*philos)[i].data = data;
		pthread_mutex_init(&(*philos)[i].life_mutex, NULL);
		(*philos)[i].last_meal = 0;
		pthread_create(&((*philos)[i].thread), NULL, &philosophing,
			(void *)(*philos) + i);
		pthread_detach((*philos)[i].thread);
		i++;
	}
	(*philos)[i].id = 0;
}

int	main(int ac, char **av)
{
	t_philosopher	*philos;
	t_data			data;
	int				i;
	int				survivors;

	if (parsing(ac, av, &philos, &data))
		return (1);
	start_philos(&philos, &data);
	observing_philos(&philos, &data);
	survivors = 1;
	while (survivors)
	{
		survivors = 0;
		i = 0;
		while (philos[i].id)
		{
			survivors += get_val(&(philos[i].life_mutex), &(philos[i].alive));
			i++;
		}
	}
	free_all(philos, &data);
	return (0);
}
