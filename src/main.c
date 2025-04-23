#include "cub3d.h"

// Simple key hook function
void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

int32_t	main(void)
{
	mlx_t	*mlx;

	// Initialize MLX42
	mlx = mlx_init(640, 480, "Cub3D Test", true);
	if (!mlx)
	{
		printf("Error: Failed to initialize MLX42");
		return (EXIT_FAILURE);
	}

	// Register a key hook
	mlx_key_hook(mlx, &key_hook, mlx);
	
	printf("MLX42 test running. Press ESC to exit.");
	
	// Start the main loop
	mlx_loop(mlx);
	
	// Clean up
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}