#ifdef CONFIG_ISA
if (!client) { /* ISA device */
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		outb_p(value, data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		return 0;
	} else
#endif
		return i2c_smbus_write_byte_data(client, reg, value);
