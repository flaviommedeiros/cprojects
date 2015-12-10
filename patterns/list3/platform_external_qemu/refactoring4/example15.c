#if !defined(PNG_1_0_X)
if (png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_COMBINE_ROW)
#else
            if (_mmx_supported)
#endif
            {
               png_uint_32 len;
               int diff;

               srcptr = png_ptr->row_buf + 1;
               dstptr = row;
               len  = png_ptr->width & ~7;          // reduce to multiple of 8
               diff = (int) (png_ptr->width & 7);   // amount lost

               __asm__ __volatile__ (
                  "not       %%edx            \n\t" // mask => unmask
                  "movd      %%edx, %%mm7     \n\t" // load bit pattern
                  "not       %%edx            \n\t" // unmask => mask for later
                  "psubb     %%mm6, %%mm6     \n\t" // zero mm6
                  "punpcklbw %%mm7, %%mm7     \n\t"
                  "punpcklwd %%mm7, %%mm7     \n\t"
                  "punpckldq %%mm7, %%mm7     \n\t" // fill reg with 8 masks

                  LOAD_GOT_rbp
                  "movq   " MASK16_0 ", %%mm0 \n\t" // _mask16_0 -> mm0
                  "movq   " MASK16_1 ", %%mm1 \n\t" // _mask16_1 -> mm1
                  RESTORE_rbp

                  "pand      %%mm7, %%mm0     \n\t"
                  "pand      %%mm7, %%mm1     \n\t"

                  "pcmpeqb   %%mm6, %%mm0     \n\t"
                  "pcmpeqb   %%mm6, %%mm1     \n\t"

// preload        "movl      len, %%ecx       \n\t" // load length of line
// preload        "movl      srcptr, %3       \n\t" // load source
// preload        "movl      dstptr, %4       \n\t" // load dest

                  "cmpl      $0, %%ecx        \n\t"
                  "jz        mainloop16end    \n\t"

                "mainloop16:                  \n\t"
                  "movq      (%3), %%mm4      \n\t"
                  "pand      %%mm0, %%mm4     \n\t"
                  "movq      %%mm0, %%mm6     \n\t"
                  "movq      (%4), %%mm7      \n\t"
                  "pandn     %%mm7, %%mm6     \n\t"
                  "por       %%mm6, %%mm4     \n\t"
                  "movq      %%mm4, (%4)      \n\t"

                  "movq      8(%3), %%mm5     \n\t"
                  "pand      %%mm1, %%mm5     \n\t"
                  "movq      %%mm1, %%mm7     \n\t"
                  "movq      8(%4), %%mm6     \n\t"
                  "pandn     %%mm6, %%mm7     \n\t"
                  "por       %%mm7, %%mm5     \n\t"
                  "movq      %%mm5, 8(%4)     \n\t"

                  "add       $16, %3          \n\t" // inc by 16 bytes processed
                  "add       $16, %4          \n\t"
                  "subl      $8, %%ecx        \n\t" // dec by 8 pixels processed
                  "ja        mainloop16       \n\t"

                "mainloop16end:               \n\t"
// preload        "movl      diff, %%ecx      \n\t" // (diff is in eax)
                  "movl      %%eax, %%ecx     \n\t"
                  "cmpl      $0, %%ecx        \n\t"
                  "jz        end16            \n\t"
// preload        "movl      mask, %%edx      \n\t"
                  "sall      $24, %%edx       \n\t" // make low byte, high byte

                "secondloop16:                \n\t"
                  "sall      %%edx            \n\t" // move high bit to CF
                  "jnc       skip16           \n\t" // if CF = 0
                  "movw      (%3), %%ax       \n\t"
                  "movw      %%ax, (%4)       \n\t"

                "skip16:                      \n\t"
                  "add       $2, %3           \n\t"
                  "add       $2, %4           \n\t"
                  "decl      %%ecx            \n\t"
                  "jnz       secondloop16     \n\t"

                "end16:                       \n\t"
                  "EMMS                       \n\t" // DONE

                  : "=a" (dummy_value_a),           // output regs (dummy)
                    "=d" (dummy_value_d),
                    "=c" (dummy_value_c),
                    "=S" (dummy_value_S),
                    "=D" (dummy_value_D)

                  : "0" (diff),        // eax       // input regs
                    "1" (mask),        // edx
                    "2" (len),         // ecx
// was (unmask)     "b"    RESERVED    // ebx       // Global Offset Table idx
                    "3" (srcptr),      // esi/rsi
                    "4" (dstptr)       // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                  : "%mm0", "%mm1", "%mm4"          // clobber list
                  , "%mm5", "%mm6", "%mm7"
#endif
               );
            }
            else /* not _mmx_supported - use modified C routine */
            {
               register png_uint_32 i;
               png_uint_32 initial_val = BPP2 * png_pass_start[png_ptr->pass];
                 /* png.c:  png_pass_start[] = {0, 4, 0, 2, 0, 1, 0}; */
               register int stride = BPP2 * png_pass_inc[png_ptr->pass];
                 /* png.c:  png_pass_inc[] = {8, 8, 4, 4, 2, 2, 1}; */
               register int rep_bytes = BPP2 * png_pass_width[png_ptr->pass];
                 /* png.c:  png_pass_width[] = {8, 4, 4, 2, 2, 1, 1}; */
               png_uint_32 len = png_ptr->width &~7;  /* reduce to mult. of 8 */
               int diff = (int) (png_ptr->width & 7); /* amount lost */
               register png_uint_32 final_val = BPP2 * len;   /* GRR bugfix */

               srcptr = png_ptr->row_buf + 1 + initial_val;
               dstptr = row + initial_val;

               for (i = initial_val; i < final_val; i += stride)
               {
                  png_memcpy(dstptr, srcptr, rep_bytes);
                  srcptr += stride;
                  dstptr += stride;
               }
               if (diff)  /* number of leftover pixels:  3 for pngtest */
               {
                  final_val += diff*BPP2;
                  for (; i < final_val; i += stride)
                  {
                     if (rep_bytes > (int)(final_val-i))
                        rep_bytes = (int)(final_val-i);
                     png_memcpy(dstptr, srcptr, rep_bytes);
                     srcptr += stride;
                     dstptr += stride;
                  }
               }
            }
