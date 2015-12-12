#ifdef USE_DMA
if (req->req.length < 4 &&
				req->req.length == req->req.actual)
#else
			if (req->req.length == req->req.actual)
#endif
				_nbu2ss_ep_done(ep, req, result);
