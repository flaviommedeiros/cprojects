#if !defined(PNG_1_0_X)
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_INTERLACE)
                /* && mmx_supported */ )
#else
            if (mmx_supported)
#endif
            {
               if (pixel_bytes == 3)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) - 8;
                     if (width_mmx < 0)
                         width_mmx = 0;
                     width -= width_mmx;        // 8 or 9 pix, 24 or 27 bytes
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 3
                           sub edi, 9
loop_pass4:
                           movq mm0, [esi]     ; X X v2 v1 v0 v5 v4 v3
                           movq mm7, mm0       ; X X v2 v1 v0 v5 v4 v3
                           movq mm6, mm0       ; X X v2 v1 v0 v5 v4 v3
                           psllq mm0, 24       ; v1 v0 v5 v4 v3 0 0 0
                           pand mm7, const4    ; 0 0 0 0 0 v5 v4 v3
                           psrlq mm6, 24       ; 0 0 0 X X v2 v1 v0
                           por mm0, mm7        ; v1 v0 v5 v4 v3 v5 v4 v3
                           movq mm5, mm6       ; 0 0 0 X X v2 v1 v0
                           psllq mm6, 8        ; 0 0 X X v2 v1 v0 0
                           movq [edi], mm0     ; move quad to memory
                           psrlq mm5, 16       ; 0 0 0 0 0 X X v2
                           pand mm5, const6    ; 0 0 0 0 0 0 0 v2
                           por mm6, mm5        ; 0 0 X X v2 v1 v0 v2
                           movd [edi+8], mm6   ; move double to memory
                           sub esi, 6
                           sub edi, 12
                           sub ecx, 2
                           jnz loop_pass4
                           EMMS
                        }
                     }

                     sptr -= width_mmx*3;
                     dp -= width_mmx*6;
                     for (i = width; i; i--)
                     {
                        png_byte v[8];
                        int j;

                        png_memcpy(v, sptr, 3);
                        for (j = 0; j < png_pass_inc[pass]; j++)
                        {
                           png_memcpy(dp, v, 3);
                           dp -= 3;
                        }
                        sptr -= 3;
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     _asm
                     {
                        mov esi, sptr
                        mov edi, dp
                        mov ecx, width
                        sub edi, 9   // (png_pass_inc[pass] - 1)*pixel_bytes
loop_pass2:
                        movd mm0, [esi]     ; X X X X X v2 v1 v0
                        pand mm0, const4    ; 0 0 0 0 0 v2 v1 v0
                        movq mm1, mm0       ; 0 0 0 0 0 v2 v1 v0
                        psllq mm0, 16       ; 0 0 0 v2 v1 v0 0 0
                        movq mm2, mm0       ; 0 0 0 v2 v1 v0 0 0
                        psllq mm0, 24       ; v2 v1 v0 0 0 0 0 0
                        psrlq mm1, 8        ; 0 0 0 0 0 0 v2 v1
                        por mm0, mm2        ; v2 v1 v0 v2 v1 v0 0 0
                        por mm0, mm1        ; v2 v1 v0 v2 v1 v0 v2 v1
                        movq [edi+4], mm0   ; move to memory
                        psrlq mm0, 16       ; 0 0 v2 v1 v0 v2 v1 v0
                        movd [edi], mm0     ; move to memory
                        sub esi, 3
                        sub edi, 12
                        dec ecx
                        jnz loop_pass2
                        EMMS
                     }
                  }
                  else if (width) /* && ((pass == 0) || (pass == 1))) */
                  {
                     _asm
                     {
                        mov esi, sptr
                        mov edi, dp
                        mov ecx, width
                        sub edi, 21   // (png_pass_inc[pass] - 1)*pixel_bytes
loop_pass0:
                        movd mm0, [esi]     ; X X X X X v2 v1 v0
                        pand mm0, const4    ; 0 0 0 0 0 v2 v1 v0
                        movq mm1, mm0       ; 0 0 0 0 0 v2 v1 v0
                        psllq mm0, 16       ; 0 0 0 v2 v1 v0 0 0
                        movq mm2, mm0       ; 0 0 0 v2 v1 v0 0 0
                        psllq mm0, 24       ; v2 v1 v0 0 0 0 0 0
                        psrlq mm1, 8        ; 0 0 0 0 0 0 v2 v1
                        por mm0, mm2        ; v2 v1 v0 v2 v1 v0 0 0
                        por mm0, mm1        ; v2 v1 v0 v2 v1 v0 v2 v1
                        movq mm3, mm0       ; v2 v1 v0 v2 v1 v0 v2 v1
                        psllq mm0, 16       ; v0 v2 v1 v0 v2 v1 0 0
                        movq mm4, mm3       ; v2 v1 v0 v2 v1 v0 v2 v1
                        punpckhdq mm3, mm0  ; v0 v2 v1 v0 v2 v1 v0 v2
                        movq [edi+16] , mm4
                        psrlq mm0, 32       ; 0 0 0 0 v0 v2 v1 v0
                        movq [edi+8] , mm3
                        punpckldq mm0, mm4  ; v1 v0 v2 v1 v0 v2 v1 v0
                        sub esi, 3
                        movq [edi], mm0
                        sub edi, 24
                        //sub esi, 3
                        dec ecx
                        jnz loop_pass0
                        EMMS
                     }
                  }
               } /* end of pixel_bytes == 3 */

               else if (pixel_bytes == 1)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 3) << 3);
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub edi, 15
                           sub esi, 7
