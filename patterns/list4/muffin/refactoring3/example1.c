switch (m)
    {
    case NotifyNormal:
      mode = "NotifyNormal";
      break;
    case NotifyGrab:
      mode = "NotifyGrab";
      break;
    case NotifyUngrab:
      mode = "NotifyUngrab";
      break;
      /* not sure any X implementations are missing this, but
       * it seems to be absent from some docs.
       */
#ifdef NotifyWhileGrabbed
    case NotifyWhileGrabbed:
      mode = "NotifyWhileGrabbed";
      break;
#endif
    }
