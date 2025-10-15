/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:16:16 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 13:26:44 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	print_matrix4(t_matrix4 mat)
{
	printf("Matrix is as follows:\n");
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].x, mat.c[1].x, mat.c[2].x, mat.c[3].x);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].y, mat.c[1].y, mat.c[2].y, mat.c[3].y);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].z, mat.c[1].z, mat.c[2].z, mat.c[3].z);
	printf("| %10.5f | %10.5f | %10.5f | %10.5f |\n", mat.c[0].w, mat.c[1].w, mat.c[2].w, mat.c[3].w);
}
