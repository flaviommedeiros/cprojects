#ifdef HAVE_XSYNC
if (META_DISPLAY_HAS_XSYNC (display) &&
          event->type == (display->xsync_event_base + XSyncAlarmNotify))
        {
          XSyncAlarmNotifyEvent *aevent = (XSyncAlarmNotifyEvent*) event;

          name = "XSyncAlarmNotify";
          extra =
            g_strdup_printf ("alarm: 0x%lx"
                             " counter_value: %" G_GINT64_FORMAT
                             " alarm_value: %" G_GINT64_FORMAT
                             " time: %u alarm state: %s",
                             aevent->alarm,
                             (gint64) sync_value_to_64 (&aevent->counter_value),
                             (gint64) sync_value_to_64 (&aevent->alarm_value),
                             (unsigned int)aevent->time,
                             alarm_state_to_string (aevent->state));
        }
      else
#endif /* HAVE_XSYNC */
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
