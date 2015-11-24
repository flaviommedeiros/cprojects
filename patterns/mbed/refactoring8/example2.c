class RtosTimer {
public:
    /** Create and Start timer.
      @param   task      name of the timer call back function.
      @param   type      osTimerOnce for one-shot or osTimerPeriodic for periodic behaviour. (default: osTimerPeriodic)
      @param   argument  argument to the timer call back function. (default: NULL)
    */
    RtosTimer(void (*task)(void const *argument),
          os_timer_type type=osTimerPeriodic,
          void *argument=NULL);

    /** Stop the timer.
      @return  status code that indicates the execution status of the function.
    */
    osStatus stop(void);

    /** start a timer.
      @param   millisec  time delay value of the timer.
      @return  status code that indicates the execution status of the function.
    */
    osStatus start(uint32_t millisec);

    ~RtosTimer();

private:
    osTimerId _timer_id;
    osTimerDef_t _timer;
#ifdef CMSIS_OS_RTX
    uint32_t _timer_data[5];
#endif
}
