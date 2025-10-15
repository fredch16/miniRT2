/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_ops1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:20:02 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 15:37:38 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

// THE SAME CODE
// inline t_tuple	tuple_sub(t_tuple *a, t_tuple *b)
// {
// 	t_tuple	c;

// 	c.x = a->x - b->x;
// 	c.y = a->y - b->y;
// 	c.z = a->z - b->z;
// 	c.w = a->w - b->w;
// 	return (c);
// }

inline t_tuple	tuple_sub(const t_tuple *a, const t_tuple *b)
{
	return ((t_tuple){a->x - b->x, a->y - b->y,	a->z - b->z, a->w - b->w});
}
