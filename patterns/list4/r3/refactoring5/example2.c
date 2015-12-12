#ifndef HAS_SMART_CONSOLE
if (Term_IO)
			total = Read_Line(Term_IO, req->data, len);
		else
#endif
			total = read(Std_Inp, req->data, len);
