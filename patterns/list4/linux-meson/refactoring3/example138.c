switch (id->driver_data) {
#ifdef CONFIG_MFD_WM5102
	case WM5102:
		regmap_config = &wm5102_i2c_regmap;
		break;
#endif
#ifdef CONFIG_MFD_WM5110
	case WM5110:
		regmap_config = &wm5110_i2c_regmap;
		break;
#endif
	default:
		dev_err(&i2c->dev, "Unknown device type %ld\n",
			id->driver_data);
		return -EINVAL;
	}
