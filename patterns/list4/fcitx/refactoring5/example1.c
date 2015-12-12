#ifdef HAVE_XINERAMA
if (x11priv->bUseXinerama) {
            x = xinerama_screeninfo[i].x_org;
            y = xinerama_screeninfo[i].y_org;
            w = xinerama_screeninfo[i].width;
            h = xinerama_screeninfo[i].height;
        } else
#endif // HAVE_XINERAMA
        {
            x = 0;
            y = 0;
            w = WidthOfScreen(ScreenOfDisplay(x11priv->dpy, i));
            h = HeightOfScreen(ScreenOfDisplay(x11priv->dpy, i));
        }
