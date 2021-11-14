/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 23:59:35 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/13 23:21:33 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	get_val(pthread_mutex_t *mutex, int	*val)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	set_val(pthread_mutex_t *mutex, int val, int *where)
{
	pthread_mutex_lock(mutex);
	*where = val;
	pthread_mutex_unlock(mutex);
}

int	ft_malloc(void **ptr, int size)
{
	*ptr = NULL;
	*ptr = malloc((size_t) size);
	if (*ptr == NULL)
		return (-1);
	return (0);
}

int	ft_atoi(const char *number)
{
	int	i;
	int	res;

	if (!number || number[0] < '0' || number[0] > '9')
		return (ERR_ARG_ATOI);
	i = 0;
	res = 0;
	while (number[i] >= '0' && number[i] <= '9')
	{
		res = res * 10 + number[i] - '0';
		i++;
	}
	return (res);
}

int	free_all(t_philosopher *philosophers, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	free(philosophers);
	free(data->forks);
	pthread_mutex_destroy(&(data->death_mutex));
	//pthread_mutex_unlock(&(data->micro));
	pthread_mutex_destroy(&(data->micro));
	return (0);
}
