#if GTK_VERSION == 2
if (((rfPointer*) pointer)->cursor != NULL)
#else
	if (G_IS_OBJECT(((rfPointer*) pointer)->cursor))
#endif
	{
		ui = g_new0(RemminaPluginRdpUiObject, 1);
		ui->type = REMMINA_RDP_UI_CURSOR;
		ui->sync = TRUE;	// Also wait for completion
		ui->cursor.pointer = (rfPointer*) pointer;
		ui->cursor.type = REMMINA_RDP_POINTER_FREE;

		rf_queue_ui(rfi->protocol_widget, ui);
	}
