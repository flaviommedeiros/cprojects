#ifdef PRINTER_SUPPORT
if(!NT_STATUS_IS_OK(status))
#endif
		{
			tevent_req_nterror(req, status);
			return tevent_req_post(req, ev);
		}
