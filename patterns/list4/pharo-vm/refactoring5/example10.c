#ifdef HAVE_MMX
if(video->have_mmx)
		{
    		if(spar) 
			{
            __asm__ __volatile__(
            	"movd       (%2),           %%mm0\n"    /* " 0 0 0  v1" */
            	"punpcklwd  %%mm0,          %%mm0\n"    /* " 0 0 v1 v1" */
            	"punpcklwd  %%mm0,          %%mm0\n"
            	"paddw      _MMX_128,        %%mm0\n"
            	"packuswb   %%mm0,          %%mm0\n"
            	"leal       (%0,%1,2),      %%eax\n"

            	"movq        %%mm0,         (%0, %1)\n"
            	"movq        %%mm0,         (%%eax)\n"
            	"leal        (%%eax,%1,2),  %0\n"
            	"movq        %%mm0,         (%%eax, %1)\n"

            	"movq        %%mm0,         (%0)\n"
            	"leal        (%0,%1,2),     %%eax\n"
            	"movq        %%mm0,         (%0, %1)\n"

            	"movq        %%mm0,         (%%eax)\n"
            	"movq        %%mm0,         (%%eax, %1)\n"
            	:
            	: "D" (rfp), "c" (iincr), "b" (bp)
            	: "eax");
    		}
    		else 
			{
    		__asm__ __volatile__(
            	"movq        _MMX_128,%%mm4\n"
            	".align 8\n"
            	"1:"
            	  "movq      (%1),   %%mm0\n"
            	  "movq      8(%1),  %%mm1\n"
            	  "paddw     %%mm4,  %%mm0\n"

            	  "movq      16(%1), %%mm2\n"
            	  "paddw     %%mm4,  %%mm1\n"

            	  "movq      24(%1), %%mm3\n"
            	  "paddw     %%mm4,  %%mm2\n"

            	  "packuswb  %%mm1,  %%mm0\n"
            	  "paddw     %%mm4,  %%mm3\n"

            	  "addl $32, %1\n"
            	  "packuswb  %%mm3,  %%mm2\n"

            	  "movq   %%mm0, (%2)\n"

            	  "movq   %%mm2, (%2,%3)\n"

            	  "leal       (%2,%3,2), %2\n"
            	"loop       1b\n"
            	:
            	: "c" (4), "r" (bp), "r" (rfp), "r" (iincr)
        	);
    		}
		}
		else
#endif
    		for(i = 0; i < 8; i++)
			{
    			rfp[0] = CLIP(bp[0] + 128);
    			rfp[1] = CLIP(bp[1] + 128);
    			rfp[2] = CLIP(bp[2] + 128);
    			rfp[3] = CLIP(bp[3] + 128);
    			rfp[4] = CLIP(bp[4] + 128);
    			rfp[5] = CLIP(bp[5] + 128);
    			rfp[6] = CLIP(bp[6] + 128);
    			rfp[7] = CLIP(bp[7] + 128);
    			rfp+= iincr;
    			bp += 8;
    		}
