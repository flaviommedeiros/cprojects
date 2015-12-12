#if defined (PDP15)
if ((api_act & (API_ML0|API_ML1|API_ML2|API_ML3)) == 0)
#endif
            api_act = api_act | API_ML4;
