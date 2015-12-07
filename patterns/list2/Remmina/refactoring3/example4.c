switch (event->direction)
	{
		case GDK_SCROLL_UP:
			flag = PTR_FLAGS_WHEEL | 0x0078;
			break;

		case GDK_SCROLL_DOWN:
			flag = PTR_FLAGS_WHEEL | PTR_FLAGS_WHEEL_NEGATIVE | 0x0088;
			break;

#ifdef GDK_SCROLL_SMOOTH
		case GDK_SCROLL_SMOOTH:
			if (event->delta_y < 0)
				flag = PTR_FLAGS_WHEEL | 0x0078;
			if (event->delta_y > 0)
				flag = PTR_FLAGS_WHEEL | PTR_FLAGS_WHEEL_NEGATIVE | 0x0088;
			if (!flag)
				return FALSE;
			break;
#endif

		default:
			return FALSE;
	}
