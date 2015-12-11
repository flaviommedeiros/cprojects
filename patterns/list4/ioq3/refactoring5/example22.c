#ifdef DEBUG_EVAL
if (integer)
		{
			Log_Write("operator %s, value1 = %d", PunctuationFromNum(source->scriptstack, o->operator), v1->intvalue);
			if (v2) Log_Write("value2 = %d", v2->intvalue);
		} //end if
		else
		{
			Log_Write("operator %s, value1 = %f", PunctuationFromNum(source->scriptstack, o->operator), v1->floatvalue);
			if (v2) Log_Write("value2 = %f", v2->floatvalue);
		}
