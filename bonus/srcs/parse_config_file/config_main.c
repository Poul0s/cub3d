/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edbernar <edbernar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:44:30 by edbernar          #+#    #+#             */
/*   Updated: 2024/04/10 00:41:57 by edbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_not_digit(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (1);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	*return_good_int(t_settings *settings, char *line)
{
	if (!ft_strcmp("width", line))
		return (&settings->width);
	else if (!ft_strcmp("height", line))
		return (&settings->height);
	else if (!ft_strcmp("quality", line))
		return (&settings->quality);
	else if (!ft_strcmp("antialiasing", line))
		return (&settings->antialiasing);
	else if (!ft_strcmp("show_minimap", line))
		return (&settings->show_minimap);
	else if (!ft_strcmp("minimap_pos_x", line))
		return (&settings->minimap_pos_x);
	else if (!ft_strcmp("minimap_pos_y", line))
		return (&settings->minimap_pos_y);
	else if (!ft_strcmp("wall_size_mini_map", line))
		return (&settings->wall_size_mini_map);
	else if (!ft_strcmp("fov", line))
		return (&settings->fov);
	else if (!ft_strcmp("show_fps", line))
		return (&settings->show_fps);
	return (NULL);
}

void	*error_config(char *msg, void *ptr)
{
	write(2, "\033[1;31m[ERROR]\033[0m ", 20);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(ptr);
	return (NULL);
}

static t_settings	*parse_config(char *path, t_settings *settings)
{
	int			fd;
	char		*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_config("Can't open config file", NULL));
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) < 2)
		{
			free(line);
			continue ;
		}
		line[ft_strlen(line) - 1] = 0;
		if (!ft_strchr(line, '=') || is_not_digit(ft_strchr(line, '=') + 1))
		{
			free(line);
			close(fd);
			return (error_config("Error in config file", settings));
		}
		ft_strchr(line, '=')[0] = 0;
		int *a = return_good_int(settings, line);
		if (!a)
		{
			free(line);
			close(fd);
			return (error_config("Error in config file", settings));
		}
		line[ft_strlen(line)] = '=';
		*a = ft_atoi(ft_strchr(line, '=') + 1);
		free(line);
	}
	free(line);
	close(fd);
	return (settings);
}

static void	*create_default_config(char *path)
{
	t_settings	*settings;
	int			fd;

	fd = open(path, O_CREAT | O_WRONLY, 0644);
	if (fd < 0)
		return (error_config("Can't create config file", NULL));
	write(fd, "width=1024\
\nheight=768\
\nquality=1\
\nantialiasing=1\
\nshow_minimap=1\
\nminimap_pos_x=10\
\nminimap_pos_y=10\
\nwall_size_mini_map=20\
\nfov=60\
\nshow_fps=1\n", 135);
	close(fd);
	return (path);
}

void	init_settings(t_settings *settings)
{
	settings->width = -1;
	settings->height = -1;
	settings->quality = -1;
	settings->antialiasing = -1;
	settings->show_minimap = -1;
	settings->minimap_pos_x = -1;
	settings->minimap_pos_y = -1;
	settings->wall_size_mini_map = -1;
	settings->fov = -1;
	settings->show_fps = -1;
}

t_settings	*verification_settings(t_settings *settings)
{
	if (settings->width < 0 || settings->height < 0 || settings->quality < 0
		|| settings->antialiasing < 0 || settings->show_minimap < 0
		|| settings->minimap_pos_x < 0 || settings->minimap_pos_y < 0
		|| settings->wall_size_mini_map < 0 || settings->fov < 0
		|| settings->show_fps < 0)
	{
		free(settings);
		return (error_config("Error in config file", NULL));
	}
	return (settings);
}

t_settings	*parse_config_file(char *path)
{
	t_settings	*settings;
	int			fd;
	char		*line;

	if (access(path, F_OK) == -1 && create_default_config(path) == NULL)
		return (error_ptr("Can't read config file", NULL));
	else if (access(path, R_OK))
		return (error_ptr("Can't read config file", NULL));
	settings = malloc(sizeof(t_settings));
	if (!settings)
		return (error_config("Error malloc", NULL));
	init_settings(settings);
	settings = parse_config(path, settings);
	get_next_line(-1);
	if (!settings)
		return (NULL);	
	settings = verification_settings(settings);
	return (settings);
}
