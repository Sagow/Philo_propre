/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:25:02 by krain             #+#    #+#             */
/*   Updated: 2021/11/18 19:00:03 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	*life_tracking(void *p)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	while (!get_val(&(philo->die_mutex), &(philo->die)))
	{
		if (get_val(&(philo->last_meal_mutex), &(philo->last_meal))
			+ philo->data->maxtime.death < current_time(philo->data))
			set_val(&(philo->die_mutex), 1, &(philo->die));
	}
	set_val(&(philo->life_obs_mutex), 0, &(philo->obs));
	return (NULL);
}

void	observing_philos(t_philosopher *philos, t_data *data)
{
	int		i;

	if (ft_malloc((void **)&(data->observers),
			sizeof(pthread_t) * data->nb_philos))
		return ;
	i = 0;
	while (i < data->nb_philos)
	{
		set_val(&(philos[i].life_obs_mutex), 1, &(philos[i].obs));
		pthread_create((data->observers + i), NULL, &life_tracking,
			(philos + i));
		pthread_detach(*(data->observers + i));
		i++;
	}
}
