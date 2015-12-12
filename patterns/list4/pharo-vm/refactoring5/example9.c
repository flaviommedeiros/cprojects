#ifdef HAVE_MMX
if(video->have_mmx)
		{
    		if(spar)
			{
    	   __asm__ __volatile__(
            	"movq       (%2),  %%mm6\n"  /* 4 blockvals */
            	"pxor       %%mm4, %%mm4\n"
            	"punpcklwd  %%mm6, %%mm6\n"
            	"punpcklwd  %%mm6, %%mm6\n"
            	".align 8\n"
            	"1:"
                	"movq       (%1),  %%mm0\n"     /* 8 rindex1 */
                	"movq       %%mm0, %%mm2\n"
                	"punpcklbw  %%mm4, %%mm0\n"
                	"punpckhbw  %%mm4, %%mm2\n"
                	"paddw      %%mm6, %%mm0\n"
                	"paddw      %%mm6, %%mm2\n"

                	"packuswb   %%mm2, %%mm0\n"
                	"movq       %%mm0, (%1)\n"

                	"leal       (%1, %3), %1\n"
            	  "loop       1b\n"
            	  :              /* scr   dest */
            	  : "c" (8),"r" (rfp), "r" (bp), "r" (iincr)
                	);
    		}
    		else 
			{
    	   __asm__ __volatile__(
        		 "pxor    %%mm4, %%mm4\n"

        		 ".align 8\n"
        		 "1:"
        		   "movq       (%2), %%mm0\n"   /* 8 rfp 0 1 2 3 4 5 6 7*/
        		   "movq       (%1), %%mm6\n"   /* 4 blockvals 0 1 2 3 */

        		   "movq       %%mm0, %%mm2\n"
        		   "movq       8(%1), %%mm5\n"  /* 4 blockvals 0 1 2 3 */
        		   "punpcklbw  %%mm4, %%mm0\n"  /* 0 2 4 6 */
        		   "punpckhbw  %%mm4, %%mm2\n"  /* 1 3 5 7 */

        		   "paddw      %%mm6, %%mm0\n"
        		   "paddw      %%mm5, %%mm2\n"
        		   "packuswb   %%mm2, %%mm0\n"

        		   "addl       $16, %1\n"
        		   "movq       %%mm0, (%2)\n"

        		   "leal       (%2,%3), %2\n"
        		 "loop       1b\n"
        		 :              /* scr   dest */
        		 : "c" (8),"r" (bp), "r" (rfp), "r" (iincr)
    		);
    		}
		}
		else
#endif
			for(i = 0; i < 8; i++)
			{
    			rfp[0] = CLIP(bp[0] + rfp[0]);
    			rfp[1] = CLIP(bp[1] + rfp[1]);
    			rfp[2] = CLIP(bp[2] + rfp[2]);
    			rfp[3] = CLIP(bp[3] + rfp[3]);
    			rfp[4] = CLIP(bp[4] + rfp[4]);
    			rfp[5] = CLIP(bp[5] + rfp[5]);
    			rfp[6] = CLIP(bp[6] + rfp[6]);
    			rfp[7] = CLIP(bp[7] + rfp[7]);
    			rfp += iincr;
    			bp += 8;
			}
