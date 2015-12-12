switch (chip->hardware) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C924:
		/* opti 929 mode (?), OPL3 clock output, audio enable */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(4), 0xf0, 0xfc);
		/* enable wave audio */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(6), 0x02, 0x02);

	case OPTi9XX_HW_82C925:
		/* enable WSS mode */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(1), 0x80, 0x80);
		/* OPL3 FM synthesis */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(2), 0x00, 0x20);
		/* disable Sound Blaster IRQ and DMA */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(3), 0xf0, 0xff);
#ifdef CS4231
		/* cs4231/4248 fix enabled */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(5), 0x02, 0x02);
#else
		/* cs4231/4248 fix disabled */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(5), 0x00, 0x02);
#endif	/* CS4231 */
		break;

	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(1), 0x80, 0x80);
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(2), 0x00, 0x20);
		/*
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(3), 0xa2, 0xae);
		*/
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(4), 0x00, 0x0c);
#ifdef CS4231
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(5), 0x02, 0x02);
#else
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(5), 0x00, 0x02);
#endif	/* CS4231 */
		break;

#else	/* OPTi93X */
	case OPTi9XX_HW_82C931:
		/* disable 3D sound (set GPIO1 as output, low) */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(20), 0x04, 0x0c);
	case OPTi9XX_HW_82C933: /* FALL THROUGH */
		/*
		 * The BTC 1817DW has QS1000 wavetable which is connected
		 * to the serial digital input of the OPTI931.
		 */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(21), 0x82, 0xff);
		/* 
		 * This bit sets OPTI931 to automaticaly select FM
		 * or digital input signal.
		 */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(26), 0x01, 0x01);
	case OPTi9XX_HW_82C930: /* FALL THROUGH */
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(6), 0x02, 0x03);
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(3), 0x00, 0xff);
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(4), 0x10 |
			(chip->hardware == OPTi9XX_HW_82C930 ? 0x00 : 0x04),
			0x34);
		snd_opti9xx_write_mask(chip, OPTi9XX_MC_REG(5), 0x20, 0xbf);
		break;
#endif	/* OPTi93X */

	default:
		snd_printk(KERN_ERR "chip %d not supported\n", chip->hardware);
		return -EINVAL;
	}
