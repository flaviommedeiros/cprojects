#ifdef ENABLE_DMA
if( lp->use_dma ) {
        wl_send_dma( lp, skb, port );
    }
    else
#endif
    {
        wl_send( lp );
    }
