switch (cmd)
	{
#ifndef CONFIG_MESON_TRUSTZONE			
		case EFUSE_ENCRYPT_ENABLE:
			aml_set_reg32_bits( P_EFUSE_CNTL4, CNTL4_ENCRYPT_ENABLE_ON,
			CNTL4_ENCRYPT_ENABLE_BIT, CNTL4_ENCRYPT_ENABLE_SIZE);
			break;

		case EFUSE_ENCRYPT_DISABLE:
			aml_set_reg32_bits( P_EFUSE_CNTL4, CNTL4_ENCRYPT_ENABLE_OFF,
			CNTL4_ENCRYPT_ENABLE_BIT, CNTL4_ENCRYPT_ENABLE_SIZE);
			break;

		case EFUSE_ENCRYPT_RESET:
			aml_set_reg32_bits( P_EFUSE_CNTL4, CNTL4_ENCRYPT_RESET_ON,
			CNTL4_ENCRYPT_RESET_BIT, CNTL4_ENCRYPT_RESET_SIZE);
			break;
#endif
		case EFUSE_INFO_GET:
			{
				efuseinfo_item_t *info = (efuseinfo_item_t*)arg;
				if(efuse_getinfo_byID(info->id, info) < 0)
					return  -EFAULT;
			}
			break;

		default:
			return -ENOTTY;
	}
