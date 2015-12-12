static const struct fb_videomode mac_modedb[] = {
    {
	/* 512x384, 60Hz, Non-Interlaced (15.67 MHz dot clock) */
	"mac2", 60, 512, 384, 63828, 80, 16, 19, 1, 32, 3,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 640x480, 60 Hz, Non-Interlaced (25.175 MHz dotclock) */
	"mac5", 60, 640, 480, 39722, 32, 32, 33, 10, 96, 2,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 640x480, 67Hz, Non-Interlaced (30.0 MHz dotclock) */
	"mac6", 67, 640, 480, 33334, 80, 80, 39, 3, 64, 3,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 640x870, 75Hz (portrait), Non-Interlaced (57.28 MHz dot clock) */
	"mac7", 75, 640, 870, 17457, 80, 32, 42, 3, 80, 3,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 800x600, 56 Hz, Non-Interlaced (36.00 MHz dotclock) */
	"mac9", 56, 800, 600, 27778, 112, 40, 22, 1, 72, 2,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 800x600, 60 Hz, Non-Interlaced (40.00 MHz dotclock) */
	"mac10", 60, 800, 600, 25000, 72, 56, 23, 1, 128, 4,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 800x600, 72 Hz, Non-Interlaced (50.00 MHz dotclock) */
	"mac11", 72, 800, 600, 20000, 48, 72, 23, 37, 120, 6,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 800x600, 75 Hz, Non-Interlaced (49.50 MHz dotclock) */
	"mac12", 75, 800, 600, 20203, 144, 32, 21, 1, 80, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 832x624, 75Hz, Non-Interlaced (57.6 MHz dotclock) */
	"mac13", 75, 832, 624, 17362, 208, 48, 39, 1, 64, 3,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 1024x768, 60 Hz, Non-Interlaced (65.00 MHz dotclock) */
	"mac14", 60, 1024, 768, 15385, 144, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 1024x768, 72 Hz, Non-Interlaced (75.00 MHz dotclock) */
	"mac15", 72, 1024, 768, 13334, 128, 40, 29, 3, 136, 6,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz dotclock) */
	"mac16", 75, 1024, 768, 12699, 176, 16, 28, 1, 96, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 1024x768, 75 Hz, Non-Interlaced (78.75 MHz dotclock) */
	"mac17", 75, 1024, 768, 12699, 160, 32, 28, 1, 96, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 1152x870, 75 Hz, Non-Interlaced (100.0 MHz dotclock) */
	"mac18", 75, 1152, 870, 10000, 128, 48, 39, 3, 128, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 1280x960, 75 Hz, Non-Interlaced (126.00 MHz dotclock) */
	"mac19", 75, 1280, 960, 7937, 224, 32, 36, 1, 144, 3,
	0, FB_VMODE_NONINTERLACED
    }, {
	/* 1280x1024, 75 Hz, Non-Interlaced (135.00 MHz dotclock) */
	"mac20", 75, 1280, 1024, 7408, 232, 64, 38, 1, 112, 3,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 1152x768, 60 Hz, Titanium PowerBook */
	"mac21", 60, 1152, 768, 15386, 158, 26, 29, 3, 136, 6,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }, {
	/* 1600x1024, 60 Hz, Non-Interlaced (112.27 MHz dotclock) */
	"mac22", 60, 1600, 1024, 8908, 88, 104, 1, 10, 16, 1,
	FB_SYNC_HOR_HIGH_ACT|FB_SYNC_VERT_HIGH_ACT, FB_VMODE_NONINTERLACED
    }

#if 0
    /* Anyone who has timings for these? */
    {
	/* VMODE_512_384_60I: 512x384, 60Hz, Interlaced (NTSC) */
	"mac1", 60, 512, 384, pixclock, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    }, {
	/* VMODE_640_480_50I: 640x480, 50Hz, Interlaced (PAL) */
	"mac3", 50, 640, 480, pixclock, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    }, {
	/* VMODE_640_480_60I: 640x480, 60Hz, Interlaced (NTSC) */
	"mac4", 60, 640, 480, pixclock, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    }, {
	/* VMODE_768_576_50I: 768x576, 50Hz (PAL full frame), Interlaced */
	"mac8", 50, 768, 576, pixclock, left, right, upper, lower, hslen, vslen,
	sync, FB_VMODE_INTERLACED
    },
#endif
};
