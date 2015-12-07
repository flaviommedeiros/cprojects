switch (event->direction)
	{
		case GDK_SCROLL_UP:
			mask = (1 << 3);
			break;
		case GDK_SCROLL_DOWN:
			mask = (1 << 4);
			break;
		case GDK_SCROLL_LEFT:
			mask = (1 << 5);
			break;
		case GDK_SCROLL_RIGHT:
			mask = (1 << 6);
			break;
#ifdef GDK_SCROLL_SMOOTH
		case GDK_SCROLL_SMOOTH:
			if (event->delta_y < 0)
				mask = (1 << 3);
			if (event->delta_y > 0)
				mask = (1 << 4);
			if (event->delta_x < 0)
				mask = (1 << 5);
			if (event->delta_x > 0)
				mask = (1 << 6);
			if (!mask)
				return FALSE;
			break;
#endif
		default:
			return FALSE;
	}
