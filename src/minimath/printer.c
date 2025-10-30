/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:38:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/30 22:59:26 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_mat(t_mat mat)
{
	printf("Matrix is as follows:\n");
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].x, mat.c[1].x, mat.c[2].x, mat.c[3].x);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].y, mat.c[1].y, mat.c[2].y, mat.c[3].y);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].z, mat.c[1].z, mat.c[2].z, mat.c[3].z);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].w, mat.c[1].w, mat.c[2].w, mat.c[3].w);
}

void	print_vec4(t_vec tup)
{
	if (tup.w == 1)
		printf("The POINT (w = 1) is as follows\n");
	else if (tup.w == 0)
		printf("The VECTOR (w = 0) is as follows\n");
	else
		printf("The TUPLE (w = %10.5f) is as follows\n", tup.w);
	printf("| x = %10.5f |\n", tup.x);
	printf("| y = %10.5f |\n", tup.y);
	printf("| z = %10.5f |\n", tup.z);
}

void	print_xs(t_xsn *xs)
{
	t_xsn	*tmp;

	if (!xs)
	{
		printf("No intersections found\n");
		return ;
	}
	tmp = xs;
	while (tmp)
	{
		printf("Intersection found at | t = %10.5f | ", tmp->t);
		if (tmp->xs_obj->type == OT_SPHERE)
			printf("with type SPHERE\n");
		else
			printf("with type UNKNOWN\n");
		tmp = tmp->next;
	}
}