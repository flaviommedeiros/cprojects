#ifdef BCM_NIC_SEND_BD
if (pDevice->Flags & NIC_SEND_BD_FLAG)
    {
        pSendBd = &pDevice->pSendBdVirt[StartIdx];
        pShadowSendBd = &pDevice->ShadowSendBd[StartIdx];

        while (StartIdx != Idx)
        {
            LM_UINT32 Value32;

            if ((Value32 = pTmpSendBd->HostAddr.High) !=
                pShadowSendBd->HostAddr.High)
            {
                MM_MEMWRITEL(&(pSendBd->HostAddr.High), Value32);
                pShadowSendBd->HostAddr.High = Value32;
            }

            MM_MEMWRITEL(&(pSendBd->HostAddr.Low), pTmpSendBd->HostAddr.Low);

            if ((Value32 = pTmpSendBd->u1.Len_Flags) !=
                pShadowSendBd->u1.Len_Flags)
            {
                MM_MEMWRITEL(&(pSendBd->u1.Len_Flags), Value32);
                pShadowSendBd->u1.Len_Flags = Value32;
            }

            if (pPacket->Flags & SND_BD_FLAG_VLAN_TAG)
            {
                MM_MEMWRITEL(&(pSendBd->u2.VlanTag), pTmpSendBd->u2.VlanTag);
            }

            StartIdx = (StartIdx + 1) & T3_SEND_RCB_ENTRY_COUNT_MASK;
            if (StartIdx == 0)
            {
                pSendBd = &pDevice->pSendBdVirt[0];
                pShadowSendBd = &pDevice->ShadowSendBd[0];
            }
            else
            {
                pSendBd++;
                pShadowSendBd++;
            }
            pTmpSendBd++;
        }
        MM_WMB();
        MB_REG_WR(pDevice, Mailbox.SendNicProdIdx[0].Low, Idx);

        if(T3_CHIP_REV(pDevice->ChipRevId) == T3_CHIP_REV_5700_BX)
        {
            MB_REG_WR(pDevice, Mailbox.SendNicProdIdx[0].Low, Idx);
        }
        if (pDevice->Flags & FLUSH_POSTED_WRITE_FLAG)
        {
            MB_REG_RD(pDevice, Mailbox.SendNicProdIdx[0].Low);
        }
         else
        {
            MM_MMIOWB();
        }	
    }
    else
#endif
    {
        MM_WMB();
        MB_REG_WR(pDevice, Mailbox.SendHostProdIdx[0].Low, Idx);

        if(T3_CHIP_REV(pDevice->ChipRevId) == T3_CHIP_REV_5700_BX)
        {
            MB_REG_WR(pDevice, Mailbox.SendHostProdIdx[0].Low, Idx);
        }
        if (pDevice->Flags & FLUSH_POSTED_WRITE_FLAG)
        {
            MB_REG_RD(pDevice, Mailbox.SendHostProdIdx[0].Low);
        }
        else
        {
            MM_MMIOWB();
        }	
    }
