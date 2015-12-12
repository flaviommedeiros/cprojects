#ifdef CONFIG_X86
if (addr == 0x73 && (adap->class & I2C_CLASS_HWMON)
	 && i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_BYTE_DATA))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_READ, 0,
				     I2C_SMBUS_BYTE_DATA, &dummy);
	else
#endif
	if (!((addr & ~0x07) == 0x30 || (addr & ~0x0f) == 0x50)
	 && i2c_check_functionality(adap, I2C_FUNC_SMBUS_QUICK))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_WRITE, 0,
				     I2C_SMBUS_QUICK, NULL);
	else if (i2c_check_functionality(adap, I2C_FUNC_SMBUS_READ_BYTE))
		err = i2c_smbus_xfer(adap, addr, 0, I2C_SMBUS_READ, 0,
				     I2C_SMBUS_BYTE, &dummy);
	else {
		dev_warn(&adap->dev, "No suitable probing method supported for address 0x%02X\n",
			 addr);
		err = -EOPNOTSUPP;
	}
