switch (opcode >> 28) {
		case 0xf:
			/*
			 *  LOAD / STORE DSA relative, don't relocate.
			 */
			relocs = 0;
			break;
		case 0xe:
			/*
			 *  LOAD / STORE absolute.
			 */
			relocs = 1;
			break;
		case 0xc:
			/*
			 *  COPY has TWO arguments.
			 */
			relocs = 2;
			tmp1 = cur[1];
			tmp2 = cur[2];
			if ((tmp1 ^ tmp2) & 3) {
				printf ("%s: ERROR1 IN SCRIPT at %d.\n",
					sym_name(np), (int) (cur-start));
			}
			/*
			 *  If PREFETCH feature not enabled, remove 
			 *  the NO FLUSH bit if present.
			 */
			if ((opcode & SCR_NO_FLUSH) &&
			    !(np->features & FE_PFEN)) {
				opcode = (opcode & ~SCR_NO_FLUSH);
			}
			break;
		case 0x0:
			/*
			 *  MOVE/CHMOV (absolute address)
			 */
			if (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 1;
			break;
		case 0x1:
			/*
			 *  MOVE/CHMOV (table indirect)
			 */
			if (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 0;
			break;
#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
		case 0x2:
			/*
			 *  MOVE/CHMOV in target role (absolute address)
			 */
			opcode &= ~0x20000000;
			if (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 1;
			break;
		case 0x3:
			/*
			 *  MOVE/CHMOV in target role (table indirect)
			 */
			opcode &= ~0x20000000;
			if (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 0;
			break;
#endif
		case 0x8:
			/*
			 *  JUMP / CALL
			 *  don't relocate if relative :-)
			 */
			if (opcode & 0x00800000)
				relocs = 0;
			else if ((opcode & 0xf8400000) == 0x80400000)/*JUMP64*/
				relocs = 2;
			else
				relocs = 1;
			break;
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
			relocs = 1;
			break;
		default:
			relocs = 0;
			break;
		}
