if (display_point((int)x, (int)y, i, 0)    /* XXX VS60 might switch color */
        /* VT11, per maintenance spec, has threshold 6 for CHAR, 4 for others */
        /* but the classic Lunar Lander uses 3 for its menu and thrust bar! */
        /* I seem to recall that both thresholds were 4 for the VS60 (VR48). */
#if 0
        && (i >= (DISPLAY_INT_MAX-1)    /* (using i applies depth cueing) */
            || (graphic_mode != CHAR && i >= (DISPLAY_INT_MAX-3)))
#else
        /* The following imposes thresholds of 3 for all graphic objects. */
        && (i >= (DISPLAY_INT_MAX-4))   /* (using i applies depth cueing) */
#endif
        && !lp_suppress) {
        lp0_hit = 1;
        if (lp0_intr_ena)
            lphit_irq = 1;              /* will lead to an interrupt */
        /*
         * Save LP hit coordinates so CPU can look at them; the virtual position
         * registers cannot be reported on LP interrupt, since they track the
         * (pre-clipping) end of the vector that was being drawn.
         */
        lp_xpos = x;
        if (menu)
            lp_xpos -= MENU_OFFSET;
        lp_ypos = y;
        lp_zpos = z;
        if (lp_intensify)               /* [technically shouldn't exceed max] */
            display_point((int)x, (int)y, DISPLAY_INT_MAX, 0);
                /* XXX  appropriate for VT11; what about VS60?  chars? */
    }
