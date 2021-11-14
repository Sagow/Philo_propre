/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:26:16 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/14 13:39:22 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	timeval_to_milli(struct timeval *s_and_us)
{
	int	milli;

	milli = s_and_us->tv_sec * 1000 + s_and_us->tv_usec / 1000;
	return (milli);
}

int	milli_to_usec(int milli)
{
	return (milli * 1000);
}

int	current_time(t_data *data)
{
	struct timeval	time;
	int	ret;

	gettimeofday(&time, NULL);
	ret = timeval_to_milli(&time) - data->start;
	return (ret);
}

int	relative_time(t_philosopher *philo)
{
	return (current_time(philo->data) + philo->perso_start);
}