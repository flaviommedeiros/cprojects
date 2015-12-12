#ifndef DISABLE_CUSTOM_TITLE
if (deadbeef->conf_get_int ("gtkui.location_set_custom_title", 0)) {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sct), TRUE);
        gtk_widget_set_sensitive (ct, TRUE);
    }
    else
#endif
    {
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (sct), FALSE);
        gtk_widget_set_sensitive (ct, FALSE);
    }
