#ifndef CONFIG_RPX8260
if (i == 3) {
			dev->dev_addr[i] = bd->bi_enetaddr[i];
			dev->dev_addr[i] |= (1 << (7 - fip->fc_fccnum));
			*eap++ = dev->dev_addr[i];
		} else
#endif
		{
			*eap++ = dev->dev_addr[i] = bd->bi_enetaddr[i];
		}
