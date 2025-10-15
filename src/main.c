/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/15 14:10:30 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/include/MLX42/MLX42.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	mlx_hook(mlx_key_data_t mlx_key_data, void *param)
{
	mlx_t *mlx = param;

	if (mlx_key_data.key == MLX_KEY_ESCAPE)
	{
		//free
		printf("WINDOW IS BEING CLOSED DUE TO ESCAPE KEY\n");
		mlx_close_window(mlx);
	}
}

int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	/* Do stuff */


	t_matrix4 testmatrix;
	t_tuple	c0, c1, c2, c3;
	c0.x = 1;
	c0.y = 5.5;
	c0.z = 9;
	c0.w = 13.5;
	c1.x = 2;
	c1.y = 6.5;
	c1.z = 10;
	c1.w = 14.5;
	c2.x = 3;
	c2.y = 7.5;
	c2.z = 11;
	c2.w = 15.5;
	c3.x = 4;
	c3.y = 8.5;
	c3.z = 12;
	c3.w = 16.5;

	testmatrix.c[0] = c0;
	testmatrix.c[1] = c1;
	testmatrix.c[2] = c2;
	testmatrix.c[3] = c3;
	print_matrix4(testmatrix);
	t_matrix4 testmatrix2;
	testmatrix2 = testmatrix;
	testmatrix2.c[0].x = 1.000001;
	print_matrix4(testmatrix2);

	if (equal_matrix(testmatrix, testmatrix2))
		printf("These two are equal!\n");
	else
		printf("These two are NOTTTTTTTTTTTT equal!\n");

	int x = 0;
	int y;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
