switch(ivideo->nbridge->device) {
#ifdef CONFIG_FB_SIS_300
		case PCI_DEVICE_ID_SI_730:
			ivideo->chip = SIS_730;
			strcpy(ivideo->myid, "SiS 730");
			break;
#endif
#ifdef CONFIG_FB_SIS_315
		case PCI_DEVICE_ID_SI_651:
			/* ivideo->chip is ok */
			strcpy(ivideo->myid, "SiS 651");
			break;
		case PCI_DEVICE_ID_SI_740:
			ivideo->chip = SIS_740;
			strcpy(ivideo->myid, "SiS 740");
			break;
		case PCI_DEVICE_ID_SI_661:
			ivideo->chip = SIS_661;
			strcpy(ivideo->myid, "SiS 661");
			break;
		case PCI_DEVICE_ID_SI_741:
			ivideo->chip = SIS_741;
			strcpy(ivideo->myid, "SiS 741");
			break;
		case PCI_DEVICE_ID_SI_760:
			ivideo->chip = SIS_760;
			strcpy(ivideo->myid, "SiS 760");
			break;
		case PCI_DEVICE_ID_SI_761:
			ivideo->chip = SIS_761;
			strcpy(ivideo->myid, "SiS 761");
			break;
#endif
		default:
			break;
		}
