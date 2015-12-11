switch (task_type)
   {
      /* Simulation barrier to redirect processing externally. */
#ifdef EXTERN_COMMAND_LIST_GBI
      case M_GFXTASK:
         if (CFG_HLE_GFX == 0)
            break;

         if (*(int32_t*)(RSP.DMEM + 0xFF0) == 0x00000000)
            break; /* Resident Evil 2, null task pointers */

         if (rsp_info.ProcessDlistList != NULL)
            rsp_info.ProcessDlistList();

         *RSP.SP_STATUS_REG |= 0x00000203;

         if (*RSP.SP_STATUS_REG & 0x00000040) /* SP_STATUS_INTR_BREAK */
         {
            *RSP.MI_INTR_REG |= 0x00000001; /* VR4300 SP interrupt */
            rsp_info.CheckInterrupts();
         }
         if (*RSP.DPC_STATUS_REG & 0x00000002) /* DPC_STATUS_FREEZE */
         {
            /* DPC_CLR_FREEZE */
            *RSP.DPC_STATUS_REG &= ~0x00000002;
         }
         return 0;
#endif
#ifdef EXTERN_COMMAND_LIST_ABI
      case M_AUDTASK:
         if (CFG_HLE_AUD == 0)
            break;

         if (rsp_info.ProcessAlistList != 0)
            rsp_info.ProcessAlistList();

         *RSP.SP_STATUS_REG |= 0x00000203;

         if (*RSP.SP_STATUS_REG & 0x00000040) /* SP_STATUS_INTR_BREAK */
         {
            *RSP.MI_INTR_REG |= 0x00000001; /* VR4300 SP interrupt */
            rsp_info.CheckInterrupts();
         }
         return 0;
#endif
      case M_VIDTASK:
         /* stub */
         break;
      case M_NJPEGTASK:
         /* Zelda, Pokemon, others */
         break;
      case M_NULTASK:
         break;
      case M_HVQMTASK:
         if (rsp_info.ShowCFB != 0)
            rsp_info.ShowCFB(); /* forced FB refresh in case gfx plugin skip */
         break;
   }
