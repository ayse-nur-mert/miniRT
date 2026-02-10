#include "../../include/engine.h"
#include "../parser/parser.h"
#include "../minilibx-linux/mlx.h"

int main(int argc, char **argv)
{
    t_world world;
    t_token *tokens;

    // 1. Validate Arguments
    if (argc != 2)
    {
        printf("Usage: %s <scene.rt>\n", argv[0]);
        return (1);
    }
    
    // 2. Initialize World Struct
    // Zero out struct (memset or {0})
    ft_memset(&world, 0, sizeof(t_world));
    world.width = 1280; // Default resolution
    world.height = 720;
    
    // 3. Parse Scene
    tokens = tokenize_file(argv[1]);
    if (!tokens)
    {
        printf("Error\nCould not read file or empty file.\n");
        return (1);
    }
    
    if (!parse_scene(&world, tokens))
    {
        printf("Error\nParsing failed.\n");
        free_tokens(tokens); 
        return (1);
    }
    printf("Scene parsed successfully.\n");
    free_tokens(tokens);

    // 4. Init MLX
    init_mlx_utils(&world);
    
    // 5. Render
    printf("Rendering...\n");
    render_scene(&world);
    printf("Render Complete.\n");
    
    mlx_put_image_to_window(world.mlx, world.win, world.img, 0, 0);
    
    // 6. Loop
    mlx_loop(world.mlx);
    
    return (0);
}


