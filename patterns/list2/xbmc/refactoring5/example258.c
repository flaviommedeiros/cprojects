#ifndef STBI_NO_STDIO
if (img_file)
      fseek(img_file, n, SEEK_CUR);
   else
#endif
      img_buffer += n;
