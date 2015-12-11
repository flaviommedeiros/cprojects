switch (polygonOffsetVersion) {
	case EXTENSION:
#ifdef GL_EXT_polygon_offset
	  glEnable(GL_POLYGON_OFFSET_EXT);
	  break;
#endif
#ifdef GL_VERSION_1_1
	case ONE_DOT_ONE:
          glEnable(GL_POLYGON_OFFSET_FILL);
	  break;
#endif
	case MISSING:
	  /* Oh well. */
	  break;
	}
