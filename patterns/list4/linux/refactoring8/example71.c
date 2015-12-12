static struct dmi_system_id acpi_osi_dmi_table[] __initdata = {
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Fujitsu Siemens",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU SIEMENS"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "ESPRIMO Mobile V5505"),
		},
	},
	{
	/*
	 * There have a NVIF method in MSI GX723 DSDT need call by Nvidia
	 * driver (e.g. nouveau) when user press brightness hotkey.
	 * Currently, nouveau driver didn't do the job and it causes there
	 * have a infinite while loop in DSDT when user press hotkey.
	 * We add MSI GX723's dmi information to this table for workaround
	 * this issue.
	 * Will remove MSI GX723 from the table after nouveau grows support.
	 */
	.callback = dmi_disable_osi_vista,
	.ident = "MSI GX723",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star International"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "GX723"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Sony VGN-NS10J_S",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NS10J_S"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Sony VGN-SR290J",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR290J"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "VGN-NS50B_L",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NS50B_L"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "VGN-SR19XN",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR19XN"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba Satellite L355",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_VERSION, "Satellite L355"),
		},
	},
	{
	.callback = dmi_disable_osi_win7,
	.ident = "ASUS K50IJ",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		     DMI_MATCH(DMI_PRODUCT_NAME, "K50IJ"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba P305D",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "Satellite P305D"),
		},
	},
	{
	.callback = dmi_disable_osi_vista,
	.ident = "Toshiba NB100",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		     DMI_MATCH(DMI_PRODUCT_NAME, "NB100"),
		},
	},

	/*
	 * The wireless hotkey does not work on those machines when
	 * returning true for _OSI("Windows 2012")
	 */
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 7737",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7737"),
		},
	},
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 7537",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 7537"),
		},
	},
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 5437",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 5437"),
		},
	},
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Inspiron 3437",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 3437"),
		},
	},
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Vostro 3446",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3446"),
		},
	},
	{
	.callback = dmi_disable_osi_win8,
	.ident = "Dell Vostro 3546",
	.matches = {
		    DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		    DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3546"),
		},
	},

	/*
	 * BIOS invocation of _OSI(Linux) is almost always a BIOS bug.
	 * Linux ignores it, except for the machines enumerated below.
	 */

	/*
	 * Without this this EEEpc exports a non working WMI interface, with
	 * this it exports a working "good old" eeepc_laptop interface, fixing
	 * both brightness control, and rfkill not working.
	 */
	{
	.callback = dmi_enable_osi_linux,
	.ident = "Asus EEE PC 1015PX",
	.matches = {
		     DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer INC."),
		     DMI_MATCH(DMI_PRODUCT_NAME, "1015PX"),
		},
	},

#ifdef CONFIG_ACPI_REV_OVERRIDE_POSSIBLE
	/*
	 * DELL XPS 13 (2015) switches sound between HDA and I2S
	 * depending on the ACPI _REV callback. If userspace supports
	 * I2S sufficiently (or if you do not care about sound), you
	 * can safely disable this quirk.
	 */
	{
	 .callback = dmi_enable_rev_override,
	 .ident = "DELL XPS 13 (2015)",
	 .matches = {
		      DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
		      DMI_MATCH(DMI_PRODUCT_NAME, "XPS 13 9343"),
		},
	},
#endif
	{}
};
