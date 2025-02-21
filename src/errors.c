/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:47:22 by kcisse            #+#    #+#             */
/*   Updated: 2025/02/19 11:47:23 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_error(char *err_msg)
{
	write(1, "Error\n", 6);
	if(err_msg)
		write(1, err_msg, ft_strlen(err_msg));
	exit(1);
}
