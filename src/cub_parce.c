/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parce.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwinfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 17:05:41 by vwinfred          #+#    #+#             */
/*   Updated: 2021/03/05 17:05:42 by vwinfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void					make_map_array(t_cub *cub, char *line)
{
	static int			i = 0;

	cub->map[i] = line;
	i++;
}

void					check_valid_line(char *line, t_cub *cub)
{
	if ((line[0] == 'N' && line[1] == 'O')
	|| (line[0] == 'S' && line[1] == 'O')
	|| (line[0] == 'W' && line[1] == 'E')
	|| (line[0] == 'E' && line[1] == 'A')
	|| (line[0] == 'S' && line[1] != 'O')
	|| (line[0] == 'R') || (line[0] == 'F') || (line[0] == 'C')
	|| (line[0] == '1' || line[0] == ' ') || (line[0] == 0))
		return ;
	else
		cub_error("Error! Not valide symbol in map.cub.\n", cub, FD_TEX);
}

void					check_line(char *line, t_cub *cub)
{
	if (line[0] == 'N' && line[1] == 'O')
		parce_no(line, cub);
	else if (line[0] == 'S' && line[1] == 'O' && cub->flags.tex_so == 0)
		parce_so(line, cub);
	else if (line[0] == 'W' && line[1] == 'E' && cub->flags.tex_we == 0)
		parce_we(line, cub);
	else if (line[0] == 'E' && line[1] == 'A' && cub->flags.tex_ea == 0)
		parce_ea(line, cub);
	else if (line[0] == 'S' && line[1] != 'O' && cub->flags.tex_s == 0)
		parce_s(line, cub);
	else if (line[0] == 'R')
		parce_r(line, cub);
	else if (line[0] == 'F')
		parce_floor_color(line, cub);
	else if (line[0] == 'C')
		parce_ceiling_color(line, cub);
}

void					general_parce(t_cub *cub)
{
	char				*line;

	while (get_next_line(cub->fd, &line) == 1)
	{
		check_valid_line(line, cub);
		if (line[0] == '0')
			cub_error("Error! Not valide symbol in map.cub.\n", cub, FD_TEX);
		check_line(line, cub);
		if (line[0] == '\0' && cub->flags.parce_map_start == 1)
			cub_error("Error! Not valide symbol in map.cub.\n", cub, FD_TEX);
		if ((line[0] == '1' && !(tex_keys(cub) == 1)))
			cub_error("Error! Not valide symbol in map.cub.\n", cub, FD_TEX);
		if ((line[0] == '1' || line[0] == ' ') && tex_keys(cub) == 1)
			parce_map(cub, line);
		else
			free(line);
	}
	free(line);
	if (cub->flags.parce_map_start == 0)
		cub_error("Error! Where map?\n", cub, FD_TEX);
	close(cub->fd);
}
