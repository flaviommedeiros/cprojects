switch (ring) {
#if defined (USE_PCI_INTB) || defined(USE_PCI_INTC) || defined(USE_PCI_INTD)
#ifdef USE_PCI_INTB
		case 1:
#endif
#ifdef USE_PCI_INTC
		case 2:
#endif
#ifdef USE_PCI_INTD
		case 3:
#endif
			writel(INTRN_MASK_RX_EN, cp->regs +
			       REG_PLUS_INTRN_MASK(ring));
			break;
#endif
		default:
			break;
		}
