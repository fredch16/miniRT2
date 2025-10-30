/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:27:52 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/30 15:30:57 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "miniRT.h"

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;


#endif