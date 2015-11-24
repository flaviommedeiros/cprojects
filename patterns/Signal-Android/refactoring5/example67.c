#ifndef SHA512_BLOCK_CAN_MANAGE_UNALIGNED_DATA
if ((size_t)data%sizeof(c->u.d[0]) != 0)
			while (len >= sizeof(c->u))
				memcpy (p,data,sizeof(c->u)),
				sha512_block_data_order (c,p,1),
				len  -= sizeof(c->u),
				data += sizeof(c->u);
		else
#endif
			sha512_block_data_order (c,data,len/sizeof(c->u)),
			data += len,
			len  %= sizeof(c->u),
			data -= len;
