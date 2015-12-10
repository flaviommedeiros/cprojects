#if !defined(PNG_1_0_X)
if (png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_INTERLACE)
#else
            if (_mmx_supported)
#endif
            {
               int dummy_value_c;        // fix 'forbidden register spilled'
               png_bytep dummy_value_S;
               png_bytep dummy_value_D;
               png_bytep dummy_value_a;
               png_bytep dummy_value_d;

               //--------------------------------------------------------------
               if (pixel_bytes == BPP3)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) - 8;   // GRR:  huh?
                     if (width_mmx < 0)
                         width_mmx = 0;
                     width -= width_mmx;        // 8 or 9 pix, 24 or 27 bytes
                     if (width_mmx)
                     {
                        // png_pass_inc[] = {8, 8, 4, 4, 2, 2, 1};
                        // sptr points at last pixel in pre-expanded row
                        // dp points at last pixel position in expanded row
                        __asm__ __volatile__ (
                           "sub  $3, %1             \n\t"
                           "sub  $9, %2             \n\t"
                                        // (png_pass_inc[pass] + 1)*pixel_bytes

                        ".loop3_pass4:              \n\t"
                           "movq (%1), %%mm0        \n\t" // x x 5 4 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // x x 5 4 3 2 1 0
                           "movq %%mm0, %%mm2       \n\t" // x x 5 4 3 2 1 0
                           "psllq $24, %%mm0        \n\t" // 4 3 2 1 0 z z z
                           "pand (%3), %%mm1        \n\t" // z z z z z 2 1 0
                           "psrlq $24, %%mm2        \n\t" // z z z x x 5 4 3
                           "por %%mm1, %%mm0        \n\t" // 4 3 2 1 0 2 1 0
                           "movq %%mm2, %%mm3       \n\t" // z z z x x 5 4 3
                           "psllq $8, %%mm2         \n\t" // z z x x 5 4 3 z
                           "movq %%mm0, (%2)        \n\t"
                           "psrlq $16, %%mm3        \n\t" // z z z z z x x 5
                           "pand (%4), %%mm3        \n\t" // z z z z z z z 5
                           "por %%mm3, %%mm2        \n\t" // z z x x 5 4 3 5
                           "sub  $6, %1             \n\t"
                           "movd %%mm2, 8(%2)       \n\t"
                           "sub  $12, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop3_pass4        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D),
                             "=a" (dummy_value_a),
                             "=d" (dummy_value_d)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp),            // edi/rdi
#if defined(PNG_x86_64_USE_GOTPCREL)     // formerly _const4 and _const6:
                             "3" (&_c64._amask5_3_0), // (0x0000000000FFFFFFLL)
                             "4" (&_c64._amask7_1_0)  // (0x00000000000000FFLL)
#else
                             "3" (&_amask5_3_0),  // eax (0x0000000000FFFFFFLL)
                             "4" (&_amask7_1_0)   // edx (0x00000000000000FFLL)
#endif

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
                           , "%mm2", "%mm3"
#endif
                        );
                     }

                     sptr -= width_mmx*BPP3;
                     dp -= width_mmx*2*BPP3;
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;

                        png_memcpy(v, sptr, BPP3);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           png_memcpy(dp, v, BPP3);
                           dp -= BPP3;
                        }
                        sptr -= BPP3;
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     __asm__ __volatile__ (
                        "sub  $9, %2             \n\t"
                                     // (png_pass_inc[pass] - 1)*pixel_bytes

                     ".loop3_pass2:              \n\t"
                        "movd (%1), %%mm0        \n\t" // x x x x x 2 1 0
                        "pand (%3), %%mm0        \n\t" // z z z z z 2 1 0
                        "movq %%mm0, %%mm1       \n\t" // z z z z z 2 1 0
                        "psllq $16, %%mm0        \n\t" // z z z 2 1 0 z z
                        "movq %%mm0, %%mm2       \n\t" // z z z 2 1 0 z z
                        "psllq $24, %%mm0        \n\t" // 2 1 0 z z z z z
                        "psrlq $8, %%mm1         \n\t" // z z z z z z 2 1
                        "por %%mm2, %%mm0        \n\t" // 2 1 0 2 1 0 z z
                        "por %%mm1, %%mm0        \n\t" // 2 1 0 2 1 0 2 1
                        "movq %%mm0, 4(%2)       \n\t"
                        "psrlq $16, %%mm0        \n\t" // z z 2 1 0 2 1 0
                        "sub  $3, %1             \n\t"
                        "movd %%mm0, (%2)        \n\t"
                        "sub  $12, %2            \n\t"
                        "decl %%ecx              \n\t"
                        "jnz .loop3_pass2        \n\t"
                        "EMMS                    \n\t" // DONE

                        : "=c" (dummy_value_c),        // output regs (dummy)
                          "=S" (dummy_value_S),
                          "=D" (dummy_value_D),
                          "=a" (dummy_value_a)

                        : "0" (width),         // ecx  // input regs
                          "1" (sptr),          // esi/rsi
                          "2" (dp),            // edi/rdi
#if defined(PNG_x86_64_USE_GOTPCREL)           // formerly _const4:
                          "3" (&_c64._amask5_3_0)  // (0x0000000000FFFFFFLL)
#else
                          "3" (&_amask5_3_0)   // eax (0x0000000000FFFFFFLL)
#endif

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                        : "%mm0", "%mm1", "%mm2"       // clobber list
#endif
                     );
                  }
                  else if (width)  // && ((pass == 0) || (pass == 1))
                  {
                     __asm__ __volatile__ (
                        "sub  $21, %2            \n\t"
                                     // (png_pass_inc[pass] - 1)*pixel_bytes

                     ".loop3_pass0:              \n\t"
                        "movd (%1), %%mm0        \n\t" // x x x x x 2 1 0
                        "pand (%3), %%mm0        \n\t" // z z z z z 2 1 0
                        "movq %%mm0, %%mm1       \n\t" // z z z z z 2 1 0
                        "psllq $16, %%mm0        \n\t" // z z z 2 1 0 z z
                        "movq %%mm0, %%mm2       \n\t" // z z z 2 1 0 z z
                        "psllq $24, %%mm0        \n\t" // 2 1 0 z z z z z
                        "psrlq $8, %%mm1         \n\t" // z z z z z z 2 1
                        "por %%mm2, %%mm0        \n\t" // 2 1 0 2 1 0 z z
                        "por %%mm1, %%mm0        \n\t" // 2 1 0 2 1 0 2 1
                        "movq %%mm0, %%mm3       \n\t" // 2 1 0 2 1 0 2 1
                        "psllq $16, %%mm0        \n\t" // 0 2 1 0 2 1 z z
                        "movq %%mm3, %%mm4       \n\t" // 2 1 0 2 1 0 2 1
                        "punpckhdq %%mm0, %%mm3  \n\t" // 0 2 1 0 2 1 0 2
                        "movq %%mm4, 16(%2)      \n\t"
                        "psrlq $32, %%mm0        \n\t" // z z z z 0 2 1 0
                        "movq %%mm3, 8(%2)       \n\t"
                        "punpckldq %%mm4, %%mm0  \n\t" // 1 0 2 1 0 2 1 0
                        "sub  $3, %1             \n\t"
                        "movq %%mm0, (%2)        \n\t"
                        "sub  $24, %2            \n\t"
                        "decl %%ecx              \n\t"
                        "jnz .loop3_pass0        \n\t"
                        "EMMS                    \n\t" // DONE

                        : "=c" (dummy_value_c),        // output regs (dummy)
                          "=S" (dummy_value_S),
                          "=D" (dummy_value_D),
                          "=a" (dummy_value_a)

                        : "0" (width),         // ecx  // input regs
                          "1" (sptr),          // esi/rsi
                          "2" (dp),            // edi/rdi
#if defined(PNG_x86_64_USE_GOTPCREL)           // formerly _const4:
                          "3" (&_c64._amask5_3_0)  // (0x0000000000FFFFFFLL)
#else
                          "3" (&_amask5_3_0)   // eax (0x0000000000FFFFFFLL)
#endif

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                        : "%mm0", "%mm1", "%mm2"       // clobber list
                        , "%mm3", "%mm4"
#endif
                     );
                  }
               } /* end of pixel_bytes == 3 */

               //--------------------------------------------------------------
               else if (pixel_bytes == BPP4)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;        // 0,1 pixels => 0,4 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $4, %1             \n\t"
                           "sub  $12, %2            \n\t"

                        ".loop4_pass4:              \n\t"
                           "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // 7 6 5 4 3 2 1 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 3 2 1 0 3 2 1 0
                           "punpckhdq %%mm1, %%mm1  \n\t" // 7 6 5 4 7 6 5 4
                           "movq %%mm0, (%2)        \n\t"
                           "sub  $8, %1             \n\t"
                           "movq %%mm1, 8(%2)       \n\t"
                           "sub  $16, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop4_pass4        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*BPP4 - BPP4); // sign fixed
                     dp -= (width_mmx*2*BPP4 - BPP4); // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= BPP4;
                        png_memcpy(v, sptr, BPP4);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= BPP4;
                           png_memcpy(dp, v, BPP4);
                        }
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1);
                     width -= width_mmx;        // 0,1 pixels => 0,4 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $4, %1             \n\t"
                           "sub  $28, %2            \n\t"

                        ".loop4_pass2:              \n\t"
                           "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // 7 6 5 4 3 2 1 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 3 2 1 0 3 2 1 0
                           "punpckhdq %%mm1, %%mm1  \n\t" // 7 6 5 4 7 6 5 4
                           "movq %%mm0, (%2)        \n\t"
                           "movq %%mm0, 8(%2)       \n\t"
                           "movq %%mm1, 16(%2)      \n\t"
                           "movq %%mm1, 24(%2)      \n\t"
                           "sub  $8, %1             \n\t"
                           "sub  $32, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop4_pass2        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*4 - 4); // sign fixed
                     dp -= (width_mmx*16 - 4);  // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= 4;
                        png_memcpy(v, sptr, 4);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= 4;
                           png_memcpy(dp, v, 4);
                        }
                     }
                  }
                  else if (width)  // && ((pass == 0) || (pass == 1))
                  {
                     int width_mmx = ((width >> 1) << 1);
                     width -= width_mmx;        // 0,1 pixels => 0,4 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $4, %1             \n\t"
                           "sub  $60, %2            \n\t"

                        ".loop4_pass0:              \n\t"
                           "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // 7 6 5 4 3 2 1 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 3 2 1 0 3 2 1 0
                           "punpckhdq %%mm1, %%mm1  \n\t" // 7 6 5 4 7 6 5 4
                           "movq %%mm0, (%2)        \n\t"
                           "movq %%mm0, 8(%2)       \n\t"
                           "movq %%mm0, 16(%2)      \n\t"
                           "movq %%mm0, 24(%2)      \n\t"
                           "movq %%mm1, 32(%2)      \n\t"
                           "movq %%mm1, 40(%2)      \n\t"
                           "movq %%mm1, 48(%2)      \n\t"
                           "sub  $8, %1             \n\t"
                           "movq %%mm1, 56(%2)      \n\t"
                           "sub  $64, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop4_pass0        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*4 - 4); // sign fixed
                     dp -= (width_mmx*32 - 4);  // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= 4;
                        png_memcpy(v, sptr, 4);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= 4;
                           png_memcpy(dp, v, 4);
                        }
                     }
                  }
               } /* end of pixel_bytes == 4 */

               //--------------------------------------------------------------
               else if (pixel_bytes == 1)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 3) << 3);
                     width -= width_mmx;        // 0-3 pixels => 0-3 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $7, %1             \n\t"
                           "sub  $15, %2            \n\t"

                        ".loop1_pass4:              \n\t"
                           "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // 7 6 5 4 3 2 1 0
                           "punpcklbw %%mm0, %%mm0  \n\t" // 3 3 2 2 1 1 0 0
                           "punpckhbw %%mm1, %%mm1  \n\t" // 7 7 6 6 5 5 4 4
                           "movq %%mm1, 8(%2)       \n\t"
                           "sub  $8, %1             \n\t"
                           "movq %%mm0, (%2)        \n\t"
                           "sub  $16, %2            \n\t"
                           "subl $8, %%ecx          \n\t"
                           "jnz .loop1_pass4        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= width_mmx;
                     dp -= width_mmx*2;
                     for (i = width; i; i--)
                     {
                        int j;

                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           *dp-- = *sptr;
                        }
                        --sptr;
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 2) << 2);
                     width -= width_mmx;        // 0-3 pixels => 0-3 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $3, %1             \n\t"
                           "sub  $15, %2            \n\t"

                        ".loop1_pass2:              \n\t"
                           "movd (%1), %%mm0        \n\t" // x x x x 3 2 1 0
                           "punpcklbw %%mm0, %%mm0  \n\t" // 3 3 2 2 1 1 0 0
                           "movq %%mm0, %%mm1       \n\t" // 3 3 2 2 1 1 0 0
                           "punpcklwd %%mm0, %%mm0  \n\t" // 1 1 1 1 0 0 0 0
                           "punpckhwd %%mm1, %%mm1  \n\t" // 3 3 3 3 2 2 2 2
                           "movq %%mm0, (%2)        \n\t"
                           "sub  $4, %1             \n\t"
                           "movq %%mm1, 8(%2)       \n\t"
                           "sub  $16, %2            \n\t"
                           "subl $4, %%ecx          \n\t"
                           "jnz .loop1_pass2        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= width_mmx;
                     dp -= width_mmx*4;
                     for (i = width; i; i--)
                     {
                        int j;

                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           *dp-- = *sptr;
                        }
                        --sptr;
                     }
                  }
                  else if (width)  // && ((pass == 0) || (pass == 1))
                  {
                     int width_mmx = ((width >> 2) << 2);
                     width -= width_mmx;        // 0-3 pixels => 0-3 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $3, %1             \n\t"
                           "sub  $31, %2            \n\t"

                        ".loop1_pass0:              \n\t"
                           "movd (%1), %%mm0        \n\t" // x x x x 3 2 1 0
                           "movq %%mm0, %%mm1       \n\t" // x x x x 3 2 1 0
                           "punpcklbw %%mm0, %%mm0  \n\t" // 3 3 2 2 1 1 0 0
                           "movq %%mm0, %%mm2       \n\t" // 3 3 2 2 1 1 0 0
                           "punpcklwd %%mm0, %%mm0  \n\t" // 1 1 1 1 0 0 0 0
                           "movq %%mm0, %%mm3       \n\t" // 1 1 1 1 0 0 0 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 0 0 0 0 0 0 0 0
                           "punpckhdq %%mm3, %%mm3  \n\t" // 1 1 1 1 1 1 1 1
                           "movq %%mm0, (%2)        \n\t"
                           "punpckhwd %%mm2, %%mm2  \n\t" // 3 3 3 3 2 2 2 2
                           "movq %%mm3, 8(%2)       \n\t"
                           "movq %%mm2, %%mm4       \n\t" // 3 3 3 3 2 2 2 2
                           "punpckldq %%mm2, %%mm2  \n\t" // 2 2 2 2 2 2 2 2
                           "punpckhdq %%mm4, %%mm4  \n\t" // 3 3 3 3 3 3 3 3
                           "movq %%mm2, 16(%2)      \n\t"
                           "sub  $4, %1             \n\t"
                           "movq %%mm4, 24(%2)      \n\t"
                           "sub  $32, %2            \n\t"
                           "subl $4, %%ecx          \n\t"
                           "jnz .loop1_pass0        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1", "%mm2"       // clobber list
                           , "%mm3", "%mm4"
#endif
                        );
                     }

                     sptr -= width_mmx;
                     dp -= width_mmx*8;
                     for (i = width; i; i--)
                     {
                        int j;

                       /* I simplified this part in version 1.0.4e
                        * here and in several other instances where
                        * pixel_bytes == 1  -- GR-P
                        *
                        * Original code:
                        *
                        * png_byte v[8];
                        * png_memcpy(v, sptr, pixel_bytes);
                        * for (j = 0; j < png_pass_inc[pass]; j++)
                        * {
                        *    png_memcpy(dp, v, pixel_bytes);
                        *    dp -= pixel_bytes;
                        * }
                        * sptr -= pixel_bytes;
                        *
                        * Replacement code is in the next three lines:
                        */

                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           *dp-- = *sptr;
                        }
                        --sptr;
                     }
                  }
               } /* end of pixel_bytes == 1 */

               //--------------------------------------------------------------
               else if (pixel_bytes == BPP2)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;        // 0,1 pixels => 0,2 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $2, %1             \n\t"
                           "sub  $6, %2             \n\t"

                        ".loop2_pass4:              \n\t"
                           "movd (%1), %%mm0        \n\t" // x x x x 3 2 1 0
                           "punpcklwd %%mm0, %%mm0  \n\t" // 3 2 3 2 1 0 1 0
                           "sub  $4, %1             \n\t"
                           "movq %%mm0, (%2)        \n\t"
                           "sub  $8, %2             \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop2_pass4        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0"                       // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*BPP2 - BPP2); // sign fixed
                     dp -= (width_mmx*2*BPP2 - BPP2); // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= BPP2;
                        png_memcpy(v, sptr, BPP2);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= BPP2;
                           png_memcpy(dp, v, BPP2);
                        }
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;        // 0,1 pixels => 0,2 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $2, %1             \n\t"
                           "sub  $14, %2            \n\t"

                        ".loop2_pass2:              \n\t"
                           "movd (%1), %%mm0        \n\t" // x x x x 3 2 1 0
                           "punpcklwd %%mm0, %%mm0  \n\t" // 3 2 3 2 1 0 1 0
                           "movq %%mm0, %%mm1       \n\t" // 3 2 3 2 1 0 1 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 1 0 1 0 1 0 1 0
                           "punpckhdq %%mm1, %%mm1  \n\t" // 3 2 3 2 3 2 3 2
                           "movq %%mm0, (%2)        \n\t"
                           "sub  $4, %1             \n\t"
                           "movq %%mm1, 8(%2)       \n\t"
                           "sub  $16, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop2_pass2        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*2 - 2); // sign fixed
                     dp -= (width_mmx*8 - 2);   // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= 2;
                        png_memcpy(v, sptr, 2);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= 2;
                           png_memcpy(dp, v, 2);
                        }
                     }
                  }
                  else if (width)  // && ((pass == 0) || (pass == 1))
                  {
                     int width_mmx = ((width >> 1) << 1);
                     width -= width_mmx;        // 0,1 pixels => 0,2 bytes
                     if (width_mmx)
                     {
                        __asm__ __volatile__ (
                           "sub  $2, %1             \n\t"
                           "sub  $30, %2            \n\t"

                        ".loop2_pass0:              \n\t"
                           "movd (%1), %%mm0        \n\t" // x x x x 3 2 1 0
                           "punpcklwd %%mm0, %%mm0  \n\t" // 3 2 3 2 1 0 1 0
                           "movq %%mm0, %%mm1       \n\t" // 3 2 3 2 1 0 1 0
                           "punpckldq %%mm0, %%mm0  \n\t" // 1 0 1 0 1 0 1 0
                           "punpckhdq %%mm1, %%mm1  \n\t" // 3 2 3 2 3 2 3 2
                           "movq %%mm0, (%2)        \n\t"
                           "movq %%mm0, 8(%2)       \n\t"
                           "movq %%mm1, 16(%2)      \n\t"
                           "sub  $4, %1             \n\t"
                           "movq %%mm1, 24(%2)      \n\t"
                           "sub  $32, %2            \n\t"
                           "subl $2, %%ecx          \n\t"
                           "jnz .loop2_pass0        \n\t"
                           "EMMS                    \n\t" // DONE

                           : "=c" (dummy_value_c),        // output regs (dummy)
                             "=S" (dummy_value_S),
                             "=D" (dummy_value_D)

                           : "0" (width_mmx),     // ecx  // input regs
                             "1" (sptr),          // esi/rsi
                             "2" (dp)             // edi/rdi

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                           : "%mm0", "%mm1"               // clobber list
#endif
                        );
                     }

                     sptr -= (width_mmx*2 - 2); // sign fixed
                     dp -= (width_mmx*16 - 2);  // sign fixed
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;
                        sptr -= 2;
                        png_memcpy(v, sptr, 2);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           dp -= 2;
                           png_memcpy(dp, v, 2);
                        }
                     }
                  }
               } /* end of pixel_bytes == 2 */

               //--------------------------------------------------------------
               else if (pixel_bytes == BPP8)
               {
// GRR TEST:  should work, but needs testing (special 64-bit version of rpng2?)
                  // GRR NOTE:  no need to combine passes here!
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     // source is 8-byte RRGGBBAA
                     // dest is 16-byte RRGGBBAA RRGGBBAA
                     __asm__ __volatile__ (
                        "sub  $8, %2             \n\t" // start of last block

                     ".loop8_pass4:              \n\t"
                        "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                        "movq %%mm0, (%2)        \n\t"
                        "sub  $8, %1             \n\t"
                        "movq %%mm0, 8(%2)       \n\t"
                        "sub  $16, %2            \n\t"
                        "decl %%ecx              \n\t"
                        "jnz .loop8_pass4        \n\t"
                        "EMMS                    \n\t" // DONE

                        : "=c" (dummy_value_c),        // output regs (dummy)
                          "=S" (dummy_value_S),
                          "=D" (dummy_value_D)

                        : "0" (width),         // ecx  // input regs
                          "1" (sptr),          // esi/rsi
                          "2" (dp)             // edi/rdi

#if defined(CLOBBER_MMX_REGS_SUPPORTED)
                        : "%mm0"                       // clobber list
#endif
                     );
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     // source is 8-byte RRGGBBAA
                     // dest is 32-byte RRGGBBAA RRGGBBAA RRGGBBAA RRGGBBAA
                     // (recall that expansion is _in place_:  sptr and dp
                     //  both point at locations within same row buffer)
                     __asm__ __volatile__ (
                        "sub  $24, %2            \n\t" // start of last block

                     ".loop8_pass2:              \n\t"
                        "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                        "movq %%mm0, (%2)        \n\t"
                        "movq %%mm0, 8(%2)       \n\t"
                        "movq %%mm0, 16(%2)      \n\t"
                        "sub  $8, %1             \n\t"
                        "movq %%mm0, 24(%2)      \n\t"
                        "sub  $32, %2            \n\t"
                        "decl %%ecx              \n\t"
                        "jnz .loop8_pass2        \n\t"
                        "EMMS                    \n\t" // DONE

                        : "=c" (dummy_value_c),        // output regs (dummy)
                          "=S" (dummy_value_S),
                          "=D" (dummy_value_D)

                        : "0" (width),         // ecx  // input regs
                          "1" (sptr),          // esi/rsi
                          "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                        : "%mm0"                       // clobber list
#endif
                     );
                  }
                  else if (width)  // && ((pass == 0) || (pass == 1))
                  {
                     // source is 8-byte RRGGBBAA
                     // dest is 64-byte RRGGBBAA RRGGBBAA RRGGBBAA RRGGBBAA ...
                     __asm__ __volatile__ (
                        "sub  $56, %2            \n\t" // start of last block

                     ".loop8_pass0:              \n\t"
                        "movq (%1), %%mm0        \n\t" // 7 6 5 4 3 2 1 0
                        "movq %%mm0, (%2)        \n\t"
                        "movq %%mm0, 8(%2)       \n\t"
                        "movq %%mm0, 16(%2)      \n\t"
                        "movq %%mm0, 24(%2)      \n\t"
                        "movq %%mm0, 32(%2)      \n\t"
                        "movq %%mm0, 40(%2)      \n\t"
                        "movq %%mm0, 48(%2)      \n\t"
                        "sub  $8, %1             \n\t"
                        "movq %%mm0, 56(%2)      \n\t"
                        "sub  $64, %2            \n\t"
                        "decl %%ecx              \n\t"
                        "jnz .loop8_pass0        \n\t"
                        "EMMS                    \n\t" // DONE

                        : "=c" (dummy_value_c),        // output regs (dummy)
                          "=S" (dummy_value_S),
                          "=D" (dummy_value_D)

                        : "0" (width),         // ecx  // input regs
                          "1" (sptr),          // esi/rsi
                          "2" (dp)             // edi/rdi

#if defined(PNG_CLOBBER_MMX_REGS_SUPPORTED)
                        : "%mm0"                       // clobber list
#endif
                     );
                  }
               } /* end of pixel_bytes == 8 */

               //--------------------------------------------------------------
               else if (pixel_bytes == BPP6)   // why no MMX for this case?
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP6);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, BPP6);
                        dp -= BPP6;
                     }
                     sptr -= BPP6;
                  }
               } /* end of pixel_bytes == 6 */

               //--------------------------------------------------------------
               else
               {
                  // ERROR:  SHOULD NEVER BE REACHED
#if defined(PNG_DEBUG)
                  png_debug(1, "Internal libpng logic error (GCC "
                    "png_do_read_interlace() _mmx_supported)\n");
#endif
               }

            } // end of _mmx_supported ========================================

            else /* MMX not supported:  use modified C code - takes advantage
                  *   of inlining of png_memcpy for a constant */
            {
               if (pixel_bytes == BPP3)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP3);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, BPP3);
                        dp -= BPP3;
                     }
                     sptr -= BPP3;
                  }
               }
               else if (pixel_bytes == BPP4)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP4);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
