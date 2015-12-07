#ifdef CONFIG_SBC82xx
if (i == 5) {
			/* bd->bi_enetaddr holds the SCC0 address; the FCC
			   devices count up from there */
			dev->dev_addr[i] = bd->bi_enetaddr[i] & ~3;
			dev->dev_addr[i] += 1 + fip->fc_fccnum;
			*eap++ = dev->dev_addr[i];
		}
