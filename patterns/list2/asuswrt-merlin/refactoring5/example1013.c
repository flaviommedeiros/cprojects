#ifdef MPC5200_BUG_435_WORKAROUND
if (bus->number != hose->bus_offset) {
		switch (len) {
			case 1:
				value = in_8(((u8 __iomem *)hose->cfg_data) + (offset & 3));
				break;
			case 2:
				value = in_le16(((u16 __iomem *)hose->cfg_data) + ((offset>>1) & 1));
				break;

			default:
				value = in_le16((u16 __iomem *)hose->cfg_data) |
					(in_le16(((u16 __iomem *)hose->cfg_data) + 1) << 16);
				break;
		}
	}
	else
#endif
	{
		value = in_le32(hose->cfg_data);

		if (len != 4) {
			value >>= ((offset & 0x3) << 3);
			value &= 0xffffffff >> (32 - (len << 3));
		}
	}
