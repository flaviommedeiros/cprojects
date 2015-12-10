#if !defined(PNG_1_0_X)
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_COMBINE_ROW)
                /* && mmx_supported */ )
#else
            if (mmx_supported)
#endif
            {
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

                  pand       mm0,mm7
                  pand       mm1,mm7
                  pand       mm2,mm7

                  pcmpeqb    mm0,mm6
                  pcmpeqb    mm1,mm6
                  pcmpeqb    mm2,mm6

                  mov        ecx,len           //load length of line
                  mov        esi,srcptr        //load source
                  mov        ebx,dstptr        //load dest
                  cmp        ecx,0
                  jz         mainloop24end

mainloop24:
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

                  movq       mm6,[esi+16]
                  pand       mm6,mm2
                  movq       mm4,mm2
                  movq       mm7,[ebx+16]
                  pandn      mm4,mm7
                  por        mm6,mm4
                  movq       [ebx+16],mm6

                  add        esi,24            //inc by 24 bytes processed
                  add        ebx,24
                  sub        ecx,8             //dec by 8 pixels processed

                  ja         mainloop24

mainloop24end:
                  mov        ecx,diff
                  cmp        ecx,0
                  jz         end24

                  mov        edx,mask
                  sal        edx,24            //make low byte the high byte
secondloop24:
                  sal        edx,1             //move high bit to CF
                  jnc        skip24            //if CF = 0
                  mov        ax,[esi]
                  mov        [ebx],ax
                  xor        eax,eax
                  mov        al,[esi+2]
                  mov        [ebx+2],al
skip24:
                  add        esi,3
                  add        ebx,3

                  dec        ecx
                  jnz        secondloop24

end24:
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
