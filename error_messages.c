/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdelwaul <mdelwaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 00:00:05 by mdelwaul          #+#    #+#             */
/*   Updated: 2021/10/14 21:28:36 by mdelwaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/includes.h"

int	err_arg_nb(int ac)
{
	if (ac < 5)
		printf("Erreur : il manque %d argument(s) dans l'appel\n", 5 - ac);
	else
		printf("Erreur : il y a %d argument(s) en trop dans l'appel\n", ac - 6);
	return (ERR_ARG_NB);
}

int	err_arg_nbphilo(char *number)
{
	printf("Le nombre de philosophes \"%s\" ne semble pas valide\n", number);
	return (ERR_PARSING);
}

int	err_arg_time(void)
{
	printf("Au moins l'une des valeurs de temps ne semble pas valide\n");
	return (ERR_PARSING);
}
