if (
#if JSH_PORTA_OFFSET!=0
        pin>=JSH_PORTA_OFFSET &&
#endif
        pin<JSH_PORTA_OFFSET+JSH_PORTA_COUNT) {
      result[0]='A';
      itostr(pin-JSH_PORTA_OFFSET,&result[1],10);
    } else if (pin>=JSH_PORTB_OFFSET && pin<JSH_PORTB_OFFSET+JSH_PORTB_COUNT) {
      result[0]='B';
      itostr(pin-JSH_PORTB_OFFSET,&result[1],10);
    } else if (pin>=JSH_PORTC_OFFSET && pin<JSH_PORTC_OFFSET+JSH_PORTC_COUNT) {
      result[0]='C';
      itostr(pin-JSH_PORTC_OFFSET,&result[1],10);
    } else if (pin>=JSH_PORTD_OFFSET && pin<JSH_PORTD_OFFSET+JSH_PORTD_COUNT) {
      result[0]='D';
      itostr(pin-JSH_PORTD_OFFSET,&result[1],10);
#if JSH_PORTE_OFFSET!=-1
    } else if (pin>=JSH_PORTE_OFFSET && pin<JSH_PORTE_OFFSET+JSH_PORTE_COUNT) {
      result[0]='E';
      itostr(pin-JSH_PORTE_OFFSET,&result[1],10);
#endif
#if JSH_PORTF_OFFSET!=-1
    } else if (pin>=JSH_PORTF_OFFSET && pin<JSH_PORTF_OFFSET+JSH_PORTF_COUNT) {
      result[0]='F';
      itostr(pin-JSH_PORTF_OFFSET,&result[1],10);
#endif
#if JSH_PORTG_OFFSET!=-1
    } else if (pin>=JSH_PORTG_OFFSET && pin<JSH_PORTG_OFFSET+JSH_PORTG_COUNT) {
      result[0]='G';
      itostr(pin-JSH_PORTG_OFFSET,&result[1],10);
#endif
#if JSH_PORTH_OFFSET!=-1
    } else if (pin>=JSH_PORTH_OFFSET && pin<JSH_PORTH_OFFSET+JSH_PORTH_COUNT) {
      result[0]='H';
      itostr(pin-JSH_PORTH_OFFSET,&result[1],10);
#endif
#endif
    } else {
      strncpy(result, "undefined", 8);
    }
