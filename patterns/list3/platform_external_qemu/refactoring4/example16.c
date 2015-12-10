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
                  "movq   " MASK48_0 ", %%mm0 \n\t" // _mask48_0 -> mm0
                  "movq   " MASK48_1 ", %%mm1 \n\t" // _mask48_1 -> mm1
                  "movq   " MASK48_2 ", %%mm2 \n\t" // _mask48_2 -> mm2
                  "movq   " MASK48_3 ", %%mm3 \n\t" // _mask48_3 -> mm3
                  "movq   " MASK48_4 ", %%mm4 \n\t" // _mask48_4 -> mm4
                  "movq   " MASK48_5 ", %%mm5 \n\t" // _mask48_5 -> mm5
                  RESTORE_rbp

                  "pand      %%mm7, %%mm0     \n\t"
                  "pand      %%mm7, %%mm1     \n\t"
                  "pand      %%mm7, %%mm2     \n\t"
                  "pand      %%mm7, %%mm3     \n\t"
                  "pand      %%mm7, %%mm4     \n\t"
                  "pand      %%mm7, %%mm5     \n\t"

                  "pcmpeqb   %%mm6, %%mm0     \n\t"
                  "pcmpeqb   %%mm6, %%mm1     \n\t"
                  "pcmpeqb   %%mm6, %%mm2     \n\t"
                  "pcmpeqb   %%mm6, %%mm3     \n\t"
                  "pcmpeqb   %%mm6, %%mm4     \n\t"
                  "pcmpeqb   %%mm6, %%mm5     \n\t"

// preload        "movl      len, %%ecx       \n\t" // load length of line
// preload        "movl      srcptr, %3       \n\t" // load source
// preload        "movl      dstptr, %4       \n\t" // load dest

                  "cmpl      $0, %%ecx        \n\t"
                  "jz        mainloop48end    \n\t"

                "mainloop48:                  \n\t"
                  "movq      (%3), %%mm7      \n\t"
                  "pand      %%mm0, %%mm7     \n\t"
                  "movq      %%mm0, %%mm6     \n\t"
                  "pandn     (%4), %%mm6      \n\t"
                  "por       %%mm6, %%mm7     \n\t"
                  "movq      %%mm7, (%4)      \n\t"

                  "movq      8(%3), %%mm6     \n\t"
                  "pand      %%mm1, %%mm6     \n\t"
                  "movq      %%mm1, %%mm7     \n\t"
                  "pandn     8(%4), %%mm7     \n\t"
                  "por       %%mm7, %%mm6     \n\t"
                  "movq      %%mm6, 8(%4)     \n\t"

                  "movq      16(%3), %%mm6    \n\t"
                  "pand      %%mm2, %%mm6     \n\t"
                  "movq      %%mm2, %%mm7     \n\t"
                  "pandn     16(%4), %%mm7    \n\t"
                  "por       %%mm7, %%mm6     \n\t"
                  "movq      %%mm6, 16(%4)    \n\t"

                  "movq      24(%3), %%mm7    \n\t"
                  "pand      %%mm3, %%mm7     \n\t"
                  "movq      %%mm3, %%mm6     \n\t"
                  "pandn     24(%4), %%mm6    \n\t"
                  "por       %%mm6, %%mm7     \n\t"
                  "movq      %%mm7, 24(%4)    \n\t"

                  "movq      32(%3), %%mm6    \n\t"
                  "pand      %%mm4, %%mm6     \n\t"
                  "movq      %%mm4, %%mm7     \n\t"
                  "pandn     32(%4), %%mm7    \n\t"
                  "por       %%mm7, %%mm6     \n\t"
                  "movq      %%mm6, 32(%4)    \n\t"

                  "movq      40(%3), %%mm7    \n\t"
                  "pand      %%mm5, %%mm7     \n\t"
                  "movq      %%mm5, %%mm6     \n\t"
                  "pandn     40(%4), %%mm6    \n\t"
                  "por       %%mm6, %%mm7     \n\t"
                  "movq      %%mm7, 40(%4)    \n\t"

                  "add       $48, %3          \n\t" // inc by 48 bytes processed
                  "add       $48, %4          \n\t"
                  "subl      $8, %%ecx        \n\t" // dec by 8 pixels processed

                  "ja        mainloop48       \n\t"

                "mainloop48end:               \n\t"
// preload        "movl      diff, %%ecx      \n\t" // (diff is in eax)
                  "movl      %%eax, %%ecx     \n\t"
                  "cmpl      $0, %%ecx        \n\t"
                  "jz        end48            \n\t"
// preload        "movl      mask, %%edx      \n\t"
                  "sall      $24, %%edx       \n\t" // make low byte, high byte

                "secondloop48:                \n\t"
                  "sall      %%edx            \n\t" // move high bit to CF
                  "jnc       skip48           \n\t" // if CF = 0
                  "movl      (%3), %%eax      \n\t"
                  "movl      %%eax, (%4)      \n\t"
                  "movw      4(%3), %%ax      \n\t" // GR-P bugfix 20070717
                  "movw      %%ax, 4(%4)      \n\t" // GR-P bugfix 20070717

                "skip48:                      \n\t"
                  "add       $6, %3           \n\t" // GR-P bugfix 20070717
                  "add       $6, %4           \n\t" // GR-P bugfix 20070717
                  "decl      %%ecx            \n\t"
                  "jnz       secondloop48     \n\t"

                "end48:                       \n\t"
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
                  : "%mm0", "%mm1", "%mm2", "%mm3"  // clobber list
                  , "%mm4", "%mm5", "%mm6", "%mm7"
#endif
               );
            }
            else /* not _mmx_supported - use modified C routine */
            {
               register png_uint_32 i;
               png_uint_32 initial_val = BPP6 * png_pass_start[png_ptr->pass];
                 /* png.c:  png_pass_start[] = {0, 4, 0, 2, 0, 1, 0}; */
               register int stride = BPP6 * png_pass_inc[png_ptr->pass];
                 /* png.c:  png_pass_inc[] = {8, 8, 4, 4, 2, 2, 1}; */
               register int rep_bytes = BPP6 * png_pass_width[png_ptr->pass];
                 /* png.c:  png_pass_width[] = {8, 4, 4, 2, 2, 1, 1}; */
               png_uint_32 len = png_ptr->width &~7;  /* reduce to mult. of 8 */
               int diff = (int) (png_ptr->width & 7); /* amount lost */
               register png_uint_32 final_val = BPP6 * len;   /* GRR bugfix */

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
                  final_val += diff*BPP6;
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
