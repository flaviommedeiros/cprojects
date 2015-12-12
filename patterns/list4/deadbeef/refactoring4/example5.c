#ifdef INVALID_ORDERS_END_SONG
if (n != IT_ORDER_SKIP)
#else
					if (n == IT_ORDER_END)
#endif
					{
						sigrenderer->processorder = sigrenderer->restart_position - 1;
					}
