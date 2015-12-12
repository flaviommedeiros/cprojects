struct lwgeom_backend_definition lwgeom_backends[LWGEOM_NUM_BACKENDS] = {
    { .name = "geos",
      .intersects_fn    = geos_intersects,
      .intersects3d_fn  = intersects3d_dwithin,
      .intersection_fn  = geos_intersection,
      .difference_fn    = geos_difference,
      .union_fn         = geos_geomunion,
      .area_fn          = LWGEOM_area_polygon,
      .distance_fn      = LWGEOM_mindistance2d,
      .distance3d_fn    = LWGEOM_mindistance3d
    },
#if HAVE_SFCGAL
    { .name = "sfcgal",
      .intersects_fn    = sfcgal_intersects,
      .intersects3d_fn  = sfcgal_intersects3D,
      .intersection_fn  = sfcgal_intersection,
      .difference_fn    = sfcgal_difference,
      .union_fn         = sfcgal_union,
      .area_fn          = sfcgal_area,
      .distance_fn      = sfcgal_distance,
      .distance3d_fn    = sfcgal_distance3D
    }
#endif
};
