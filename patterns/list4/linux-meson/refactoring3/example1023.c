switch (msi_data->feature & FSL_PIC_IP_MASK) {
	case FSL_PIC_IP_MPIC:
		msir_value = fsl_msi_read(msi_data->msi_regs,
			msir_index * 0x10);
		break;
	case FSL_PIC_IP_IPIC:
		msir_value = fsl_msi_read(msi_data->msi_regs, msir_index * 0x4);
		break;
#ifdef CONFIG_EPAPR_PARAVIRT
	case FSL_PIC_IP_VMPIC: {
		unsigned int ret;
		ret = fh_vmpic_get_msir(virq_to_hw(irq), &msir_value);
		if (ret) {
			pr_err("fsl-msi: fh_vmpic_get_msir() failed for "
			       "irq %u (ret=%u)\n", irq, ret);
			msir_value = 0;
		}
		break;
	}
#endif
	}
