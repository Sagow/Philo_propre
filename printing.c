/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:20:53 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/16 14:23:14 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

void	talk(t_philosopher *philo, char *thing)
{
	if (!get_val(&(philo->data->death_mutex), &(philo->data->dead)))
	{
		pthread_mutex_lock(&(philo->data->micro));
		if (!(philo->data->dead))
			printf("%d %d %s\n", current_time(philo->data), philo->id, thing);
		pthread_mutex_unlock(&(philo->data->micro));
	}
}
