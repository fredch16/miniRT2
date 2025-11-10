/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:01:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/10 00:57:23 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/miniRT.h"
#include <ctype.h>
#include <stdlib.h>

int	verify_colours(t_colour col)
{
	if (col.blue > (1 + EPSILON) || col.blue < 0)
		return (-1);
	if (col.red > (1 + EPSILON) || col.red < 0)
		return (-1);
	if (col.green > (1 + EPSILON) || col.green < 0)
		return (-1);
	return (0);
}