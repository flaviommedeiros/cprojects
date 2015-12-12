if (!displaydata->use_xrandr &&
#if SDL_VIDEO_DRIVER_X11_XINERAMA
            /* XVidMode only works on the screen at the origin */
            (!displaydata->use_xinerama ||
             (displaydata->x == 0 && displaydata->y == 0)) &&
#endif
            use_vidmode) {
            displaydata->use_vidmode = use_vidmode;
            if (displaydata->use_xinerama) {
                displaydata->vidmode_screen = 0;
            } else {
                displaydata->vidmode_screen = screen;
            }
            XF86VidModeGetModeInfo(data->display, displaydata->vidmode_screen, &modedata->vm_mode);
        }
