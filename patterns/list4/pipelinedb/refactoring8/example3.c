struct lwgeom_backend_definition lwgeom_backends[LWGEOM_NUM_BACKENDS] = {
    { .name = "geos",
      .intersects_fn    = geos_intersects,
      .intersects3d_fn  = intersects3d_dwithin,
      .intersection_fn  = geos_intersection,
      .area_fn          = LWGEOM_area_polygon,
      .distance_fn      = LWGEOM_mindistance2d,
      .distance3d_fn    = LWGEOM_mindistance3d
    },
#if HAVE_SFCGAL
    { .name = "sfcgal",
      .intersects_fn    = sfcgal_intersects,
      .intersects3d_fn  = sfcgal_intersects3D,
      .intersection_fn  = sfcgal_intersection,
      .area_fn          = sfcgal_area,
      .distance_fn      = sfcgal_distance,
      .distance3d_fn    = sfcgal_distance3D
    }
#endif
};
