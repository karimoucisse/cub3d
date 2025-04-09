// int wall_top_pixel = (HEIGHT / 2) - (game->raycast_info.wall_height / 2)
// wall_top_pixel < 0 ? 0 : wall_top_pixel

// int wall_bottom_pixel = (HEIGHT / 2) + (game->raycast_info.wall_height / 2)
// wall_bottom_pixel > HEIGHT ? HEIGHT : HEIGHT

// y = 0;
// while(y < wall_top_pixel) ceilling color

// y = wall_top_pixel;
// while(y < wall_bottom_pixel) render texture wall

// y = wall_bottom_pixel;
// while(y < HEIGHT) floor color



// if(wall is hit vertical)
// 		texture_offset_x = (int)game->raycast_info.wall_hity % TILE
// else
//		texture_offset_x = (int)game->raycast_info.wall_hitx % TILE

// while (y < wall_bottom_pixel)
// {
	// int distanceFromTop = y + (game->raycast_info.wall_height / 2) - (HEIGHT / 2);
	// texture_offset_y = distanceFromTop * ((double)texture.height / game->raycast_info.wall_height);
	// color = texture.pixels[(texture.width * texture_offset_y) + texture_offset_x];
// }
