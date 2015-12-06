#if 1
if (!VectorCompare(light->l.center, vec3_origin))
		{
			MatrixTransformPoint(light->transformMatrix, light->l.center, transformed);
			VectorSubtract(transformed, light->l.origin, light->direction);
			VectorNormalize(light->direction);

			VectorMA(light->l.origin, 10000, light->direction, light->origin);
		}
		else
#endif
		{
			vec3_t down = { 0, 0, 1 };

			MatrixTransformPoint(light->transformMatrix, down, transformed);
			VectorSubtract(transformed, light->l.origin, light->direction);
			VectorNormalize(light->direction);

			VectorMA(light->l.origin, 10000, light->direction, light->origin);

			VectorCopy(light->l.origin, light->origin);
		}
