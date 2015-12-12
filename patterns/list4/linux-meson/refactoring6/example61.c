if( ((pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod + pmlmepriv->LinkDetectInfo.NumTxOkInPeriod) > 8 ) ||
#ifdef CONFIG_LPS_SLOW_TRANSITION			
			(pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 2) 
#else //CONFIG_LPS_SLOW_TRANSITION
			(pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod > 4) 
#endif //CONFIG_LPS_SLOW_TRANSITION
			)
		{
#ifdef DBG_RX_COUNTER_DUMP
			if( padapter->dump_rx_cnt_mode & DUMP_DRV_TRX_COUNTER_DATA)
				DBG_871X("(-)Tx = %d, Rx = %d \n",pmlmepriv->LinkDetectInfo.NumTxOkInPeriod,pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod);
#endif	
			bEnterPS= _FALSE;
#ifdef CONFIG_LPS_SLOW_TRANSITION
			if(bBusyTraffic == _TRUE)
			{
				if(pmlmepriv->LinkDetectInfo.TrafficTransitionCount <= 4)
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 4;

				pmlmepriv->LinkDetectInfo.TrafficTransitionCount++;

				//DBG_871X("Set TrafficTransitionCount to %d\n", pmlmepriv->LinkDetectInfo.TrafficTransitionCount);
			
				if(pmlmepriv->LinkDetectInfo.TrafficTransitionCount > 30/*TrafficTransitionLevel*/)
				{
					pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 30;
				}	
			}
#endif //CONFIG_LPS_SLOW_TRANSITION
	
		}
		else
		{
#ifdef DBG_RX_COUNTER_DUMP		
			if( padapter->dump_rx_cnt_mode & DUMP_DRV_TRX_COUNTER_DATA)
				DBG_871X("(+)Tx = %d, Rx = %d \n",pmlmepriv->LinkDetectInfo.NumTxOkInPeriod,pmlmepriv->LinkDetectInfo.NumRxUnicastOkInPeriod);
#endif			
#ifdef CONFIG_LPS_SLOW_TRANSITION
			if(pmlmepriv->LinkDetectInfo.TrafficTransitionCount>=2)
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount -=2;
			else
				pmlmepriv->LinkDetectInfo.TrafficTransitionCount = 0;

			if(pmlmepriv->LinkDetectInfo.TrafficTransitionCount == 0)
				bEnterPS= _TRUE;
#else //CONFIG_LPS_SLOW_TRANSITION
				bEnterPS= _TRUE;
#endif //CONFIG_LPS_SLOW_TRANSITION
		}
