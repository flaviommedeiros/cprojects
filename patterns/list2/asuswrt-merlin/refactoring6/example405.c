if (fast && transfersize
				    && !(len % transfersize)
				    && (len >= transfersize)
#ifdef FAST32
				    && !(transfersize % 4)
#endif
				    ) {
					DPRINTK (DEBUG_FAST,
						 "scsi%d : FAST transfer, underflow = %d, transfersize = %d\n"
						 "         len = %d, data = %08x\n",
						 hostno, SCint->underflow,
						 SCint->transfersize, len,
						 data);

			/* SJT: Start. Fast Write */
#ifdef SEAGATE_USE_ASM
					__asm__ ("cld\n\t"
#ifdef FAST32
						 "shr $2, %%ecx\n\t"
						 "1:\t"
						 "lodsl\n\t"
						 "movl %%eax, (%%edi)\n\t"
#else
						 "1:\t"
						 "lodsb\n\t"
						 "movb %%al, (%%edi)\n\t"
#endif
						 "loop 1b;"
				      /* output */ :
				      /* input */ :"D" (st0x_dr),
						 "S"
						 (data),
						 "c" (SCint->transfersize)
/* clobbered */
				      :	 "eax", "ecx",
						 "esi");
#else				/* SEAGATE_USE_ASM */
					memcpy_toio(st0x_dr, data, transfersize);
#endif				/* SEAGATE_USE_ASM */
/* SJT: End */
					len -= transfersize;
					data += transfersize;
					DPRINTK (DEBUG_FAST, "scsi%d : FAST transfer complete len = %d data = %08x\n", hostno, len, data);
				} else {
					/*
					 *    We loop as long as we are in a 
					 *    data out phase, there is data to
					 *    send, and BSY is still active.
					 */

/* SJT: Start. Slow Write. */
#ifdef SEAGATE_USE_ASM

					int __dummy_1, __dummy_2;

/*
 *      We loop as long as we are in a data out phase, there is data to send, 
 *      and BSY is still active.
 */
/* Local variables : len = ecx , data = esi, 
                     st0x_cr_sr = ebx, st0x_dr =  edi
*/
					__asm__ (
							/* Test for any data here at all. */
							"orl %%ecx, %%ecx\n\t"
							"jz 2f\n\t" "cld\n\t"
/*                    "movl st0x_cr_sr, %%ebx\n\t"  */
/*                    "movl st0x_dr, %%edi\n\t"  */
							"1:\t"
							"movb (%%ebx), %%al\n\t"
							/* Test for BSY */
							"test $1, %%al\n\t"
							"jz 2f\n\t"
							/* Test for data out phase - STATUS & REQ_MASK should be 
							   REQ_DATAOUT, which is 0. */
							"test $0xe, %%al\n\t"
							"jnz 2f\n\t"
							/* Test for REQ */
							"test $0x10, %%al\n\t"
							"jz 1b\n\t"
							"lodsb\n\t"
							"movb %%al, (%%edi)\n\t"
							"loop 1b\n\t" "2:\n"
				      /* output */ :"=S" (data), "=c" (len),
							"=b"
							(__dummy_1),
							"=D" (__dummy_2)
/* input */
				      :		"0" (data), "1" (len),
							"2" (st0x_cr_sr),
							"3" (st0x_dr)
/* clobbered */
				      :		"eax");
#else				/* SEAGATE_USE_ASM */
					while (len) {
						unsigned char stat;

						stat = STATUS;
						if (!(stat & STAT_BSY)
						    || ((stat & REQ_MASK) !=
							REQ_DATAOUT))
							break;
						if (stat & STAT_REQ) {
							WRITE_DATA (*data++);
							--len;
						}
					}
#endif				/* SEAGATE_USE_ASM */
/* SJT: End. */
				}
