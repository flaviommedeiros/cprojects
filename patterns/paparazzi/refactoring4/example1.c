#ifndef SITL
if (ACCEL_FLOAT_OF_BFP(accel_meas_body.x)  < (nav_catapult_acceleration_threshold * 9.81))
#else
      if (launch != 1)
#endif
      {
        nav_catapult_launch = 0;
      }
