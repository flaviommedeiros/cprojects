switch (type[i]) {
		case ISDN_CTYPE_16_0:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = mem[i];
			cards[j].para[2] = io[i];
			break;

		case ISDN_CTYPE_8_0:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = mem[i];
			break;

#ifdef IO0_IO1
		case ISDN_CTYPE_PNP:
		case ISDN_CTYPE_NICCY:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = io0[i];
			cards[j].para[2] = io1[i];
			break;
		case ISDN_CTYPE_COMPAQ_ISA:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = io0[i];
			cards[j].para[2] = io1[i];
			cards[j].para[3] = io[i];
			break;
#endif
		case ISDN_CTYPE_ELSA:
		case ISDN_CTYPE_HFC_PCI:
			cards[j].para[0] = io[i];
			break;
		case ISDN_CTYPE_16_3:
		case ISDN_CTYPE_TELESPCMCIA:
		case ISDN_CTYPE_A1:
		case ISDN_CTYPE_A1_PCMCIA:
		case ISDN_CTYPE_ELSA_PNP:
		case ISDN_CTYPE_ELSA_PCMCIA:
		case ISDN_CTYPE_IX1MICROR2:
		case ISDN_CTYPE_DIEHLDIVA:
		case ISDN_CTYPE_ASUSCOM:
		case ISDN_CTYPE_TELEINT:
		case ISDN_CTYPE_SEDLBAUER:
		case ISDN_CTYPE_SEDLBAUER_PCMCIA:
		case ISDN_CTYPE_SEDLBAUER_FAX:
		case ISDN_CTYPE_SPORTSTER:
		case ISDN_CTYPE_MIC:
		case ISDN_CTYPE_TELES3C:
		case ISDN_CTYPE_ACERP10:
		case ISDN_CTYPE_S0BOX:
		case ISDN_CTYPE_FRITZPCI:
		case ISDN_CTYPE_HSTSAPHIR:
		case ISDN_CTYPE_GAZEL:
		case ISDN_CTYPE_HFC_SX:
		case ISDN_CTYPE_HFC_SP_PCMCIA:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = io[i];
			break;
		case ISDN_CTYPE_ISURF:
			cards[j].para[0] = irq[i];
			cards[j].para[1] = io[i];
			cards[j].para[2] = mem[i];
			break;
		case ISDN_CTYPE_ELSA_PCI:
		case ISDN_CTYPE_NETJET_S:
		case ISDN_CTYPE_TELESPCI:
		case ISDN_CTYPE_W6692:
		case ISDN_CTYPE_NETJET_U:
			break;
		case ISDN_CTYPE_BKM_A4T:
			break;
		case ISDN_CTYPE_SCT_QUADRO:
			if (irq[i]) {
				cards[j].para[0] = irq[i];
			} else {
				/* QUADRO is a 4 BRI card */
				cards[j++].para[0] = 1;
				/* we need to check if further cards can be added */
				if (j < HISAX_MAX_CARDS) {
					cards[j].typ = ISDN_CTYPE_SCT_QUADRO;
					cards[j].protocol = protocol[i];
					cards[j++].para[0] = 2;
				}
				if (j < HISAX_MAX_CARDS) {
					cards[j].typ = ISDN_CTYPE_SCT_QUADRO;
					cards[j].protocol = protocol[i];
					cards[j++].para[0] = 3;
				}
				if (j < HISAX_MAX_CARDS) {
					cards[j].typ = ISDN_CTYPE_SCT_QUADRO;
					cards[j].protocol = protocol[i];
					cards[j].para[0] = 4;
				}
			}
			break;
		}
