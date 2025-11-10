/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/10 00:45:09 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

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

int	main(int ac, char **av)
{

	(void)ac;
	(void)av;
	if (ac != 2)
	{
		printf("USAGE: ./miniRT <scene.rt>\n");
		return (-1);
	}
	t_parse_node	*pn;
	pn = pn_from_file(av[1]);
	pn_print(pn);
	// if (verify_pn_list(pn) < 0)
	// 	return (printf("Incorrect object entered!\n"), -1);
	t_world	world = {0}; 
	world.parser.error_flag = 0;
	while (pn && world.parser.error_flag == 0)
	{
		world.parser.error_flag = construct_world(&world, pn);
		if (world.parser.error_flag < 0)
			return (printf("Error\n"), -1);
		pn = pn->next;
	}
	printf("OKAYYYY LETS GO\n");
	print_colour(world.ambient);

	// return (0);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Render scene
	printf("Starting render: %dx%d pixels...\n", WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; y++)
	{
		// Progress indicator every 10%
		if (y % (HEIGHT / 10) == 0)
			printf("Rendering progress: %.1f%%\n", (float)y / HEIGHT * 100);
			
		for (int x = 0; x < WIDTH; x++)
		{
			t_ray r = ray_for_pixel(world.camera, x, y);
			t_colour color = colour_at(&world, r);
			mlx_put_pixel(img, x, y, colour_to_rgba(color));
		}
	}
	printf("Render complete!\n");

	printf("\n\n\n\nDEBUGGING ZONE:\n");
	printf("Ambient\n");
	print_colour(world.ambient);
	printf("World Light\n");
	print_colour(world.light.colour);
	print_colour(colour_at(&world, ray_for_pixel(world.camera, 0, 0)));

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
