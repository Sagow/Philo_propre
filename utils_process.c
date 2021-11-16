/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:03:44 by magostin          #+#    #+#             */
/*   Updated: 2021/11/16 20:10:45 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	suicide(t_philosopher *philo)
{
	if (!get_val(&(philo->die_mutex), &(philo->die)))
		return (0);
	return (1);
}

void	my_sleep(int target, t_philosopher *philo)
{
	while (relative_time(philo) < target
		&& !get_val(&(philo->data->death_mutex), &(philo->data->dead)))
		usleep(15);
}

void	one_philo(t_data *data)
{
	printf("%d %d has taken a fork\n", current_time(data), 1);
	usleep(data->maxtime.death * 1000);
	printf("%d %d died\n", current_time(data), 1);
}
