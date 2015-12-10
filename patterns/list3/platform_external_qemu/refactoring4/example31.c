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

                  pand       mm0,mm7
                  pand       mm1,mm7

                  pcmpeqb    mm0,mm6
                  pcmpeqb    mm1,mm6

                  mov        ecx,len           //load length of line
                  mov        esi,srcptr        //load source
                  mov        ebx,dstptr        //load dest
                  cmp        ecx,0             //lcr
                  jz         mainloop16end

mainloop16:
                  movq       mm4,[esi]
                  pand       mm4,mm0
                  movq       mm6,mm0
                  movq       mm7,[ebx]
                  pandn      mm6,mm7
                  por        mm4,mm6
                  movq       [ebx],mm4

                  movq       mm5,[esi+8]
                  pand       mm5,mm1
                  movq       mm7,mm1
                  movq       mm6,[ebx+8]
                  pandn      mm7,mm6
                  por        mm5,mm7
                  movq       [ebx+8],mm5

                  add        esi,16            //inc by 16 bytes processed
                  add        ebx,16
                  sub        ecx,8             //dec by 8 pixels processed

                  ja         mainloop16

mainloop16end:
                  mov        ecx,diff
                  cmp        ecx,0
                  jz         end16

                  mov        edx,mask
                  sal        edx,24            //make low byte the high byte
secondloop16:
                  sal        edx,1             //move high bit to CF
                  jnc        skip16            //if CF = 0
                  mov        ax,[esi]
                  mov        [ebx],ax
skip16:
                  add        esi,2
                  add        ebx,2

                  dec        ecx
                  jnz        secondloop16
end16:
                  emms
               }
            }
            else /* mmx not supported - use modified C routine */
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
