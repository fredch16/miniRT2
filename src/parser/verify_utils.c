/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:01:19 by fredchar          #+#    #+#             */
/*   Updated: 2025/11/07 13:05:29 by fredchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/miniRT.h"
#include <ctype.h>
#include <stdlib.h>

/* parse_double_range
 * - Parses a double from *src, advances *src to the first char after the number
 * - Checks that parsed value is within [min,max]
 * - Writes value to *out on success
 * - Returns 1 on success, 0 on failure
 */
int	parse_double_range(char **src, double min, double max, double *out)
{
	char *s;
	char *end;
	double val;

	if (!src || !*src || !out)
		return (0);
	s = *src;
	while (*s == ' ' || *s == '\t')
		s++;
	val = strtod(s, &end);
	if (end == s)
		return (0);
	if (!(val >= min && val <= max))
		return (0);
	*out = val;
	*src = end;
	return (1);
}

/* parse_rgb_triplet
 * - Parses "r,g,b" where r,g,b are integers 0-255 from *src
 * - Converts them to t_colour with components in [0,1]
 * - Advances *src to the character after the triplet
 * - Returns 1 on success, 0 on failure
 */
int	parse_rgb_triplet(char **src, t_colour *out)
{
	char *s;
	char *end;
	long v0, v1, v2;

	if (!src || !*src || !out)
		return (0);
	s = *src;
	while (*s == ' ' || *s == '\t')
		s++;
	/* first value */
	v0 = strtol(s, &end, 10);
	if (end == s || v0 < 0 || v0 > 255)
		return (0);
	s = end;
	if (*s != ',')
		return (0);
	s++;
	/* second value */
	v1 = strtol(s, &end, 10);
	if (end == s || v1 < 0 || v1 > 255)
		return (0);
	s = end;
	if (*s != ',')
		return (0);
	s++;
	/* third value */
	v2 = strtol(s, &end, 10);
	if (end == s || v2 < 0 || v2 > 255)
		return (0);
	s = end;
	/* accept whitespace or NUL after triplet */
	if (*s && *s != ' ' && *s != '\t' && *s != '\n')
		return (0);
	out->red = (double)v0 / 255.0;
	out->green = (double)v1 / 255.0;
	out->blue = (double)v2 / 255.0;
	*src = s;
	return (1);
}
