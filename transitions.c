/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:44:50 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 18:55:01 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	thinking_to_eating(t_philosopher *philo)
{
	if (take_forks(philo))
		return ;
	set_val(&(philo->last_meal_mutex), current_time(philo->data),
		&(philo->last_meal));
	talk(philo, "is eating");
	philo->nb_meals++;
	if (philo->nb_meals == philo->data->maxtime.max_meals)
		set_val(&(philo->data->all_eaten_mutex),
			get_val(&(philo->data->all_eaten_mutex), &(philo->data->all_eaten))
			+ 1, &(philo->data->all_eaten));
	my_sleep(current_time(philo->data) + philo->data->maxtime.eat, philo);
	put_forks(philo);
}

void	kill_philos(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	if (!get_val(&(data->death_mutex), &(data->dead)))
		set_val(&(data->death_mutex), -1, &(data->dead));
	while (i < data->nb_philos)
	{
		set_val(&(philos[i].die_mutex), 1, &(philos[i].die));
		i++;
	}
}
