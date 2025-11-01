/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:39:14 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/01 17:55:52 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

inline t_vec	normal_at_sp(t_obj *o, t_vec p)
{
	(void)o;
	return (tuple_norm(tuple_sub(p, point(0, 0, 0))));
}