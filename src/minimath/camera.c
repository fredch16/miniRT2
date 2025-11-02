/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:26:23 by swied             #+#    #+#             */
/*   Updated: 2025/11/02 19:34:17 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_mat   view_transform(t_vec from, t_vec to, t_vec up)
{
    t_vec   forward;
    t_vec   upn;
    t_vec   left;
    t_vec   true_up;
    t_mat   orientation;
    
    forward = tuple_norm(tuple_sub(to, from));
    upn = tuple_norm(up);
    left = tuple_cro(forward, upn);
    true_up = tuple_cro(left, forward);
    orientation = mat(
        tuple(left.x, left.y, left.z, 0),
        tuple(true_up.x, true_up.y, true_up.z, 0),
        tuple(-forward.x, -forward.y, -forward.z, 0),
        tuple(0, 0, 0, 1)
    );
    return (mat_mul_mat(orientation, translation(-from.x, -from.y, -from.z)));
}
