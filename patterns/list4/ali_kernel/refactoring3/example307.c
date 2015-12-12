switch (wd->sta.encryMode)
	        {
            case ZM_WEP64:
            case ZM_WEP128:
            case ZM_WEP256:
                header[4] |= 0x4000;
                header[hlen] = 0x0;   //IV
                header[hlen+1] = 0x0; //IV
                hlen += 2;
                icvLen = 4;
                macCtrl |= 0x40;
                break;

            case ZM_TKIP:
            {
                wd->sta.iv16++;
                if ( wd->sta.iv16 == 0 )
                {
                    wd->sta.iv32++;
                }

                b1 = (u8_t) (wd->sta.iv16 >> 8);
                b2 = (b1 | 0x20) & 0x7f;
                header[hlen] = ((u16_t)b2 << 8) + b1;
                b1 = (u8_t) wd->sta.iv16;
                b2 = 0x20;
                header[hlen+1] = ((u16_t)b2 << 8) + b1;
                header[hlen+2] = (u16_t) wd->sta.iv32;
                header[hlen+3] = (u16_t) (wd->sta.iv32 >> 16);

                //macCtrl |= 0x80;
                macCtrl |= 0x40;
                icvLen = 4;

                /* set hardware MIC */
                if ( (!(seq & 0xf))&&(!(flag & 0x4)) )
                {
                    macCtrl |= 0x100;
                    plusLen += 8;
                    *micLen = 8;
                }

                header[4] |= 0x4000;
                hlen += 4;
            }/* end of PSEUDO TKIP */
                break;

            case ZM_AES:
            {
                wd->sta.iv16++;
                if ( wd->sta.iv16 == 0 )
                {
                    wd->sta.iv32++;
                }

                b1 = (u8_t) wd->sta.iv16;
                b2 = (u8_t) (wd->sta.iv16 >> 8);
                header[hlen] = ((u16_t)b2 << 8) + b1;
                header[hlen+1] = 0x2000;
                header[hlen+2] = (u16_t) (wd->sta.iv32);
                header[hlen+3] = (u16_t) (wd->sta.iv32 >> 16);
                macCtrl |= 0xc0;
                icvLen = 8;  /* MIC */
                header[4] |= 0x4000;
                hlen += 4;
            }/* end of PSEUDO AES */
                    break;

              #ifdef ZM_ENABLE_CENC
              case ZM_CENC:
                    /* Accumlate the PN sequence */
                    wd->sta.txiv[0] += 2;

                    if (wd->sta.txiv[0] == 0 || wd->sta.txiv[0] == 1)
                    {
                        wd->sta.txiv[1]++;
                    }

                    if (wd->sta.txiv[1] == 0)
                    {
                        wd->sta.txiv[2]++;
                    }

                    if (wd->sta.txiv[2] == 0)
                    {
                        wd->sta.txiv[3]++;
                    }

                    if (wd->sta.txiv[3] == 0)
                    {
                        wd->sta.txiv[0] = 0;
                        wd->sta.txiv[1] = 0;
                        wd->sta.txiv[2] = 0;
                    }

                    header[hlen] = 0;
                    header[hlen+1] = (u16_t) wd->sta.txiv[0];
                    header[hlen+2] = (u16_t) (wd->sta.txiv[0] >> 16);
                    header[hlen+3] = (u16_t) wd->sta.txiv[1];
                    header[hlen+4] = (u16_t) (wd->sta.txiv[1] >> 16);
                    header[hlen+5] = (u16_t) wd->sta.txiv[2];
                    header[hlen+6] = (u16_t) (wd->sta.txiv[2] >> 16);
                    header[hlen+7] = (u16_t) wd->sta.txiv[3];
                    header[hlen+8] = (u16_t) (wd->sta.txiv[3] >> 16);

                    macCtrl |= 0x80;
                    icvLen = 16;  /* MIC */

                    header[4] |= 0x4000;
                    hlen += 9;
				break;
		    #endif //ZM_ENABLE_CENC
			}
