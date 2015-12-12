if (GTK_IS_FIXED (widget->parent)
#if GLADE_SUPPORTS_GTK_PACKER
      || GTK_IS_PACKER (widget->parent)
#endif
      || GTK_IS_LAYOUT (widget->parent))
    {
      gtk_widget_destroy (widget);
      return;
    }
