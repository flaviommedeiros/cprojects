static
VOID
s_nsBulkOutIoCompleteWrite(
    IN struct urb *urb
    )
{
    PSDevice            pDevice;
    NTSTATUS            status;
    CONTEXT_TYPE        ContextType;
    ULONG               ulBufLen;
    PUSB_SEND_CONTEXT   pContext;


    DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"---->s_nsBulkOutIoCompleteWrite\n");
    //
    // The context given to IoSetCompletionRoutine is an USB_CONTEXT struct
    //
    pContext = (PUSB_SEND_CONTEXT) urb->context;
    ASSERT( NULL != pContext );

    pDevice = pContext->pDevice;
    ContextType = pContext->Type;
    ulBufLen = pContext->uBufLen;

    if (!netif_device_present(pDevice->dev))
	    return;

   //
    // Perform various IRP, URB, and buffer 'sanity checks'
    //

    status = urb->status;
    //we should have failed, succeeded, or cancelled, but NOT be pending
    STAvUpdateUSBCounter(&pDevice->scStatistic.USB_BulkOutStat, status);

    if(status == STATUS_SUCCESS) {
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"Write %d bytes\n",(int)ulBufLen);
        pDevice->ulBulkOutBytesWrite += ulBufLen;
        pDevice->ulBulkOutContCRCError = 0;
	//2007-0115-06<Add>by MikeLiu
           #ifdef TxInSleep
             pDevice->nTxDataTimeCout = 0;
           #endif

    } else {
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"BULK Out failed %d\n", status);
        pDevice->ulBulkOutError++;
    }

//    pDevice->ulCheckForHangCount = 0;
//    pDevice->pPendingBulkOutContext = NULL;

    if ( CONTEXT_DATA_PACKET == ContextType ) {
        // Indicate to the protocol the status of the sent packet and return
        // ownership of the packet.
	    if (pContext->pPacket != NULL) {
	        dev_kfree_skb_irq(pContext->pPacket);
	        pContext->pPacket = NULL;
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"tx  %d bytes\n",(int)ulBufLen);
	    }

        pDevice->dev->trans_start = jiffies;


        if (status == STATUS_SUCCESS) {
            pDevice->packetsSent++;
        }
        else {
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"Send USB error! [%08xh]\n", status);
            pDevice->packetsSentDropped++;
        }

    }
    if (pDevice->bLinkPass == TRUE) {
        if (netif_queue_stopped(pDevice->dev))
            netif_wake_queue(pDevice->dev);
    }
    pContext->bBoolInUse = FALSE;

    return;
}
