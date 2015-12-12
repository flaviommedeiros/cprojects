switch (bi->board) {
	case CHBT_BOARD_8000:
	case CHBT_BOARD_N110:
	case CHBT_BOARD_N210:
	case CHBT_BOARD_CHT210:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x800);
		break;
	case CHBT_BOARD_CHT110:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x1800);

		/* TBD XXX Might not need.  This fixes a problem
		 *         described in the Intel SR XPAK errata.
		 */
		power_sequence_xpak(adapter);
		break;
#ifdef CONFIG_CHELSIO_T1_1G
	case CHBT_BOARD_CHT204E:
		/* add config space write here */
	case CHBT_BOARD_CHT204:
	case CHBT_BOARD_CHT204V:
	case CHBT_BOARD_CHN204:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x804);
		break;
	case CHBT_BOARD_CHT101:
	case CHBT_BOARD_7500:
		t1_tpi_par(adapter, 0xf);
		t1_tpi_write(adapter, A_ELMER0_GPO, 0x1804);
		break;
#endif
	}
