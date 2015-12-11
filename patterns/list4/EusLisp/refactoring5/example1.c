#ifdef GL_VERSION_1_1
if (supportsOneDotOne() && !forceExtension) {
    polygonOffsetVersion = ONE_DOT_ONE;
    glPolygonOffset(-2.0, -1.0);
  } else
#endif
  {
#ifdef GL_EXT_polygon_offset
  /* check for the polygon offset extension */
  if (glutExtensionSupported("GL_EXT_polygon_offset")) {
    polygonOffsetVersion = EXTENSION;
    glPolygonOffsetEXT(-0.1, -0.002);
  } else 
#endif
    {
      polygonOffsetVersion = MISSING;
      printf("\ndinoshine: Missing polygon offset.\n");
      printf("           Expect shadow depth aliasing artifacts.\n\n");
    }
  }
