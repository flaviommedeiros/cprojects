if (!strcmp (child_name, GladeChildOKButton)
	  || !strcmp (child_name, GladeChildCancelButton)
	  || !strcmp (child_name, GladeChildHelpButton)
	  || !strcmp (child_name, GladeChildApplyButton)
	  || !strcmp (child_name, GladeChildSaveButton)
	  || !strcmp (child_name, GladeChildCloseButton)
	  || !strcmp (child_name, GladeChildDialogVBox)
	  || !strcmp (child_name, GladeChildDialogActionArea)
	  || !strcmp (child_name, GladeChildComboEntry)
	  || !strcmp (child_name, GladeChildComboList)
	  || !strcmp (child_name, GladeChildFontSelection)
	  || !strcmp (child_name, GladeChildColorSelection)
#ifdef USE_GNOME
	  || !strcmp (child_name, GladeChildGnomeAppDock)
	  || !strcmp (child_name, GladeChildGnomeAppBar)
	  || !strcmp (child_name, GladeChildGnomeDruidVBox)
	  || !strcmp (child_name, GladeChildGnomeEntry)
#endif
	  )
	{
	  return _("The widget is created automatically as part of the parent widget, and it can't be deleted.");
	}
