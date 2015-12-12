#ifdef CONFIG_ISA
if (!client) { /* ISA device */
		int res;
		mutex_lock(&data->lock);
		outb_p(reg, data->isa_addr + LM78_ADDR_REG_OFFSET);
		res = inb_p(data->isa_addr + LM78_DATA_REG_OFFSET);
		mutex_unlock(&data->lock);
		return res;
	} else
#endif
		return i2c_smbus_read_byte_data(client, reg);
