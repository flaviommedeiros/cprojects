#ifdef isnanf
if (isnanf(da->data.f32[i]))
#else
			if (isnan(da->data.f32[i]))
#endif
				return i + 1;
