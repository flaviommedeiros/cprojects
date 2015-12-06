#ifdef BARO_AIRSPEED_PRESENT
if(airspeedData.BaroConnected==BAROAIRSPEED_BAROCONNECTED_TRUE){ //Check if there is an airspeed sensors present...
				//Calculate error and error integral
				float airspeedErr=v_air_GPS - airspeed_tas_baro;
				airspeedErrInt+=airspeedErr * delT;
				
				//Saturate integral component at 5 m/s
				airspeedErrInt = airspeedErrInt >  (5.0f / GPS_AIRSPEED_BIAS_KI) ?  (5.0f / GPS_AIRSPEED_BIAS_KI) : airspeedErrInt;
				airspeedErrInt = airspeedErrInt < -(5.0f / GPS_AIRSPEED_BIAS_KI) ? -(5.0f / GPS_AIRSPEED_BIAS_KI) : airspeedErrInt;
							
				//There's already an airspeed sensor, so instead correct it for bias with P correction. The I correction happened earlier in the function.
				airspeedData.TrueAirspeed = airspeed_tas_baro + airspeedErr * GPS_AIRSPEED_BIAS_KP;
				
				
				/* Note: 
				      This would be a good place to change the airspeed calibration, so that it matches the GPS computed values. However,
				      this might be a bad idea, as their are two degrees of freedom here: temperature and sensor calibration. I don't 
				      know how to control for temperature bias.
				 */
			}
			else
 #endif
			{
				//...there's no airspeed sensor, so everything comes from GPS. In this
				//case, filter the airspeed for smoother output
				float alpha=gpsSamplePeriod_ms/(gpsSamplePeriod_ms + GPS_AIRSPEED_TIME_CONSTANT_MS); //Low pass filter.
				airspeedData.TrueAirspeed=v_air_GPS*(alpha) + airspeedData.TrueAirspeed*(1.0f-alpha);
				
				//Calculate calibrated airspeed from GPS, since we're not getting it from a discrete airspeed sensor
				int16_t groundTemperature_10;
				float groundTemperature;
				float positionActual_Down;

				PositionActualDownGet(&positionActual_Down);
				HomeLocationGroundTemperatureGet(&groundTemperature_10); // Gets tenths of degrees C
				groundTemperature = groundTemperature_10/10; // Convert into degrees C
				groundTemperature -= BARO_TEMPERATURE_OFFSET; //Do this just because we suspect that the board heats up relative to its surroundings. THIS IS BAD(tm)

				struct AirParameters air_STP = initialize_air_structure();
				air_STP.air_temperature_at_surface = groundTemperature + CELSIUS2KELVIN;

				airspeedData.CalibratedAirspeed = tas2cas(airspeedData.TrueAirspeed, -positionActual_Down, &air_STP);
			}
