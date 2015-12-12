if (GTK_IS_ENTRY (new_child)
		  || GTK_IS_COMBO (new_child)
		  || GTK_IS_SPIN_BUTTON (new_child)
#ifdef USE_GNOME
		   || GNOME_IS_DATE_EDIT (new_child)
		   || GNOME_IS_FILE_ENTRY (new_child)
		   || GNOME_IS_PIXMAP_ENTRY (new_child)
#endif
		  )
		{
		  expand = FALSE;
		  fill = FALSE;
		}
