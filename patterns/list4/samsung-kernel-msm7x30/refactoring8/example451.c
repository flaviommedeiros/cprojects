static const unsigned short swordfish_keymap[ARRAY_SIZE(swordfish_col_gpios) * ARRAY_SIZE(swordfish_row_gpios)] = {
	[KEYMAP_INDEX(0, 0)] = KEY_5,
	[KEYMAP_INDEX(0, 1)] = KEY_9,
	[KEYMAP_INDEX(0, 2)] = 229,            /* SOFT1 */
	[KEYMAP_INDEX(0, 3)] = KEY_6,
	[KEYMAP_INDEX(0, 4)] = KEY_LEFT,

	[KEYMAP_INDEX(1, 0)] = KEY_0,
	[KEYMAP_INDEX(1, 1)] = KEY_RIGHT,
	[KEYMAP_INDEX(1, 2)] = KEY_1,
	[KEYMAP_INDEX(1, 3)] = 228,           /* KEY_SHARP */
	[KEYMAP_INDEX(1, 4)] = KEY_SEND,

	[KEYMAP_INDEX(2, 0)] = KEY_VOLUMEUP,
	[KEYMAP_INDEX(2, 1)] = KEY_HOME,      /* FA   */
	[KEYMAP_INDEX(2, 2)] = KEY_F8,        /* QCHT */
	[KEYMAP_INDEX(2, 3)] = KEY_F6,        /* R+   */
	[KEYMAP_INDEX(2, 4)] = KEY_F7,        /* R-   */

	[KEYMAP_INDEX(3, 0)] = KEY_UP,
	[KEYMAP_INDEX(3, 1)] = KEY_CLEAR,
	[KEYMAP_INDEX(3, 2)] = KEY_4,
	[KEYMAP_INDEX(3, 3)] = KEY_MUTE,      /* SPKR */
	[KEYMAP_INDEX(3, 4)] = KEY_2,

	[KEYMAP_INDEX(4, 0)] = 230,           /* SOFT2 */
	[KEYMAP_INDEX(4, 1)] = 232,           /* KEY_CENTER */
	[KEYMAP_INDEX(4, 2)] = KEY_DOWN,
	[KEYMAP_INDEX(4, 3)] = KEY_BACK,      /* FB */
	[KEYMAP_INDEX(4, 4)] = KEY_8,

	[KEYMAP_INDEX(5, 0)] = KEY_VOLUMEDOWN,
	[KEYMAP_INDEX(5, 1)] = 227,           /* KEY_STAR */
	[KEYMAP_INDEX(5, 2)] = KEY_MAIL,      /* MESG */
	[KEYMAP_INDEX(5, 3)] = KEY_3,
	[KEYMAP_INDEX(5, 4)] = KEY_7,

#if SCAN_FUNCTION_KEYS
	[KEYMAP_INDEX(6, 0)] = KEY_F5,
	[KEYMAP_INDEX(6, 1)] = KEY_F4,
	[KEYMAP_INDEX(6, 2)] = KEY_F3,
	[KEYMAP_INDEX(6, 3)] = KEY_F2,
	[KEYMAP_INDEX(6, 4)] = KEY_F1
#endif
};
