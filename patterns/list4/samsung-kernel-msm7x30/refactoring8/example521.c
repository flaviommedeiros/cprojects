static struct gpio_keys_button mini2440_buttons[] = {
	{
		.gpio		= S3C2410_GPG(0),		/* K1 */
		.code		= KEY_F1,
		.desc		= "Button 1",
		.active_low	= 1,
	},
	{
		.gpio		= S3C2410_GPG(3),		/* K2 */
		.code		= KEY_F2,
		.desc		= "Button 2",
		.active_low	= 1,
	},
	{
		.gpio		= S3C2410_GPG(5),		/* K3 */
		.code		= KEY_F3,
		.desc		= "Button 3",
		.active_low	= 1,
	},
	{
		.gpio		= S3C2410_GPG(6),		/* K4 */
		.code		= KEY_POWER,
		.desc		= "Power",
		.active_low	= 1,
	},
	{
		.gpio		= S3C2410_GPG(7),		/* K5 */
		.code		= KEY_F5,
		.desc		= "Button 5",
		.active_low	= 1,
	},
#if 0
	/* this pin is also known as TCLK1 and seems to already
	 * marked as "in use" somehow in the kernel -- possibly wrongly */
	{
		.gpio		= S3C2410_GPG(11),	/* K6 */
		.code		= KEY_F6,
		.desc		= "Button 6",
		.active_low	= 1,
	},
#endif
};
