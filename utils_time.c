/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:26:16 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/15 22:21:14 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	current_time(t_data *data)
{
	struct timeval	time;
	int	ret;

	gettimeofday(&time, NULL);
	ret = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret - data->start);
}

int	relative_time(t_philosopher *philo)
{
	return (current_time(philo->data) + philo->perso_start);
}