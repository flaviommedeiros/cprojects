switch (event->direction)
	{
	case GDK_SCROLL_UP:
		if (opacity > 0)
		{
			remmina_file_set_int(cnnobj->remmina_file, "toolbar_opacity", opacity - 1);
			remmina_connection_holder_update_toolbar_opacity(cnnhld);
			return TRUE;
		}
		break;
	case GDK_SCROLL_DOWN:
		if (opacity < TOOLBAR_OPACITY_LEVEL)
		{
			remmina_file_set_int(cnnobj->remmina_file, "toolbar_opacity", opacity + 1);
			remmina_connection_holder_update_toolbar_opacity(cnnhld);
			return TRUE;
		}
		break;
#ifdef GDK_SCROLL_SMOOTH
	case GDK_SCROLL_SMOOTH:
		if (event->delta_y < 0 && opacity > 0)
		{
			remmina_file_set_int(cnnobj->remmina_file, "toolbar_opacity", opacity - 1);
			remmina_connection_holder_update_toolbar_opacity(cnnhld);
			return TRUE;
		}
		if (event->delta_y > 0 && opacity < TOOLBAR_OPACITY_LEVEL)
		{
			remmina_file_set_int(cnnobj->remmina_file, "toolbar_opacity", opacity + 1);
			remmina_connection_holder_update_toolbar_opacity(cnnhld);
			return TRUE;
		}
		break;
#endif
	default:
		break;
	}
