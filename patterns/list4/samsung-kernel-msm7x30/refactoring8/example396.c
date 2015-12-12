static struct msm_gpiomux_config msm8x60_ebi2_configs[] __initdata = {
	{
		.gpio      = 40,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs2,
		},
	},
	{
		.gpio      = 123,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 124,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 125,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 126,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 127,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 128,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 129,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 130,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
	/* ISP VDD_3V3_EN */
	{
		.gpio      = 132,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs4,
		},
	},
#endif
	{
		.gpio      = 133,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs3,
		},
	},
	{
		.gpio      = 135,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 136,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 137,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 138,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 139,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 140,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 141,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 142,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 143,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 144,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 145,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 146,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 147,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 148,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 149,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 150,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 151,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_oe,
		},
	},
	{
		.gpio      = 153,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_adv,
		},
	},
	{
		.gpio      = 157,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_we,
		},
	},
};
