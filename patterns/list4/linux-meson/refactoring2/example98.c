#if NOA1ROM
if (!(state->m_DRXK_A1_ROM_CODE)
			&& !(state->m_DRXK_A2_ROM_CODE))
#endif
		{
			status = write16(state, SCU_RAM_GPIO__A, SCU_RAM_GPIO_HW_LOCK_IND_DISABLE);
			if (status < 0)
				goto error;
		}
