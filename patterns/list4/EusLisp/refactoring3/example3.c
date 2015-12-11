switch (polygonOffsetVersion) {
#ifdef GL_EXT_polygon_offset
	case EXTENSION:
	  glDisable(GL_POLYGON_OFFSET_EXT);
	  break;
#endif
#ifdef GL_VERSION_1_1
	case ONE_DOT_ONE:
          glDisable(GL_POLYGON_OFFSET_FILL);
	  break;
#endif
	case MISSING:
	  /* Oh well. */
	  break;
	}
