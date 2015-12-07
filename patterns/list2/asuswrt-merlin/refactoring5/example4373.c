#ifndef OPENSSL_SMALL_FOOTPRINT
if (bitrem == inpgap) {
                c->data[byteoff++] |= inp[0] & (0xff >> inpgap);
                inpgap = 8 - inpgap;
                bitoff += inpgap;
                bitrem = 0;     /* bitoff%8 */
                bits -= inpgap;
                inpgap = 0;     /* bits%8 */
                inp++;
                if (bitoff == WHIRLPOOL_BBLOCK) {
                    whirlpool_block(c, c->data, 1);
                    bitoff = 0;
                }
                c->bitoff = bitoff;
                goto reconsider;
            } else
#endif
            if (bits >= 8) {
                b = ((inp[0] << inpgap) | (inp[1] >> (8 - inpgap)));
                b &= 0xff;
                if (bitrem)
                    c->data[byteoff++] |= b >> bitrem;
                else
                    c->data[byteoff++] = b;
                bitoff += 8;
                bits -= 8;
                inp++;
                if (bitoff >= WHIRLPOOL_BBLOCK) {
                    whirlpool_block(c, c->data, 1);
                    byteoff = 0;
                    bitoff %= WHIRLPOOL_BBLOCK;
                }
                if (bitrem)
                    c->data[byteoff] = b << (8 - bitrem);
            } else {            /* remaining less than 8 bits */

                b = (inp[0] << inpgap) & 0xff;
                if (bitrem)
                    c->data[byteoff++] |= b >> bitrem;
                else
                    c->data[byteoff++] = b;
                bitoff += (unsigned int)bits;
                if (bitoff == WHIRLPOOL_BBLOCK) {
                    whirlpool_block(c, c->data, 1);
                    byteoff = 0;
                    bitoff %= WHIRLPOOL_BBLOCK;
                }
                if (bitrem)
                    c->data[byteoff] = b << (8 - bitrem);
                bits = 0;
            }
