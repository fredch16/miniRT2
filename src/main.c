/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/12/21 23:32:55 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

// Exit the program as failure.
static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	mlx_hook(mlx_key_data_t mlx_key_data, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_key_data.key == MLX_KEY_ESCAPE)
	{
		printf("WINDOW IS BEING CLOSED DUE TO ESCAPE KEY\n");
		mlx_close_window(mlx);
	}
}

void	init(t_world *world)
{
	world->parser.error_flag = 0;
	world->parser.a_count = 0;
	world->parser.l_count = 0;
	world->parser.c_count = 0;
}

void	render(t_world *world, mlx_image_t *img)
{
	int			y;
	int			x;
	t_ray		r;
	t_colour	color;

	y = 0;
	printf("Starting render: %dx%d pixels...\n", WIDTH, HEIGHT);
	while (y < HEIGHT)
	{
		if (y % (HEIGHT / 10) == 0)
			printf("Rendering progress: %.1f%%\n", (float)y / HEIGHT * 100);
		x = 0;
		while (x < WIDTH)
		{
			r = ray_for_pixel(world->camera, x, y);
			color = colour_at(world, r);
			mlx_put_pixel(img, x, y, colour_to_rgba(color));
			x++;
		}
		y++;
	}
	obj_clear(&(world->obj_list));
	printf("Render complete!\n");
}

int	main(int ac, char **av)
{
	t_world		world = {0};
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (ac != 2)
	{
		printf("USAGE: ./miniRT <scene.rt>\n");
		return (-1);
	}
	init(&world);
	if (parse_that_jawn(&world, av[1]) < 0)
		return (-1);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	render(&world, img);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	mlx_key_hook(mlx, mlx_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
