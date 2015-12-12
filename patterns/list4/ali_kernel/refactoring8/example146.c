static struct fb_videomode ami_modedb[] __initdata = {

    /*
     *  AmigaOS Video Modes
     *
     *  If you change these, make sure to update DEFMODE_* as well!
     */

    {
	/* 640x200, 15 kHz, 60 Hz (NTSC) */
	"ntsc", 60, 640, 200, TAG_HIRES, 106, 86, 44, 16, 76, 2,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x400, 15 kHz, 60 Hz interlaced (NTSC) */
	"ntsc-lace", 60, 640, 400, TAG_HIRES, 106, 86, 88, 33, 76, 4,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x256, 15 kHz, 50 Hz (PAL) */
	"pal", 50, 640, 256, TAG_HIRES, 106, 86, 40, 14, 76, 2,
	FB_SYNC_BROADCAST, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x512, 15 kHz, 50 Hz interlaced (PAL) */
	"pal-lace", 50, 640, 512, TAG_HIRES, 106, 86, 80, 29, 76, 4,
	FB_SYNC_BROADCAST, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x480, 29 kHz, 57 Hz */
	"multiscan", 57, 640, 480, TAG_SHRES, 96, 112, 29, 8, 72, 8,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x960, 29 kHz, 57 Hz interlaced */
	"multiscan-lace", 57, 640, 960, TAG_SHRES, 96, 112, 58, 16, 72, 16,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x200, 15 kHz, 72 Hz */
	"euro36", 72, 640, 200, TAG_HIRES, 92, 124, 6, 6, 52, 5,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x400, 15 kHz, 72 Hz interlaced */
	"euro36-lace", 72, 640, 400, TAG_HIRES, 92, 124, 12, 12, 52, 10,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x400, 29 kHz, 68 Hz */
	"euro72", 68, 640, 400, TAG_SHRES, 164, 92, 9, 9, 80, 8,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x800, 29 kHz, 68 Hz interlaced */
	"euro72-lace", 68, 640, 800, TAG_SHRES, 164, 92, 18, 18, 80, 16,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 800x300, 23 kHz, 70 Hz */
	"super72", 70, 800, 300, TAG_SHRES, 212, 140, 10, 11, 80, 7,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 800x600, 23 kHz, 70 Hz interlaced */
	"super72-lace", 70, 800, 600, TAG_SHRES, 212, 140, 20, 22, 80, 14,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x200, 27 kHz, 57 Hz doublescan */
	"dblntsc", 57, 640, 200, TAG_SHRES, 196, 124, 18, 17, 80, 4,
	0, FB_VMODE_DOUBLE | FB_VMODE_YWRAP
    }, {
	/* 640x400, 27 kHz, 57 Hz */
	"dblntsc-ff", 57, 640, 400, TAG_SHRES, 196, 124, 36, 35, 80, 7,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x800, 27 kHz, 57 Hz interlaced */
	"dblntsc-lace", 57, 640, 800, TAG_SHRES, 196, 124, 72, 70, 80, 14,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x256, 27 kHz, 47 Hz doublescan */
	"dblpal", 47, 640, 256, TAG_SHRES, 196, 124, 14, 13, 80, 4,
	0, FB_VMODE_DOUBLE | FB_VMODE_YWRAP
    }, {
	/* 640x512, 27 kHz, 47 Hz */
	"dblpal-ff", 47, 640, 512, TAG_SHRES, 196, 124, 28, 27, 80, 7,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x1024, 27 kHz, 47 Hz interlaced */
	"dblpal-lace", 47, 640, 1024, TAG_SHRES, 196, 124, 56, 54, 80, 14,
	0, FB_VMODE_INTERLACED | FB_VMODE_YWRAP
    },

    /*
     *  VGA Video Modes
     */

    {
	/* 640x480, 31 kHz, 60 Hz (VGA) */
	"vga", 60, 640, 480, TAG_SHRES, 64, 96, 30, 9, 112, 2,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 640x400, 31 kHz, 70 Hz (VGA) */
	"vga70", 70, 640, 400, TAG_SHRES, 64, 96, 35, 12, 112, 2,
	FB_SYNC_VERT_HIGH_ACT | FB_SYNC_COMP_HIGH_ACT, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    },

#if 0

    /*
     *  A2024 video modes
     *  These modes don't work yet because there's no A2024 driver.
     */

    {
	/* 1024x800, 10 Hz */
	"a2024-10", 10, 1024, 800, TAG_HIRES, 0, 0, 0, 0, 0, 0,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }, {
	/* 1024x800, 15 Hz */
	"a2024-15", 15, 1024, 800, TAG_HIRES, 0, 0, 0, 0, 0, 0,
	0, FB_VMODE_NONINTERLACED | FB_VMODE_YWRAP
    }
#endif
};
