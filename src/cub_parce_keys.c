/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parce_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwinfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 17:04:50 by vwinfred          #+#    #+#             */
/*   Updated: 2021/03/05 17:04:51 by vwinfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void					check_valid_color(char *rgb, t_cub *cub)
{
	int					i;

	i = 0;
	if (rgb[i] == '-')
		cub_error("Error! Not valide color.\n", cub, FD_TEX);
	while (rgb[i])
	{
		if (rgb[i] != ' ' && rgb[i] != '0' && rgb[i] != '1'
		&& rgb[i] != '2' && rgb[i] != '3' && rgb[i] != '4'
		&& rgb[i] != '5' && rgb[i] != '6' && rgb[i] != '7'
		&& rgb[i] != '8' && rgb[i] != '9')
			cub_error("Error! Not valide color.\n", cub, FD_TEX);
		i++;
	}
}

void					check_one_more_null(int color, char *rgb, t_cub *cub)
{
	int					nbr_null;
	int					i;

	i = 0;
	nbr_null = 0;
	while (rgb[i++])
		if (rgb[i] == '0')
			nbr_null++;
	if (nbr_null == 2 && color == 100)
		return ;
	if (nbr_null == 2 && color == 200)
		return ;
	if (nbr_null >= 2)
		cub_error("Error! Not valide color.\n", cub, FD_TEX);
}

void					super_check_number_element_colors(t_cub *cub,
						char *color)
{
	char				**check;

	check = NULL;
	check = ft_split(color, ' ');
	if (check[1] || !check[0])
	{
		free_array(check);
		cub_error("Error! WTF RGB???\n", cub, FD_TEX);
	}
	free_array(check);
}

void					colors_check(t_cub *cub, char *red,
									char *green, char *blue)
{
	check_valid_color(red, cub);
	check_valid_color(green, cub);
	check_valid_color(blue, cub);
	cub->r = ft_atoi(red);
	cub->g = ft_atoi(green);
	cub->b = ft_atoi(blue);
	check_one_more_null(cub->r, red, cub);
	check_one_more_null(cub->g, green, cub);
	check_one_more_null(cub->b, blue, cub);
	super_check_number_element_colors(cub, red);
	super_check_number_element_colors(cub, green);
	super_check_number_element_colors(cub, blue);
	free(red);
	free(green);
	free(blue);
}

int						parse_color(char *color, t_cub *cub)
{
	char				**rgb;
	char				*red;
	char				*green;
	char				*blue;

	rgb = NULL;
	rgb = ft_split(color, ',');
	if (rgb[3] || !rgb[0] || !rgb[2] || !rgb[1])
	{
		free_array(rgb);
		free(color);
		cub_error("Error! RGB: XXX, XXX, XXX\n", cub, FD_TEX);
	}
	red = ft_strtrim(rgb[0], " ");
	green = ft_strtrim(rgb[1], " ");
	blue = ft_strtrim(rgb[2], " ");
	colors_check(cub, red, green, blue);
	free_array(rgb);
	free(color);
	if ((cub->r < 0 || cub->r > 255) || (cub->g < 0 || cub->g > 255)
	|| (cub->b < 0 || cub->b > 255))
		cub_error("Error! RGB range: 0 - 255\n", cub, FD_TEX);
	return (((cub->r & 0x0ff) << 16)
	| ((cub->g & 0x0ff) << 8) | (cub->b & 0x0ff));
}
