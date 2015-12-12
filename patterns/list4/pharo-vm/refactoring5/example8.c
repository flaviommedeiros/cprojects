#ifdef HAVE_MMX
if(video->have_mmx)
	{
		switch(switcher)
		{
			case 0x3: 	reca_mmx(s, d, lx2, h);       break;
			case 0x2:	recac_mmx(s, d, lx2, h);      break;
			case 0x1:	rec_mmx(s, d, lx2, h);        break;
			case 0x0:	recc_mmx(s, d, lx2, h);       break;
			case 0x7:   recva(s, d, lx, lx2, h);  break;
			case 0x6:   recvac(s, d, lx, lx2, h); break;
			case 0x5:	recv_mmx(s, d, lx, lx2, h);   break;
			case 0x4:	recvc_mmx(s, d, lx, lx2, h);  break;
			case 0x9:	rech(s, d, lx2, h);       break;
			case 0x8:   rechc(s, d, lx2, h);      break;
		}
	}
	else
#endif
	{
		switch(switcher)
		{
			case 0x3: 	reca(s, d, lx2, h);       break;
			case 0x2:	recac(s, d, lx2, h);      break;
			case 0x1:	rec(s, d, lx2, h);        break;
			case 0x0:	recc(s, d, lx2, h);       break;
			case 0x7:   recva(s, d, lx, lx2, h);  break;
			case 0x6:   recvac(s, d, lx, lx2, h); break;
			case 0x5:	recv(s, d, lx, lx2, h);   break;
			case 0x4:	recvc(s, d, lx, lx2, h);  break;
			case 0x9:	rech(s, d, lx2, h);       break;
			case 0x8:   rechc(s, d, lx2, h);      break;
		}
	}
