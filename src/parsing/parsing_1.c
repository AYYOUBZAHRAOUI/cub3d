#include "cub3d.h"

int parse_rgb_colors(t_map *map)
{
    if (!parse_color(map->floor_color, &map->f))
    {
        perror("Error: Invalid floor color");
        return (0);
    }
    if (!parse_color(map->ceiling_color, &map->c))
    {
        perror("Error: Invalid ceiling color");
        return (0);
    }  
    return (1);
}

int parse_color(char *color_str, t_rgb **rgb)
{
    char **values;

    values = ft_split(color_str, ',');
    if (!values || !values[0] || !values[1] || !values[2] || values[3])
    {
        if (values)
            free_split(values);
        return (0);
    }
    *rgb = malloc(sizeof(t_rgb));
    if (!*rgb)
    {
        free_split(values);
        return (0);
    }
    if (check_color(values[0], &((*rgb)->red))
        && check_color(values[1], &((*rgb)->grean))
        && check_color(values[2], &((*rgb)->blue)))
    {
        free_split(values);
        return (1);
    }
    free_split(values);
    free(*rgb);
    return (0);
}

int check_color(char *color_str, int *color)
{
    char *r_trim;
    int color_value;
  
    r_trim = ft_strtrim(color_str, " \t");
    color_value = ft_atoi(r_trim);
    free(r_trim);
    if (!(0 <= color_value && color_value <= 255))
        return (0);
    *color = color_value;
    return (1);
}

void free_split(char **split)
{
    int i = 0;
    
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
