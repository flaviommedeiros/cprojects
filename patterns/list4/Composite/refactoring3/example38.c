switch (oround) {
		default: /* FE_TONEAREST */
			return (z);
#ifdef FE_TOWARDZERO
		case FE_TOWARDZERO:
			if (x > 0.0 ^ y < 0.0 ^ z < 0.0)
				return (z);
			else
				return (nextafterl(z, 0));
#endif
#ifdef FE_DOWNWARD
		case FE_DOWNWARD:
			if (x > 0.0 ^ y < 0.0)
				return (z);
			else
				return (nextafterl(z, -INFINITY));
#endif
#ifdef FE_UPWARD
		case FE_UPWARD:
			if (x > 0.0 ^ y < 0.0)
				return (nextafterl(z, INFINITY));
			else
				return (z);
#endif
		}
