/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:29:30 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 23:38:11 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	someone_hungry(t_philosopher **philos, t_data *data)
{
	int	i;

	i = 0;
	if (data->maxtime.max_meals == -1)
		return (1);
	while ((*philos)[i].id)
	{
		if ((*philos)[i].nb_meals < data->maxtime.max_meals)
			return (1);
		i++;
	}
	return (0);
}

int	get_time(struct timeval time, t_data *data)
{
	return (timeval_to_milli(&time) - data->start);
}

/*
int	died(t_philosopher *philo)
{
	struct timeval	old;

	gettimeofday(&old, NULL);
	//printf("maxtime = %d\n", philo->data->maxtime.death);
	if ((get_time(old, philo->data) - philo->last_meal > philo->data->maxtime.death)
		&& (philo->data->maxtime.max_meals == -1 || philo->nb_meals
			< philo->data->maxtime.max_meals))
	{
	//	printf("mort = %d\n", timeval_to_milli(&old));
		return (1);
	}
	//printf("%d\n",get_time(old, philo->data) - philo->last_meal);
	return (0);
}*/
