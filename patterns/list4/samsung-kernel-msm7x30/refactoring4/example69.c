#ifdef SUPPORT_MAGIC_GATE
if ((chip->mspro_formatter_enable) &&
			(chip->lun2card[lun] & MS_CARD))
#else
	if (chip->mspro_formatter_enable)
#endif
	{
		if (!card || (card == MS_CARD)) {
			pro_formatter_flag = 1;
		}
	}
