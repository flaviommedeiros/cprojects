#ifndef ENABLE_NLS
if (plain || (len < 256))
#else
    if (len < 256)
#endif
    {
        print_one_paragraph(text, plain, fp);
        return;
    }
