/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:42:13 by kcisse            #+#    #+#             */
/*   Updated: 2025/04/14 14:43:05 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_down(double angle)
{
	if (angle > 0 && angle < PI)
		return (true);
	return (false);
}

bool	is_up(double angle)
{
	if (!is_down(angle))
		return (true);
	return (false);
}

bool	is_right(double angle)
{
	if (angle < (0.5 * PI) || angle > (1.5 * PI))
		return (true);
	return (false);
}

bool	is_left(double angle)
{
	if (!is_right(angle))
		return (true);
	return (false);
}
