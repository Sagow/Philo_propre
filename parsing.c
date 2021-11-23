/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krain <krain@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:01:37 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/11/18 16:57:34 by krain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	init_forks(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(data->forks + i, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	set_philosophers_and_forks(char *number, t_philosopher **philosophers,
t_data *data)
{
	int	nb;

	nb = ft_atoi(number);
	if (nb < 1)
		return (ERR_ARG_ATOI);
	if (ft_malloc((void **)&((*philosophers)), sizeof(t_philosopher)
			* (nb + 1)))
		return (ERR_MALLOC);
	if (ft_malloc((void **)(&data->forks), sizeof(pthread_mutex_t) * (nb + 1)))
	{
		free(*philosophers);
		return (ERR_MALLOC);
	}
	data->nb_philos = nb;
	if (init_forks(data, nb))
	{
		free(*philosophers);
		free(data->forks);
		return (ERR_MUTEX_INIT);
	}
	return (0);
}

int	set_maxtime(int ac, char **av, t_timespan *maxtime)
{
	long int	nb;

	nb = ft_atoi(av[2]);
	if (nb <= 0 || nb > __INT_MAX__)
		return (ERR_ARG_ATOI);
	maxtime->death = nb;
	nb = ft_atoi(av[3]);
	if (nb <= 0 || nb > __INT_MAX__)
		return (ERR_ARG_ATOI);
	maxtime->eat = nb;
	nb = ft_atoi(av[4]);
	if (nb <= 0 || nb > __INT_MAX__)
		return (ERR_ARG_ATOI);
	maxtime->sleep = nb;
	if (ac == 6)
	{
		nb = ft_atoi(av[5]);
		if (nb <= 0 || nb > __INT_MAX__)
			return (ERR_ARG_ATOI);
		maxtime->max_meals = nb;
	}
	else
		maxtime->max_meals = -1;
	return (0);
}

int	parsing(int ac, char **av, t_philosopher **philosophers, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (err_arg_nb(ac));
	if (set_philosophers_and_forks(av[1], philosophers, data))
		return (err_arg_nbphilo(av[1]));
	if (set_maxtime(ac, av, &(data->maxtime)))
	{
		free(data->forks);
		free(*philosophers);
		return (err_arg_time());
	}
	data->start = 0;
	data->start = current_time(data);
	pthread_mutex_init(&(data->micro), NULL);
	pthread_mutex_init(&(data->death_mutex), NULL);
	data->dead = 0;
	data->all_eaten = 0;
	pthread_mutex_init(&(data->all_eaten_mutex), NULL);
	data->observers = NULL;
	return (0);
}
