/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:38:35 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/14 15:44:32 by swied            ###   ########.fr       */
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

	tmp = NULL;
	if (!xs)
	{
		printf("No intersections found\n");
		return ;
	}
	tmp = xs;
	while (tmp)
	{
		printf("Intersection found at | t = %10.5f | ", tmp->t);
		if (tmp->xs_obj && tmp->xs_obj->type == OT_SPHERE)
			printf("with type SPHERE\n");
		else if (tmp->xs_obj)
			printf("with type UNKNOWN\n");
		else
			printf("with NO object attached\n");
		tmp = tmp->next;
	}
}

void	print_comps(t_comps comps)
{
	printf("---- t_comps ----\n");
	printf("t = %10.5f\n", comps.t);
	if (comps.obj)
	{
		printf("obj ptr = %p | type = ", (void *)comps.obj);
		if (comps.obj->type == OT_SPHERE)
			printf("SPHERE\n");
		else
			printf("UNKNOWN(%d)\n", comps.obj->type);
	}
	else
		printf("obj = NULL\n");
	printf("inside = %s\n", comps.inside ? "true" : "false");
	printf("point:\n");
	print_vec4(comps.point);
	printf("eyev:\n");
	print_vec4(comps.eyev);
	printf("normalv:\n");
	print_vec4(comps.normalv);
}

void	print_colour(t_colour col)
{
	printf("Colour -> r = %10.5f | g = %10.5f | b = %10.5f\n",
		col.red, col.green, col.blue);
}