#if defined(PNG_DEBUG) && defined(PNG_1_0_X)  // row_buf_size gone in 1.2.x
                        if (dp < row || dp+3 > row+png_ptr->row_buf_size)
                        {
                           printf("dp out of bounds: row=%10p, dp=%10p, "
                             "rp=%10p\n", row, dp, row+png_ptr->row_buf_size);
                           printf("row_buf_size=%lu\n", png_ptr->row_buf_size);
                        }
#endif
                        png_memcpy(dp, v, BPP4);
                        dp -= BPP4;
                     }
                     sptr -= BPP4;
                  }
               }
               else if (pixel_bytes == 1)
               {
                  for (i = width; i; i--)
                  {
                     int j;
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        *dp-- = *sptr;
                     }
                     --sptr;
                  }
               }
               else if (pixel_bytes == BPP2)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP2);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, BPP2);
                        dp -= BPP2;
                     }
                     sptr -= BPP2;
                  }
               }
               else if (pixel_bytes == BPP6)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP6);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, BPP6);
                        dp -= BPP6;
                     }
                     sptr -= BPP6;
                  }
               }
               else if (pixel_bytes == BPP8)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, BPP8);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, BPP8);
                        dp -= BPP8;
                     }
                     sptr -= BPP8;
                  }
               }
               else
               {
                  // ERROR:  SHOULD NEVER BE REACHED
#if defined(PNG_DEBUG)
                  png_debug(1, "Internal libpng logic error (GCC "
                    "png_do_read_interlace() !_mmx_supported)\n");
#endif
               }

            }
