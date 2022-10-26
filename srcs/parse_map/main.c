#include "cub3d.h"
#include "libft.h"
#include "parse_map.h"

static void	free_all(t_map_info *map_info)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		ft_safe_free(map_info->texture_path[i]);
		++i;
	}
	ft_safe_free_two_dimentions_arr(map_info->map);
}

int	main(int argc, char *argv[])
{
	t_map_info	map_info;

	init_map_info(&map_info, argc, argv[1]);
	free_all(&map_info);
	return (0);
}
