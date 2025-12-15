/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_example.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:30:00 by swied            #+#    #+#             */
/*   Updated: 2025/12/15 15:30:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * EXAMPLE USAGE OF THE PARSER
 * 
 * This file demonstrates how to use the parsing functions to load a scene
 * from a .rt file instead of hardcoding the scene.
 * 
 * To use in main.c, replace the hardcoded scene setup with:
 * 
 *     t_world world;
 *     
 *     if (ac != 2)
 *     {
 *         ft_putstr_fd("Usage: ./miniRT <scene_file.rt>\n", 2);
 *         return (1);
 *     }
 *     
 *     if (parse_scene(av[1], &world) < 0)
 *     {
 *         ft_putstr_fd("Failed to parse scene\n", 2);
 *         return (1);
 *     }
 *     
 *     // Now world contains all the parsed data:
 *     // - world.ambient (ambient lighting)
 *     // - world.light (point light)
 *     // - world.camera (camera with transform already set up)
 *     // - world.obj_list (linked list of all objects)
 *     
 *     // Proceed with rendering...
 *     mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT - Ray Tracer", true);
 *     // ... rest of rendering code
 *     
 *     // Don't forget to free resources when done:
 *     free_world(&world);
 * 
 * 
 * SCENE FILE FORMAT (.rt):
 * 
 * A    ratio                      R,G,B
 * L    position(x,y,z)           intensity    R,G,B
 * C    position(x,y,z)           orientation(x,y,z)    FOV
 * 
 * sp   position(x,y,z)           diameter    R,G,B
 * pl   position(x,y,z)           normal(x,y,z)    R,G,B
 * cy   position(x,y,z)           axis(x,y,z)    diameter    height    R,G,B
 * 
 * Example scene file (scenes/simple.rt):
 * 
 *     A 0.2                          255,255,255
 *     
 *     L 0,100,-80                   0.8    255,255,255
 *     
 *     C 0,0,-50                     0,0,1    70
 *     
 *     sp 0,0,0                      16    255,0,0
 *     sp -15,0,0                    12    0,255,0
 *     sp 15,0,0                     12    0,0,255
 *     
 *     pl 0,-50,0                    0,1,0    100,100,100
 * 
 */

#include "../include/parser.h"
#include "../include/miniRT.h"

/*
 * This is just an example/documentation file.
 * The actual usage should be implemented in main.c
 */

int	example_main(int ac, char **av)
{
	t_world	world;
	
	if (ac != 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file.rt>\n", 2);
		return (1);
	}
	
	// Parse the scene file
	if (parse_scene(av[1], &world) < 0)
	{
		ft_putstr_fd("Failed to parse scene\n", 2);
		return (1);
	}
	
	// Now world is populated with all scene data
	printf("Scene loaded successfully!\n");
	printf("Ambient: R=%.2f G=%.2f B=%.2f\n", 
		world.ambient.red, world.ambient.green, world.ambient.blue);
	printf("Light position: (%.2f, %.2f, %.2f)\n",
		world.light.position.x, world.light.position.y, world.light.position.z);
	
	// Count objects
	int count = 0;
	t_obj *curr = world.obj_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	printf("Number of objects: %d\n", count);
	
	// Clean up
	free_world(&world);
	
	return (0);
}
