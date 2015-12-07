if (0 ||
#if (!defined(_CFE_) && !defined(_CFEZ_)) || defined(CFG_WL)
				(flags & CISH_FLAG_PCIECIS) ||
#endif /* (!_CFE_ && !_CFEZ_) || CFG_WL */
				CHIPID(oi->sih->chip) == BCM4336_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM43362_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM43341_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM43242_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM43243_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM43143_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM4324_CHIP_ID ||
				CHIPID(oi->sih->chip) == BCM4335_CHIP_ID ||
				((CHIPID(oi->sih->chip) == BCM4345_CHIP_ID) &&
				CST4345_CHIPMODE_SDIOD(oi->sih->chipst)) ||
				((BCM4350_CHIP(oi->sih->chip)) &&
				CST4350_CHIPMODE_SDIOD(oi->sih->chipst)))
				ipxotp_write_bit(oi, cc, otpgu_bit_base + OTPGU_NEWCISFORMAT_OFF);