loop1_pass4:
                           movq mm0, [esi]     ; v0 v1 v2 v3 v4 v5 v6 v7
                           movq mm1, mm0       ; v0 v1 v2 v3 v4 v5 v6 v7
                           punpcklbw mm0, mm0  ; v4 v4 v5 v5 v6 v6 v7 v7
                           //movq mm1, mm0     ; v0 v0 v1 v1 v2 v2 v3 v3
                           punpckhbw mm1, mm1  ;v0 v0 v1 v1 v2 v2 v3 v3
                           movq [edi+8], mm1   ; move to memory v0 v1 v2 and v3
                           sub esi, 8
                           movq [edi], mm0     ; move to memory v4 v5 v6 and v7
                           //sub esi, 4
                           sub edi, 16
                           sub ecx, 8
                           jnz loop1_pass4
                           EMMS
                        }
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
                        sptr --;
                     }
                  }
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 2) << 2);
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub edi, 15
                           sub esi, 3
loop1_pass2:
                           movd mm0, [esi]     ; X X X X v0 v1 v2 v3
                           punpcklbw mm0, mm0  ; v0 v0 v1 v1 v2 v2 v3 v3
                           movq mm1, mm0       ; v0 v0 v1 v1 v2 v2 v3 v3
                           punpcklwd mm0, mm0  ; v2 v2 v2 v2 v3 v3 v3 v3
                           punpckhwd mm1, mm1  ; v0 v0 v0 v0 v1 v1 v1 v1
                           movq [edi], mm0     ; move to memory v2 and v3
                           sub esi, 4
                           movq [edi+8], mm1   ; move to memory v1     and v0
                           sub edi, 16
                           sub ecx, 4
                           jnz loop1_pass2
                           EMMS
                        }
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
                        sptr --;
                     }
                  }
                  else if (width) /* && ((pass == 0) || (pass == 1))) */
                  {
                     int width_mmx = ((width >> 2) << 2);
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub edi, 31
                           sub esi, 3
loop1_pass0:
                           movd mm0, [esi]     ; X X X X v0 v1 v2 v3
                           movq mm1, mm0       ; X X X X v0 v1 v2 v3
                           punpcklbw mm0, mm0  ; v0 v0 v1 v1 v2 v2 v3 v3
                           movq mm2, mm0       ; v0 v0 v1 v1 v2 v2 v3 v3
                           punpcklwd mm0, mm0  ; v2 v2 v2 v2 v3 v3 v3 v3
                           movq mm3, mm0       ; v2 v2 v2 v2 v3 v3 v3 v3
                           punpckldq mm0, mm0  ; v3 v3 v3 v3 v3 v3 v3 v3
                           punpckhdq mm3, mm3  ; v2 v2 v2 v2 v2 v2 v2 v2
                           movq [edi], mm0     ; move to memory v3
                           punpckhwd mm2, mm2  ; v0 v0 v0 v0 v1 v1 v1 v1
                           movq [edi+8], mm3   ; move to memory v2
                           movq mm4, mm2       ; v0 v0 v0 v0 v1 v1 v1 v1
                           punpckldq mm2, mm2  ; v1 v1 v1 v1 v1 v1 v1 v1
                           punpckhdq mm4, mm4  ; v0 v0 v0 v0 v0 v0 v0 v0
                           movq [edi+16], mm2  ; move to memory v1
                           movq [edi+24], mm4  ; move to memory v0
                           sub esi, 4
                           sub edi, 32
                           sub ecx, 4
                           jnz loop1_pass0
                           EMMS
                        }
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
                           *dp-- = *sptr;
                        sptr--;
                     }
                  }
               } /* end of pixel_bytes == 1 */

               else if (pixel_bytes == 2)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 2
                           sub edi, 6
