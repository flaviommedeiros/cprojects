if (0
#ifndef DROPBEAR_ECC_256
				|| i == DROPBEAR_SIGNKEY_ECDSA_NISTP256
#endif
#ifndef DROPBEAR_ECC_384
				|| i == DROPBEAR_SIGNKEY_ECDSA_NISTP384
#endif
#ifndef DROPBEAR_ECC_521
				|| i == DROPBEAR_SIGNKEY_ECDSA_NISTP521
#endif
				) {
				TRACE(("attempt to use ecdsa type %d not compiled in", i))
				return DROPBEAR_SIGNKEY_NONE;
			
