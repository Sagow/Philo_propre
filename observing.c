/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 22:25:02 by krain             #+#    #+#             */
/*   Updated: 2021/11/13 23:51:59 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	*life_tracking(void *philo)
{
	while (((t_philosopher *)philo)->last_meal
		+ ((t_philosopher *)philo)->data->maxtime.death
		> current_time(((t_philosopher *)philo)->data)
		&& get_val(&(((t_philosopher *)philo)->life_mutex),
			&(((t_philosopher *)philo)->alive)))
		usleep(20);
	if (!get_val(&(((t_philosopher *)philo)->life_mutex),
		&(((t_philosopher *)philo)->alive)))
		return (NULL);
	announce_death((t_philosopher *)philo);
	return (NULL);
}

void	observing_philos(t_philosopher **philos, t_data *data)
{
	int	i;
	pthread_t	*observers;

	printf("observing\n");

	if (ft_malloc((void **)&observers, sizeof(pthread_t) * data->nb_philos))
		return ;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create((observers + i), NULL, &life_tracking,
			(void *)(*philos + i));
		pthread_detach(*(observers + i));
		i++;
	}
	
}
