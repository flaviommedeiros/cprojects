#ifndef STBI_NO_STDIO
if (img_file)
            {
               if (fread(idata+ioff,1,c.length,img_file) != c.length) return e("outofdata","Corrupt PNG");
            }
            else
            #endif
            {
               memcpy(idata+ioff, img_buffer, c.length);
               img_buffer += c.length;
            }
