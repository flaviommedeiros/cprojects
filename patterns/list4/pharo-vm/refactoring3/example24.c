switch (BITS (5, 7)) {
	case 0:		/* cfmvrdl */
		/* Move lower half of a DF stored in a DSP reg into an Arm reg.  */
		printfdbg ("cfmvrdl\n");
		printfdbg ("\tlower half=0x%x\n", DSPregs[SRC1_REG].lower.i);
		printfdbg ("\tentire thing=%g\n", mv_getRegDouble (SRC1_REG));

		*value = (ARMword) DSPregs[SRC1_REG].lower.i;
		break;

	case 1:		/* cfmvrdh */
		/* Move upper half of a DF stored in a DSP reg into an Arm reg.  */
		printfdbg ("cfmvrdh\n");
		printfdbg ("\tupper half=0x%x\n", DSPregs[SRC1_REG].upper.i);
		printfdbg ("\tentire thing=%g\n", mv_getRegDouble (SRC1_REG));

		*value = (ARMword) DSPregs[SRC1_REG].upper.i;
		break;

	case 2:		/* cfmvrs */
		/* Move SF from upper half of a DSP register to an Arm register.  */
		*value = (ARMword) DSPregs[SRC1_REG].upper.i;
		printfdbg ("cfmvrs = mvf%d <-- %f\n",
			   SRC1_REG, DSPregs[SRC1_REG].upper.f);
		break;

#ifdef doesnt_work
	case 4:		/* cfcmps */
		{
			float a, b;
			int n, z, c, v;

			a = DSPregs[SRC1_REG].upper.f;
			b = DSPregs[SRC2_REG].upper.f;

			printfdbg ("cfcmps\n");
			printfdbg ("\tcomparing %f and %f\n", a, b);

			z = a == b;	/* zero */
			n = a != b;	/* negative */
			v = a > b;	/* overflow */
			c = 0;	/* carry */
			*value = (n << 31) | (z << 30) | (c << 29) | (v <<
								      28);
			break;
		}

	case 5:		/* cfcmpd */
		{
			double a, b;
			int n, z, c, v;

			a = mv_getRegDouble (SRC1_REG);
			b = mv_getRegDouble (SRC2_REG);

			printfdbg ("cfcmpd\n");
			printfdbg ("\tcomparing %g and %g\n", a, b);

			z = a == b;	/* zero */
			n = a != b;	/* negative */
			v = a > b;	/* overflow */
			c = 0;	/* carry */
			*value = (n << 31) | (z << 30) | (c << 29) | (v <<
								      28);
			break;
		}
#else
	case 4:		/* cfcmps */
		{
			float a, b;
			int n, z, c, v;

			a = DSPregs[SRC1_REG].upper.f;
			b = DSPregs[SRC2_REG].upper.f;

			printfdbg ("cfcmps\n");
			printfdbg ("\tcomparing %f and %f\n", a, b);

			z = a == b;	/* zero */
			n = a < b;	/* negative */
			c = a > b;	/* carry */
			v = 0;	/* fixme */
			printfdbg ("\tz = %d, n = %d\n", z, n);
			*value = (n << 31) | (z << 30) | (c << 29) | (v <<
								      28);
			break;
		}

	case 5:		/* cfcmpd */
		{
			double a, b;
			int n, z, c, v;

			a = mv_getRegDouble (SRC1_REG);
			b = mv_getRegDouble (SRC2_REG);

			printfdbg ("cfcmpd\n");
			printfdbg ("\tcomparing %g and %g\n", a, b);

			z = a == b;	/* zero */
			n = a < b;	/* negative */
			c = a > b;	/* carry */
			v = 0;	/* fixme */
			*value = (n << 31) | (z << 30) | (c << 29) | (v <<
								      28);
			break;
		}
#endif
	default:
		fprintf (stderr, "unknown opcode in DSPMRC4 0x%x\n", instr);
		cirrus_not_implemented ("unknown");
		break;
	}
