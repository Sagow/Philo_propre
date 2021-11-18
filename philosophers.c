/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:07:24 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 19:01:25 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	*philosophing(void *p)
{
	t_data			*data;
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	data = philo->data;
	while (1)
	{
		thinking_to_eating(philo);
		if (suicide(philo))
			break ;
		talk(philo, "is sleeping");
		my_sleep(relative_time(philo) + data->maxtime.sleep, philo);
		if (suicide(philo))
			break ;
		talk(philo, "is thinking");
	}
	set_val(&(philo->life_mutex), 0, &(philo->alive));
	return (NULL);
}

void	start_philos(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].alive = 1;
		philos[i].nb_meals = 0;
		philos[i].die = 0;
		pthread_mutex_init(&philos[i].die_mutex, NULL);
		pthread_mutex_init(&philos[i].life_obs_mutex, NULL);
		set_forks(philos + i, data);
		philos[i].data = data;
		pthread_mutex_init(&philos[i].life_mutex, NULL);
		philos[i].last_meal = 0;
		pthread_mutex_init(&philos[i].last_meal_mutex, NULL);
		philos[i].perso_start = current_time(data);
		pthread_create(&(philos[i].thread), NULL, &philosophing, philos + i);
		pthread_detach(philos[i].thread);
		i++;
	}
	philos[i].id = 0;
}

void	waiting_for_death(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (!get_val(&(philos[i].die_mutex), &(philos[i].die))/* && get_val
		(&(data->all_eaten_mutex), &(data->all_eaten)) != data->nb_philos*/)
	{
		//mettre ici le decompte de miam, rajouter des mutex de nb_meals
		i++;
		if (i == data->nb_philos)
			i = 0;
	}
	//printf("i = %d eaten %d\n", i + 1, get_val(&(data->all_eaten_mutex), &(data->all_eaten)));
	/*if ()*/
		set_val(&(data->death_mutex), i + 1, &(data->dead));
	if (get_val(&(data->death_mutex), &(data->dead)) > 0)
	{
		pthread_mutex_lock(&(data->micro));
		printf("%d %d died\n", current_time(data), i + 1);
		pthread_mutex_unlock(&(data->micro));
	}
	i = 0;
	if (!get_val(&(data->death_mutex), &(data->dead)))
		set_val(&(data->death_mutex), -1, &(data->dead));
	while (i < data->nb_philos)
	{
		set_val(&(philos[i].die_mutex), 1, &(philos[i].die));
		i++;
	}
}

void	process(t_philosopher *philos, t_data *data)
{
	int	i;
	int	survivors;

	start_philos(philos, data);
	observing_philos(philos, data);
	waiting_for_death(philos, data);
	survivors = 1;
	while (survivors)
	{
		survivors = 0;
		i = -1;
		while (philos[++i].id)
		{
			survivors += get_val(&(philos[i].life_mutex),
					&(philos[i].alive));
			survivors += get_val(&(philos[i].life_obs_mutex),
					&(philos[i].obs));
		}
	}
}

int	main(int ac, char **av)
{
	t_philosopher	*philos;
	t_data			*data;

	if (ft_malloc((void **)&data, sizeof(t_data)))
		return (1);
	if (parsing(ac, av, &philos, data))
	{
		free(data);
		return (1);
	}
	if (data->nb_philos == 1)
		one_philo(data);
	else
		process(philos, data);
	free_all(philos, data);
	return (0);
}