loop2_pass4:
                           movd mm0, [esi]        ; X X X X v1 v0 v3 v2
                           punpcklwd mm0, mm0     ; v1 v0 v1 v0 v3 v2 v3 v2
                           sub esi, 4
                           movq [edi], mm0
                           sub edi, 8
                           sub ecx, 2
                           jnz loop2_pass4
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*2 - 2);            // sign fixed
                     dp -= (width_mmx*4 - 2);            // sign fixed
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
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 2
                           sub edi, 14
loop2_pass2:
                           movd mm0, [esi]        ; X X X X v1 v0 v3 v2
                           punpcklwd mm0, mm0     ; v1 v0 v1 v0 v3 v2 v3 v2
                           movq mm1, mm0          ; v1 v0 v1 v0 v3 v2 v3 v2
                           punpckldq mm0, mm0     ; v3 v2 v3 v2 v3 v2 v3 v2
                           punpckhdq mm1, mm1     ; v1 v0 v1 v0 v1 v0 v1 v0
                           movq [edi], mm0
                           sub esi, 4
                           movq [edi + 8], mm1
                           //sub esi, 4
                           sub edi, 16
                           sub ecx, 2
                           jnz loop2_pass2
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*2 - 2);            // sign fixed
                     dp -= (width_mmx*8 - 2);            // sign fixed
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
                  else if (width) /* && ((pass == 0) || (pass == 1))) */
                  {
                     int width_mmx = ((width >> 1) << 1);
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 2
                           sub edi, 30
loop2_pass0:
                           movd mm0, [esi]        ; X X X X v1 v0 v3 v2
                           punpcklwd mm0, mm0     ; v1 v0 v1 v0 v3 v2 v3 v2
                           movq mm1, mm0          ; v1 v0 v1 v0 v3 v2 v3 v2
                           punpckldq mm0, mm0     ; v3 v2 v3 v2 v3 v2 v3 v2
                           punpckhdq mm1, mm1     ; v1 v0 v1 v0 v1 v0 v1 v0
                           movq [edi], mm0
                           movq [edi + 8], mm0
                           movq [edi + 16], mm1
                           movq [edi + 24], mm1
                           sub esi, 4
                           sub edi, 32
                           sub ecx, 2
                           jnz loop2_pass0
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*2 - 2);            // sign fixed
                     dp -= (width_mmx*16 - 2);            // sign fixed
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

               else if (pixel_bytes == 4)
               {
                  if (((pass == 4) || (pass == 5)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 4
                           sub edi, 12
loop4_pass4:
                           movq mm0, [esi]      ; v3 v2 v1 v0 v7 v6 v5 v4
                           movq mm1, mm0        ; v3 v2 v1 v0 v7 v6 v5 v4
                           punpckldq mm0, mm0   ; v7 v6 v5 v4 v7 v6 v5 v4
                           punpckhdq mm1, mm1   ; v3 v2 v1 v0 v3 v2 v1 v0
                           movq [edi], mm0
                           sub esi, 8
                           movq [edi + 8], mm1
                           sub edi, 16
                           sub ecx, 2
                           jnz loop4_pass4
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*4 - 4);          // sign fixed
                     dp -= (width_mmx*8 - 4);            // sign fixed
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
                  else if (((pass == 2) || (pass == 3)) && width)
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 4
                           sub edi, 28
loop4_pass2:
                           movq mm0, [esi]      ; v3 v2 v1 v0 v7 v6 v5 v4
                           movq mm1, mm0        ; v3 v2 v1 v0 v7 v6 v5 v4
                           punpckldq mm0, mm0   ; v7 v6 v5 v4 v7 v6 v5 v4
                           punpckhdq mm1, mm1   ; v3 v2 v1 v0 v3 v2 v1 v0
                           movq [edi], mm0
                           movq [edi + 8], mm0
                           movq [edi+16], mm1
                           movq [edi + 24], mm1
                           sub esi, 8
                           sub edi, 32
                           sub ecx, 2
                           jnz loop4_pass2
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*4 - 4);            // sign fixed
                     dp -= (width_mmx*16 - 4);            // sign fixed
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
                  else if (width) /* && ((pass == 0) || (pass == 1))) */
                  {
                     int width_mmx = ((width >> 1) << 1) ;
                     width -= width_mmx;
                     if (width_mmx)
                     {
                        _asm
                        {
                           mov esi, sptr
                           mov edi, dp
                           mov ecx, width_mmx
                           sub esi, 4
                           sub edi, 60
loop4_pass0:
                           movq mm0, [esi]        ; v3 v2 v1 v0 v7 v6 v5 v4
                           movq mm1, mm0          ; v3 v2 v1 v0 v7 v6 v5 v4
                           punpckldq mm0, mm0     ; v7 v6 v5 v4 v7 v6 v5 v4
                           punpckhdq mm1, mm1     ; v3 v2 v1 v0 v3 v2 v1 v0
                           movq [edi], mm0
                           movq [edi + 8], mm0
                           movq [edi + 16], mm0
                           movq [edi + 24], mm0
                           movq [edi+32], mm1
                           movq [edi + 40], mm1
                           movq [edi+ 48], mm1
                           sub esi, 8
                           movq [edi + 56], mm1
                           sub edi, 64
                           sub ecx, 2
                           jnz loop4_pass0
                           EMMS
                        }
                     }

                     sptr -= (width_mmx*4 - 4);            // sign fixed
                     dp -= (width_mmx*32 - 4);            // sign fixed
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

               else if (pixel_bytes == 6)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, 6);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, 6);
                        dp -= 6;
                     }
                     sptr -= 6;
                  }
               } /* end of pixel_bytes == 6 */

               else
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr-= pixel_bytes;
                  }
               }
            } /* end of mmx_supported */

            else /* MMX not supported:  use modified C code - takes advantage
                  * of inlining of memcpy for a constant */
            {
               if (pixel_bytes == 1)
               {
                  for (i = width; i; i--)
                  {
                     int j;
                     for (j = 0; j < png_pass_inc[pass]; j++)
                        *dp-- = *sptr;
                     sptr--;
                  }
               }
               else if (pixel_bytes == 3)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr -= pixel_bytes;
                  }
               }
               else if (pixel_bytes == 2)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr -= pixel_bytes;
                  }
               }
               else if (pixel_bytes == 4)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr -= pixel_bytes;
                  }
               }
               else if (pixel_bytes == 6)
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr -= pixel_bytes;
                  }
               }
               else
               {
                  for (i = width; i; i--)
                  {
                     png_byte v[8];
                     int j;
                     png_memcpy(v, sptr, pixel_bytes);
                     for (j = 0; j < png_pass_inc[pass]; j++)
                     {
                        png_memcpy(dp, v, pixel_bytes);
                        dp -= pixel_bytes;
                     }
                     sptr -= pixel_bytes;
                  }
               }

            }
