#ifndef HAS_SMART_CONSOLE
if (Term_IO)
            total = Read_Line(Term_IO, s_cast(req->common.data), len);
        else
#endif
            total = read(Std_Inp, req->common.data, len);
