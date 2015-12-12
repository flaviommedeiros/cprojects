#ifndef NO_SHARED_MEMORY
if (data->use_mitshm) {
        for (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            if (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                /* Clipped? */
                continue;
            }
            if (x < 0)
            {
                x += w;
                w += rects[i].x;
            }
            if (y < 0)
            {
                y += h;
                h += rects[i].y;
            }
            if (x + w > window->w)
                w = window->w - x;
            if (y + h > window->h)
                h = window->h - y;

            XShmPutImage(display, data->xwindow, data->gc, data->ximage,
                x, y, x, y, w, h, False);
        }
    }
    else
#endif /* !NO_SHARED_MEMORY */
    {
        for (i = 0; i < numrects; ++i) {
            x = rects[i].x;
            y = rects[i].y;
            w = rects[i].w;
            h = rects[i].h;

            if (w <= 0 || h <= 0 || (x + w) <= 0 || (y + h) <= 0) {
                /* Clipped? */
                continue;
            }
            if (x < 0)
            {
                x += w;
                w += rects[i].x;
            }
            if (y < 0)
            {
                y += h;
                h += rects[i].y;
            }
            if (x + w > window->w)
                w = window->w - x;
            if (y + h > window->h)
                h = window->h - y;

            XPutImage(display, data->xwindow, data->gc, data->ximage,
                x, y, x, y, w, h);
        }
    }
