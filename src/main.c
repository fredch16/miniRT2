/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:24:39 by fredchar          #+#    #+#             */
/*   Updated: 2025/10/30 23:56:28 by fredchar         ###   ########.fr       */
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


	t_mat testmatrix, testmatrix2;
	t_vec	c0, c1, c2, c3;

	c0 = vector(1, 2, 8);
	c0.w = 0;
	c1 = vector(2, 4, 6);
	c1.w = 0;
	c2 = vector(3, 4, 4);
	c2.w = 0;
	c3 = vector(4, 2, 1);
	c3.w = 1;

	testmatrix.c[0] = c0;
	testmatrix.c[1] = c1;
	testmatrix.c[2] = c2;
	testmatrix.c[3] = c3;

	// second
	c0 = vector(-2, 3, 4);
	c0.w = 1;
	c1 = vector(1, 2, 3);
	c1.w = 2;
	c2 = vector(2, 1, 6);
	c2.w = 7;
	c3 = vector(3, -1, 5);
	c3.w = 8;

	testmatrix2.c[0] = c0;
	testmatrix2.c[1] = c1;
	testmatrix2.c[2] = c2;
	testmatrix2.c[3] = c3;

	if (equal_matrix(testmatrix, testmatrix2))
		printf("These two are equal!\n");
	else
		printf("These two are NOTTTTTTTTTTTT equal!\n");


	printf("subtracting vector 1 from 2\n");
	t_vec test1, test2;
	test1 = point(3, 2, 1);
	test2 = point(5, 6, 7);
	t_vec res = tuple_add(test1, test2);
	print_vec4(res);
	print_vec4(tuple_neg(point(1, 2, -3)));
	printf("Mag is | %10.5f |\n", (tuple_mag(point(1, 2, -3))));
	printf("Norm is: ");
	print_vec4(tuple_norm(vector(1, 2, 3)));
	printf("Dot is | %10.5f |\n", tuple_dot(vector(1, 2, 3), vector(2, 3, 4)));

	printf("Cross is: ");
	print_vec4(tuple_cro(vector(1, 2, 3), vector(3, 4, 5)));
	int x = 0;
	int y;


	printf("testmatrix\n");
	print_mat(testmatrix);
	print_mat(mat_transpose(mat_idt()));
	// print_mat(mat_mul_mat(testmatrix, mat_idt()));

	// Test der Determinanten-Berechnung
	printf("\n=== TEST DETERMINANTE ===\n");
	t_mat test_det;
	test_det.c[0] = tuple(-2, -8, 3, 5);
	test_det.c[1] = tuple(-3, 1, 7, 3);
	test_det.c[2] = tuple(1, 2, -9, 6);
	test_det.c[3] = tuple(-6, 7, 7, -9);
	
	printf("Test Matrix:\n");
	print_mat(test_det);
	printf("\nDeterminante: %.2f\n", mat_determinant(test_det));
	
	printf("\nDeterminante der Identitätsmatrix: %.2f\n", mat_determinant(mat_idt()));

	// Test der Matrix-Invertierung
	printf("\n=== TEST MATRIX INVERSION ===\n");
	t_mat test_inv;
	test_inv.c[0] = tuple(-5, 2, 6, -8);
	test_inv.c[1] = tuple(1, -5, 1, 8);
	test_inv.c[2] = tuple(7, 7, -6, -7);
	test_inv.c[3] = tuple(1, -3, 7, 4);
	
	printf("Original Matrix A:\n");
	print_mat(test_inv);
	
	printf("\nDeterminante: %.2f\n", mat_determinant(test_inv));
	printf("Ist invertierbar: %s\n", mat_is_invertible(test_inv) ? "JA" : "NEIN");
	
	if (mat_is_invertible(test_inv))
	{
		t_mat inverted = mat_inverse(test_inv);
		printf("\nInvertierte Matrix A⁻¹:\n");
		print_mat(inverted);
		
		// Verification: A × A⁻¹ sollte Identitätsmatrix ergeben
		t_mat identity_test = mat_mul_mat(test_inv, inverted);
		printf("\nA × A⁻¹ (sollte Identität sein):\n");
		print_mat(identity_test);
	}

	// Test der Translation
	printf("\n=== TEST TRANSLATION ===\n");
	t_mat transform = translation(5, -3, 2);
	t_vec p = point(-3, 4, 5);
	
	printf("Original Punkt: ");
	print_vec4(p);
	
	t_vec translated = mat_mul_vec(transform, p);
	printf("Nach Translation(5, -3, 2): ");
	print_vec4(translated);
	printf("Erwartet: (2, 1, 7)\n");
	
	// Test: Inverse Translation
	t_mat inv_transform = mat_inverse(transform);
	t_vec back = mat_mul_vec(inv_transform, translated);
	printf("\nMit inverser Translation zurück: ");
	print_vec4(back);
	printf("Sollte wieder (-3, 4, 5) sein\n");
	
	// Test: Translation verändert Vektoren NICHT
	t_vec v = vector(-3, 4, 5);
	t_vec v_translated = mat_mul_vec(transform, v);
	printf("\nVektor vor Translation: ");
	print_vec4(v);
	printf("Vektor nach Translation: ");
	print_vec4(v_translated);
	printf("Sollte unverändert sein (w=0)\n");

	// Test der Skalierung
	printf("\n=== TEST SCALING ===\n");
	t_mat scale_transform = scaling(2, 3, 4);
	t_vec p2 = point(-4, 6, 8);
	
	printf("Original Punkt: ");
	print_vec4(p2);
	
	t_vec scaled = mat_mul_vec(scale_transform, p2);
	printf("Nach Scaling(2, 3, 4): ");
	print_vec4(scaled);
	printf("Erwartet: (-8, 18, 32)\n");
	
	// Test: Skalierung auf Vektor
	t_vec v2 = vector(-4, 6, 8);
	t_vec v_scaled = mat_mul_vec(scale_transform, v2);
	printf("\nVektor vor Scaling: ");
	print_vec4(v2);
	printf("Vektor nach Scaling(2, 3, 4): ");
	print_vec4(v_scaled);
	printf("Erwartet: (-8, 18, 32)\n");
	
	// Test: Inverse Skalierung
	t_mat inv_scale = mat_inverse(scale_transform);
	t_vec inv_scaled = mat_mul_vec(inv_scale, v2);
	printf("\nMit inverser Skalierung: ");
	print_vec4(inv_scaled);
	printf("Erwartet: (-2, 2, 2) = v * (1/2, 1/3, 1/4)\n");
	
	// Test: Reflection (Spiegelung mit negativer Skalierung)
	t_mat reflect = scaling(-1, 1, 1);
	t_vec p3 = point(2, 3, 4);
	t_vec reflected = mat_mul_vec(reflect, p3);
	printf("\nPunkt vor Reflection: ");
	print_vec4(p3);
	printf("Nach Reflection(-1, 1, 1): ");
	print_vec4(reflected);
	printf("Erwartet: (-2, 3, 4) - Spiegelung an der YZ-Ebene\n");

	// Test der Rotation
	printf("\n=== TEST ROTATION ===\n");
	
	// Test: Rotation um X-Achse (90 Grad = PI/2)
	t_mat half_quarter_x = rotation_x(M_PI / 4);
	t_vec p4 = point(0, 1, 0);
	t_vec rotated_x_half = mat_mul_vec(half_quarter_x, p4);
	printf("Punkt (0,1,0) nach Rotation X (45°): ");
	print_vec4(rotated_x_half);
	printf("Erwartet: (0, √2/2, √2/2) ≈ (0, 0.707, 0.707)\n");
	
	t_mat full_quarter_x = rotation_x(M_PI / 2);
	t_vec rotated_x_full = mat_mul_vec(full_quarter_x, p4);
	printf("Punkt (0,1,0) nach Rotation X (90°): ");
	print_vec4(rotated_x_full);
	printf("Erwartet: (0, 0, 1)\n");
	
	// Test: Inverse Rotation (gegen Uhrzeigersinn)
	t_mat inv_quarter_x = mat_inverse(half_quarter_x);
	t_vec inv_rotated_x = mat_mul_vec(inv_quarter_x, p4);
	printf("Punkt (0,1,0) nach inverser Rotation X (45°): ");
	print_vec4(inv_rotated_x);
	printf("Erwartet: (0, √2/2, -√2/2) ≈ (0, 0.707, -0.707)\n");
	
	// Test: Rotation um Y-Achse
	t_mat half_quarter_y = rotation_y(M_PI / 4);
	t_vec p5 = point(0, 0, 1);
	t_vec rotated_y_half = mat_mul_vec(half_quarter_y, p5);
	printf("\nPunkt (0,0,1) nach Rotation Y (45°): ");
	print_vec4(rotated_y_half);
	printf("Erwartet: (√2/2, 0, √2/2) ≈ (0.707, 0, 0.707)\n");
	
	t_mat full_quarter_y = rotation_y(M_PI / 2);
	t_vec rotated_y_full = mat_mul_vec(full_quarter_y, p5);
	printf("Punkt (0,0,1) nach Rotation Y (90°): ");
	print_vec4(rotated_y_full);
	printf("Erwartet: (1, 0, 0)\n");
	
	// Test: Rotation um Z-Achse
	t_mat half_quarter_z = rotation_z(M_PI / 4);
	t_vec p6 = point(0, 1, 0);
	t_vec rotated_z_half = mat_mul_vec(half_quarter_z, p6);
	printf("\nPunkt (0,1,0) nach Rotation Z (45°): ");
	print_vec4(rotated_z_half);
	printf("Erwartet: (-√2/2, √2/2, 0) ≈ (-0.707, 0.707, 0)\n");
	
	t_mat full_quarter_z = rotation_z(M_PI / 2);
	t_vec rotated_z_full = mat_mul_vec(full_quarter_z, p6);
	printf("Punkt (0,1,0) nach Rotation Z (90°): ");
	print_vec4(rotated_z_full);
	printf("Erwartet: (-1, 0, 0)\n");

	
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
