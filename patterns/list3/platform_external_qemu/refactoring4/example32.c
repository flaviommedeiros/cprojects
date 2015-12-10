#if !defined(PNG_1_0_X)
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_COMBINE_ROW)
                /* && mmx_supported */ )
#else
            if (mmx_supported)
#endif
            {
               srcptr = png_ptr->row_buf + 1;
               dstptr = row;

               unmask = ~mask;
               len     = (png_ptr->width)&~7;
               diff = (png_ptr->width)&7;
               _asm
               {
                  movd       mm7, unmask       //load bit pattern
                  psubb      mm6,mm6           //zero mm6
                  punpcklbw  mm7,mm7
                  punpcklwd  mm7,mm7
                  punpckldq  mm7,mm7           //fill register with 8 masks

                  movq       mm0,mask0
                  movq       mm1,mask1
                  movq       mm2,mask2
                  movq       mm3,mask3
                  movq       mm4,mask4
                  movq       mm5,mask5

                  pand       mm0,mm7
                  pand       mm1,mm7
                  pand       mm2,mm7
                  pand       mm3,mm7
                  pand       mm4,mm7
                  pand       mm5,mm7

                  pcmpeqb    mm0,mm6
                  pcmpeqb    mm1,mm6
                  pcmpeqb    mm2,mm6
                  pcmpeqb    mm3,mm6
                  pcmpeqb    mm4,mm6
                  pcmpeqb    mm5,mm6

                  mov        ecx,len           //load length of line
                  mov        esi,srcptr        //load source
                  mov        ebx,dstptr        //load dest

                  cmp        ecx,0
                  jz         mainloop48end

mainloop48:
                  movq       mm7,[esi]
                  pand       mm7,mm0
                  movq       mm6,mm0
                  pandn      mm6,[ebx]
                  por        mm7,mm6
                  movq       [ebx],mm7

                  movq       mm6,[esi+8]
                  pand       mm6,mm1
                  movq       mm7,mm1
                  pandn      mm7,[ebx+8]
                  por        mm6,mm7
                  movq       [ebx+8],mm6

                  movq       mm6,[esi+16]
                  pand       mm6,mm2
                  movq       mm7,mm2
                  pandn      mm7,[ebx+16]
                  por        mm6,mm7
                  movq       [ebx+16],mm6

                  movq       mm7,[esi+24]
                  pand       mm7,mm3
                  movq       mm6,mm3
                  pandn      mm6,[ebx+24]
                  por        mm7,mm6
                  movq       [ebx+24],mm7

                  movq       mm6,[esi+32]
                  pand       mm6,mm4
                  movq       mm7,mm4
                  pandn      mm7,[ebx+32]
                  por        mm6,mm7
                  movq       [ebx+32],mm6

                  movq       mm7,[esi+40]
                  pand       mm7,mm5
                  movq       mm6,mm5
                  pandn      mm6,[ebx+40]
                  por        mm7,mm6
                  movq       [ebx+40],mm7

                  add        esi,48            //inc by 32 bytes processed
                  add        ebx,48
                  sub        ecx,8             //dec by 8 pixels processed

                  ja         mainloop48
mainloop48end:

                  mov        ecx,diff
                  cmp        ecx,0
                  jz         end48

                  mov        edx,mask
                  sal        edx,24            //make low byte the high byte

secondloop48:
                  sal        edx,1             //move high bit to CF
                  jnc        skip48            //if CF = 0
                  mov        eax,[esi]
                  mov        [ebx],eax
                  mov        ax,[esi+4]       // These 2 lines added 20070717
                  mov        [ebx+4],ax       // Glenn R-P
skip48:
                  add        esi,6            // Changed 4 to 6 on these 2
                  add        ebx,6            // lines.  Glenn R-P 20070717

                  dec        ecx
                  jnz        secondloop48

end48:
                  emms
               }
            }
            else /* mmx _not supported - Use modified C routine */
            {
               register unsigned int incr1, initial_val, final_val;
               png_size_t pixel_bytes;
               png_uint_32 i;
               register int disp = png_pass_inc[png_ptr->pass];
               int offset_table[7] = {0, 4, 0, 2, 0, 1, 0};

               pixel_bytes = (png_ptr->row_info.pixel_depth >> 3);
               srcptr = png_ptr->row_buf + 1 + offset_table[png_ptr->pass]*
                  pixel_bytes;
               dstptr = row + offset_table[png_ptr->pass]*pixel_bytes;
               initial_val = offset_table[png_ptr->pass]*pixel_bytes;
               final_val = png_ptr->width*pixel_bytes;
               incr1 = (disp)*pixel_bytes;
               for (i = initial_val; i < final_val; i += incr1)
               {
                  png_memcpy(dstptr, srcptr, pixel_bytes);
                  srcptr += incr1;
                  dstptr += incr1;
               }
            }
