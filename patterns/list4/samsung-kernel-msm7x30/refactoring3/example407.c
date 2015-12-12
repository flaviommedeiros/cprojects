switch( pMsg->type )
      {
         case SYS_MSG_ID_MC_START:
         {
#if defined( FEATURE_WLAN_NON_INTEGRATED_SOC )
            // save the callback pointer and user data in the context
            // data
            gSysContext.mcStartCB = (sysResponseCback)pMsg->bodyptr;
            gSysContext.mcStartUserData= (v_VOID_t *)pMsg->bodyval;

            // Trigger the CFG download sequence by sending the
            // SIR_HAL_INIT_START_REQ message to the mac module.
            vosStatus = sys_SendHalInitStartReqMsg( pVosContext );
#else
            /* Handling for this message is not needed now so adding 
             *debug print and VOS_ASSERT*/
            VOS_TRACE( VOS_MODULE_ID_SYS, VOS_TRACE_LEVEL_ERROR,
                       " Received SYS_MSG_ID_MC_START message msgType= %d [0x%08lx]",
                       pMsg->type, pMsg->type );
            VOS_ASSERT(0);
#endif
            break;
         }

         case SYS_MSG_ID_MC_STOP:
         {
            VOS_TRACE( VOS_MODULE_ID_SYS, VOS_TRACE_LEVEL_INFO,
                       "Processing SYS MC STOP" );

            // get the HAL context...
            hHal = vos_get_context( VOS_MODULE_ID_PE, pVosContext );
            if (NULL == hHal)
            {
               VOS_TRACE( VOS_MODULE_ID_SYS, VOS_TRACE_LEVEL_ERROR,
                          "%s: Invalid hHal", __FUNCTION__ );
            }
            else
            {
               vosStatus = sme_Stop( hHal, TRUE );
               VOS_ASSERT( VOS_IS_STATUS_SUCCESS( vosStatus ) );

               vosStatus = macStop( hHal, HAL_STOP_TYPE_SYS_DEEP_SLEEP );
               VOS_ASSERT( VOS_IS_STATUS_SUCCESS( vosStatus ) );

               ((sysResponseCback)pMsg->bodyptr)((v_VOID_t *)pMsg->bodyval);

               vosStatus = VOS_STATUS_SUCCESS;
            }
            break;
         }

         // Process MC thread probe.  Just callback to the
         // function that is in the message.
         case SYS_MSG_ID_MC_THR_PROBE:
         {
#if defined( FEATURE_WLAN_NON_INTEGRATED_SOC )
            sysResponseCback callback;

            // Make a callback to the function based on the info
            // in the message (callback is in bodyptr and user
            // data is in bodyval)
            callback = (sysResponseCback)pMsg->bodyptr;

            callback( (v_VOID_t *)pMsg->bodyval );
#else
            /* Handling for this message is not needed now so adding 
             *debug print and VOS_ASSERT*/
            VOS_TRACE( VOS_MODULE_ID_SYS, VOS_TRACE_LEVEL_ERROR,
                       " Received SYS_MSG_ID_MC_THR_PROBE message msgType= %d [0x%08lx]",
                       pMsg->type, pMsg->type );
            VOS_ASSERT(0);
#endif
            break;
         }

         case SYS_MSG_ID_MC_TIMER:
         {
            vos_timer_callback_t timerCB;
            // hummmm... note says...
            // invoke the timer callback and the user data stick
            // into the bodyval; no body to free.    I think this is
            // what that means.
            timerCB = (vos_timer_callback_t)pMsg->bodyptr;

            // make the callback to the timer routine...
            timerCB( (v_VOID_t *)pMsg->bodyval );

            break;
         }
#ifndef WLAN_FTM_STUB
         case SYS_MSG_ID_FTM_RSP:
         {
             WLANFTM_McProcessMsg((v_VOID_t *)pMsg->bodyptr);
             break;
         }
#endif

         default:
         {
            VOS_TRACE( VOS_MODULE_ID_SYS, VOS_TRACE_LEVEL_ERROR,
                       "Unknown message type in sysMcProcessMsg() msgType= %d [0x%08lx]",
                       pMsg->type, pMsg->type );
            break;
        }

      }
