/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_line_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:32:58 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 20:21:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <ctype.h>

// ft_split
// check the single float
// check_rgb
int	verify_ambient(t_parse_node *n)
{	
	(void)n;
	return (0);
}

// check 3dcrds
// check single float
// check rgb
int	verify_light(t_parse_node *n)
{
	(void)n;
	return (0);
}

// check 3drds
// check 3d normed vec
// check aspect ratio?
int	verify_camera(t_parse_node *n)
{
	(void)n;
	return (0);
}

int	full_empty(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (!(content[i] == ' ' || content[i] == '\t'))
			return (-1);
		i++;
	}
	return (0);
}
