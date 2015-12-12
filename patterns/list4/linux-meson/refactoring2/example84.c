#ifdef CONFIG_W1_SLAVE_DS2408_READBACK
if (w1_reset_resume_command(sl->master))
			goto error;
