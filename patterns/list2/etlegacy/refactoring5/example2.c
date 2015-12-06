#if 1
if (!VectorCompare(light->l.projStart, vec3_origin))
		{
			vec3_t nearCorners[4];

			// calculate the vertices defining the top area
			PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[0]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[1]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[2]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[3]);

			for (j = 0; j < 4; j++)
			{
				// outer quad
				R_AddEdgeToLightScissor(light, nearCorners[j], farCorners[j]);
				R_AddEdgeToLightScissor(light, farCorners[j], farCorners[(j + 1) % 4]);
				R_AddEdgeToLightScissor(light, farCorners[(j + 1) % 4], nearCorners[(j + 1) % 4]);
				R_AddEdgeToLightScissor(light, nearCorners[(j + 1) % 4], nearCorners[j]);

				// far cap
				R_AddEdgeToLightScissor(light, farCorners[j], farCorners[(j + 1) % 4]);

				// near cap
				R_AddEdgeToLightScissor(light, nearCorners[j], nearCorners[(j + 1) % 4]);
			}
		}
		else
#endif
		{
			vec3_t top;

			// no light_start, just use the top vertex (doesn't need to be mirrored)
			PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], top);

			for (j = 0; j < 4; j++)
			{
				R_AddEdgeToLightScissor(light, farCorners[j], farCorners[(j + 1) % 4]);
				R_AddEdgeToLightScissor(light, top, farCorners[j]);
			}
		}
