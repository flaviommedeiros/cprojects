static struct i2c_registry msm9615_i2c_devices[] __initdata = {
#ifdef CONFIG_WCD9310_CODEC
	{
		I2C_SURF | I2C_FFA | I2C_FLUID,
		MSM_9615_GSBI5_QUP_I2C_BUS_ID,
		wcd9xxx_device_info,
		ARRAY_SIZE(wcd9xxx_device_info),
	},
#endif
};
