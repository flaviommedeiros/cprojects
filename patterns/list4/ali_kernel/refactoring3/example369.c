switch (cmd) {
	case I2OGETIOPS:
		ret = i2o_cfg_getiops(arg);
		break;

	case I2OHRTGET:
		ret = i2o_cfg_gethrt(arg);
		break;

	case I2OLCTGET:
		ret = i2o_cfg_getlct(arg);
		break;

	case I2OPARMSET:
		ret = i2o_cfg_parms(arg, I2OPARMSET);
		break;

	case I2OPARMGET:
		ret = i2o_cfg_parms(arg, I2OPARMGET);
		break;

	case I2OSWDL:
		ret = i2o_cfg_swdl(arg);
		break;

	case I2OSWUL:
		ret = i2o_cfg_swul(arg);
		break;

	case I2OSWDEL:
		ret = i2o_cfg_swdel(arg);
		break;

	case I2OVALIDATE:
		ret = i2o_cfg_validate(arg);
		break;

	case I2OEVTREG:
		ret = i2o_cfg_evt_reg(arg, fp);
		break;

	case I2OEVTGET:
		ret = i2o_cfg_evt_get(arg, fp);
		break;

#ifdef CONFIG_I2O_EXT_ADAPTEC
	case I2OPASSTHRU:
		ret = i2o_cfg_passthru(arg);
		break;
#endif

	default:
		osm_debug("unknown ioctl called!\n");
		ret = -EINVAL;
	}
