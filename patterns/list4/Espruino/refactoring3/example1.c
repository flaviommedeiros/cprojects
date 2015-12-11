switch (task->type) {
      case UET_SET: {
        int j;
        for (j=0;j<UTILTIMERTASK_PIN_COUNT;j++) {
          if (task->data.set.pins[j] == PIN_UNDEFINED) break;
          jshPinSetValue(task->data.set.pins[j], (task->data.set.value >> j)&1);
        }
      } break;
      case UET_EXECUTE:
        executeFn = task->data.execute;
        break;
#ifndef SAVE_ON_FLASH
      case UET_READ_SHORT: {
        if (!task->data.buffer.var) break;
        int v = jshPinAnalogFast(task->data.buffer.pin);
        *jstUtilTimerInterruptHandlerByte(task) = (unsigned char)v;  // LSB first
        jstUtilTimerInterruptHandlerNextByte(task);
        *jstUtilTimerInterruptHandlerByte(task) = (unsigned char)(v >> 8);
        jstUtilTimerInterruptHandlerNextByte(task);
        break;
      }
      case UET_READ_BYTE: {
        if (!task->data.buffer.var) break;
        *jstUtilTimerInterruptHandlerByte(task) = (unsigned char)(jshPinAnalogFast(task->data.buffer.pin) >> 8);
        jstUtilTimerInterruptHandlerNextByte(task);
        break;
      }
      case UET_WRITE_SHORT:
      case UET_WRITE_BYTE: {
        if (!task->data.buffer.var) break;
        // get data
        int sum;
        if (task->type == UET_WRITE_SHORT) {
          sum = *jstUtilTimerInterruptHandlerByte(task);  // LSB first
          jstUtilTimerInterruptHandlerNextByte(task);
        } else {
          sum = 0;
        }
        sum |=  (unsigned short)(*jstUtilTimerInterruptHandlerByte(task) << 8);
        jstUtilTimerInterruptHandlerNextByte(task);
        task->data.buffer.currentValue = (unsigned short)sum;
        // now search for other tasks writing to this pin... (polyphony)
        int t = (utilTimerTasksTail+1) & (UTILTIMERTASK_TASKS-1);
        while (t!=utilTimerTasksHead) {
          if (UET_IS_BUFFER_WRITE_EVENT(utilTimerTasks[t].type))
            sum += ((int)(unsigned int)utilTimerTasks[t].data.buffer.currentValue) - 32768;
          t = (t+1) & (UTILTIMERTASK_TASKS-1);
        }
        // saturate
        if (sum<0) sum = 0;
        if (sum>65535) sum = 65535;
        // and output...
        jshSetOutputValue(task->data.buffer.pinFunction, sum);
        break;
      }
#endif
      case UET_WAKEUP: // we've already done our job by waking the device up
      default: break;
      }
