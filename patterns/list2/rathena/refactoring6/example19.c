if( bl->x >= x0 && bl->x <= x1 && bl->y >= y0 && bl->y <= y1
#ifdef CIRCULAR_AREA
						&& check_distance_bl(center, bl, range)
#endif
						&& bl_list_count < BL_LIST_MAX )
						bl_list[ bl_list_count++ ] = bl;
