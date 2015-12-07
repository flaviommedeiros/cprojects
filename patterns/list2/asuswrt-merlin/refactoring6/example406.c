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

/* SJT: Start. Fast Read */
#ifdef SEAGATE_USE_ASM
					__asm__ ("cld\n\t"
#ifdef FAST32
						 "shr $2, %%ecx\n\t"
						 "1:\t"
						 "movl (%%esi), %%eax\n\t"
						 "stosl\n\t"
#else
						 "1:\t"
						 "movb (%%esi), %%al\n\t"
						 "stosb\n\t"
#endif
						 "loop 1b\n\t"
				      /* output */ :
				      /* input */ :"S" (st0x_dr),
						 "D"
						 (data),
						 "c" (SCint->transfersize)
/* clobbered */
				      :	 "eax", "ecx",
						 "edi");
#else				/* SEAGATE_USE_ASM */
					memcpy_fromio(data, st0x_dr, len);
#endif				/* SEAGATE_USE_ASM */
/* SJT: End */
					len -= transfersize;
					data += transfersize;
#if (DEBUG & PHASE_DATAIN)
					printk ("scsi%d: transfered += %d\n", hostno, transfersize);
					transfered += transfersize;
#endif

					DPRINTK (DEBUG_FAST, "scsi%d : FAST transfer complete len = %d data = %08x\n", hostno, len, data);
				} else {

#if (DEBUG & PHASE_DATAIN)
					printk ("scsi%d: transfered += %d\n", hostno, len);
					transfered += len;	/* Assume we'll transfer it all, then
								   subtract what we *didn't* transfer */
#endif

/*
 *	We loop as long as we are in a data in phase, there is room to read,
 *      and BSY is still active
 */

/* SJT: Start. */
#ifdef SEAGATE_USE_ASM

					int __dummy_3, __dummy_4;

/* Dummy clobbering variables for the new gcc-2.95 */

/*
 *      We loop as long as we are in a data in phase, there is room to read, 
 *      and BSY is still active
 */
					/* Local variables : ecx = len, edi = data
					   esi = st0x_cr_sr, ebx = st0x_dr */
					__asm__ (
							/* Test for room to read */
							"orl %%ecx, %%ecx\n\t"
							"jz 2f\n\t" "cld\n\t"
/*                "movl st0x_cr_sr, %%esi\n\t"  */
/*                "movl st0x_dr, %%ebx\n\t"  */
							"1:\t"
							"movb (%%esi), %%al\n\t"
							/* Test for BSY */
							"test $1, %%al\n\t"
							"jz 2f\n\t"
							/* Test for data in phase - STATUS & REQ_MASK should be REQ_DATAIN, 
							   = STAT_IO, which is 4. */
							"movb $0xe, %%ah\n\t"
							"andb %%al, %%ah\n\t"
							"cmpb $0x04, %%ah\n\t"
							"jne 2f\n\t"
							/* Test for REQ */
							"test $0x10, %%al\n\t"
							"jz 1b\n\t"
							"movb (%%ebx), %%al\n\t"
							"stosb\n\t"
							"loop 1b\n\t" "2:\n"
				      /* output */ :"=D" (data), "=c" (len),
							"=S"
							(__dummy_3),
							"=b" (__dummy_4)
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
							REQ_DATAIN))
							break;
						if (stat & STAT_REQ) {
							*data++ = DATA;
							--len;
						}
					}
#endif				/* SEAGATE_USE_ASM */
/* SJT: End. */
#if (DEBUG & PHASE_DATAIN)
					printk ("scsi%d: transfered -= %d\n", hostno, len);
					transfered -= len;	/* Since we assumed all of Len got  *
								   transfered, correct our mistake */
#endif
				}
