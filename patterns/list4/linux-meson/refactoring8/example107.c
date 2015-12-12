struct i2c_msg msg[] = 
	{
		{
			.addr = this_client->addr,
			.flags = 0,
			.len = length,
			.buf = txData,
#ifdef STK_ROCKCHIP_PLATFORM				
			.scl_rate = scl_clk_rate,			
#endif				
		},
	};
