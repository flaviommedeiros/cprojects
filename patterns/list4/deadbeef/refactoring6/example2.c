if (GTK_IS_TOOLBAR (parent)
#if GLADE_SUPPORTS_GTK_TREE
      || GTK_IS_TREE (parent)
#endif
      || GTK_IS_LIST (parent))
    {
      gtk_widget_destroy (placeholder);
      return;
    }
