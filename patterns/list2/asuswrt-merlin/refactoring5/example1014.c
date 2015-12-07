#ifdef MPC5200_BUG_435_WORKAROUND
if (bus->number != hose->bus_offset) {
		switch (len) {
			case 1:
				out_8(((u8 __iomem *)hose->cfg_data) +
					(offset & 3), val);
				break;
			case 2:
				out_le16(((u16 __iomem *)hose->cfg_data) +
					((offset>>1) & 1), val);
				break;

			default:
				out_le16((u16 __iomem *)hose->cfg_data,
					(u16)val);
				out_le16(((u16 __iomem *)hose->cfg_data) + 1,
					(u16)(val>>16));
				break;
		}
	}
	else
#endif
	{
		if (len != 4) {
			value = in_le32(hose->cfg_data);

			offset = (offset & 0x3) << 3;
			mask = (0xffffffff >> (32 - (len << 3)));
			mask <<= offset;

			value &= ~mask;
			val = value | ((val << offset) & mask);
		}

		out_le32(hose->cfg_data, val);
	}
