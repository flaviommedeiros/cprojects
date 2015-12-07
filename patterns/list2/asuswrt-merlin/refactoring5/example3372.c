#ifdef BCM_NIC_SEND_BD
if (pDevice->Flags & NIC_SEND_BD_FLAG)
        {
            pTmpSendBd = pSendBd = &NicSendBdArr[0];
        }
        else
#endif
        {
            pTmpSendBd = pSendBd = &pDevice->pSendBdVirt[Idx];
        }
