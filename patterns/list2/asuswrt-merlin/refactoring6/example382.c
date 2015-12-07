if(T3_ASIC_REV(pDevice->ChipRevId) != T3_ASIC_REV_5700 &&
#ifdef INCLUDE_TBI_SUPPORT
            !(pDevice->TbiFlags & ENABLE_TBI_FLAG) &&
#endif
            pDevice->LedCtrl == LED_CTRL_PHY_MODE_2)
        {
            pDevice->PhyIntMode = T3_PHY_INT_MODE_MI_INTERRUPT;
            pDevice->LinkChngMode = T3_LINK_CHNG_MODE_USE_STATUS_REG;
        }
