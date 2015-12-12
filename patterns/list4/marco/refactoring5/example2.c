#ifdef HAVE_SHAPE
if (META_DISPLAY_HAS_SHAPE (display) &&
            event->type == (display->shape_event_base + ShapeNotify))
          {
            XShapeEvent *sev = (XShapeEvent*) event;

            name = "ShapeNotify";

            extra =
              g_strdup_printf ("kind: %s "
                               "x: %d y: %d w: %u h: %u "
                               "shaped: %d",
                               sev->kind == ShapeBounding ?
                               "ShapeBounding" :
                               (sev->kind == ShapeClip ?
                               "ShapeClip" : "(unknown)"),
                               sev->x, sev->y, sev->width, sev->height,
                               sev->shaped);
          }
        else
#endif /* HAVE_SHAPE */
        {
          name = "(Unknown event)";
          extra = g_strdup_printf ("type: %d", event->xany.type);
        }
