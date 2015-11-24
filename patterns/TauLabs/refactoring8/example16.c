static void i2c_adapter_inject_event(struct pios_i2c_adapter *i2c_adapter, enum i2c_adapter_event event)
{
	PIOS_IRQ_Disable();

#if defined(PIOS_I2C_DIAGNOSTICS)	
	i2c_adapter->i2c_state_event_history[i2c_adapter->i2c_state_event_history_pointer] = event;
	i2c_adapter->i2c_state_event_history_pointer = (i2c_adapter->i2c_state_event_history_pointer + 1) % I2C_LOG_DEPTH;

	i2c_adapter->i2c_state_history[i2c_adapter->i2c_state_history_pointer] = i2c_adapter->curr_state;
	i2c_adapter->i2c_state_history_pointer = (i2c_adapter->i2c_state_history_pointer + 1) % I2C_LOG_DEPTH;
	
	if (i2c_adapter_transitions[i2c_adapter->curr_state].next_state[event] == I2C_STATE_FSM_FAULT)
		i2c_adapter_log_fault(i2c_adapter, PIOS_I2C_ERROR_FSM);
#endif	
	/* 
	 * Move to the next state
	 *
	 * This is done prior to calling the new state's entry function to 
	 * guarantee that the entry function never depends on the previous
	 * state.  This way, it cannot ever know what the previous state was.
	 */
	enum i2c_adapter_state prev_state = i2c_adapter->curr_state;
	if (prev_state) ;

	i2c_adapter->curr_state = i2c_adapter_transitions[i2c_adapter->curr_state].next_state[event];

	/* Call the entry function (if any) for the next state. */
	if (i2c_adapter_transitions[i2c_adapter->curr_state].entry_fn) {
		i2c_adapter_transitions[i2c_adapter->curr_state].entry_fn(i2c_adapter);
	}

	/* Process any AUTO transitions in the FSM */
	i2c_adapter_process_auto(i2c_adapter);

	PIOS_IRQ_Enable();
}
