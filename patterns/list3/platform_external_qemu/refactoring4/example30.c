#if !defined(PNG_1_0_X)
if ((png_ptr->asm_flags & PNG_ASM_FLAG_MMX_READ_COMBINE_ROW)
                /* && mmx_supported */ )
#else
            if (mmx_supported)
#endif
            {
               srcptr = png_ptr->row_buf + 1;
               dstptr = row;
               m = 0x80;
               unmask = ~mask;
               len  = png_ptr->width &~7;  //reduce to multiple of 8
               diff = png_ptr->width & 7;  //amount lost

               _asm
               {
                  movd       mm7, unmask   //load bit pattern
                  psubb      mm6,mm6       //zero mm6
                  punpcklbw  mm7,mm7
                  punpcklwd  mm7,mm7
                  punpckldq  mm7,mm7       //fill register with 8 masks

                  movq       mm0,mask0

                  pand       mm0,mm7       //nonzero if keep byte
                  pcmpeqb    mm0,mm6       //zeros->1s, v versa

                  mov        ecx,len       //load length of line (pixels)
                  mov        esi,srcptr    //load source
                  mov        ebx,dstptr    //load dest
                  cmp        ecx,0         //lcr
                  je         mainloop8end

mainloop8:
                  movq       mm4,[esi]
                  pand       mm4,mm0
                  movq       mm6,mm0
                  pandn      mm6,[ebx]
                  por        mm4,mm6
                  movq       [ebx],mm4

                  add        esi,8         //inc by 8 bytes processed
                  add        ebx,8
                  sub        ecx,8         //dec by 8 pixels processed

                  ja         mainloop8
mainloop8end:

                  mov        ecx,diff
                  cmp        ecx,0
                  jz         end8

                  mov        edx,mask
                  sal        edx,24        //make low byte the high byte

secondloop8:
                  sal        edx,1         //move high bit to CF
                  jnc        skip8         //if CF = 0
                  mov        al,[esi]
                  mov        [ebx],al
skip8:
                  inc        esi
                  inc        ebx

                  dec        ecx
                  jnz        secondloop8
end8:
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
