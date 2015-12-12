coord_t points_frame1[] = {
        { x, y + h-2 },
#if GTK_CHECK_VERSION(3,0,0)
        { x, y + 0.5 },
        { x + 0.5, y },
#else
        { x, y + 1 },
        { x + 1, y },
#endif
        { x + w - h - 1, y },
        { x + w - h + 1, y + 1 },
        { x + w - 3, y + h - 3 },
        { x + w - 0, y + h - 2 },
    };
