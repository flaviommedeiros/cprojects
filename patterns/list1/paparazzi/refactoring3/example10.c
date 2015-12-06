switch (actuator_no) {
#ifdef SERVO_0
      case 0: ActuatorSet(0, actuator_value); break;
#endif
#ifdef SERVO_1
      case 1: ActuatorSet(1, actuator_value); break;
#endif
#ifdef SERVO_2
      case 2: ActuatorSet(2, actuator_value); break;
#endif
#ifdef SERVO_3
      case 3: ActuatorSet(3, actuator_value); break;
#endif
#ifdef SERVO_4
      case 4: ActuatorSet(4, actuator_value); break;
#endif
#ifdef SERVO_5
      case 5: ActuatorSet(5, actuator_value); break;
#endif
#ifdef SERVO_6
      case 6: ActuatorSet(6, actuator_value); break;
#endif
#ifdef SERVO_7
      case 7: ActuatorSet(7, actuator_value); break;
#endif
#ifdef SERVO_8
      case 8: ActuatorSet(8, actuator_value); break;
#endif
      default: break;
    }
