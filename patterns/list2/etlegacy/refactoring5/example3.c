#if 1
if (light->isStatic && light->frustumVBO && light->frustumIBO)
	{
		// render in world space
		backEnd.orientation = backEnd.viewParms.world;
		GL_LoadModelViewMatrix(backEnd.viewParms.world.modelViewMatrix);
		SetUniformMatrix16(UNIFORM_MODELVIEWPROJECTIONMATRIX, GLSTACK_MVPM);

		R_BindVBO(light->frustumVBO);
		R_BindIBO(light->frustumIBO);

		GLSL_VertexAttribsState(ATTR_POSITION);

		tess.numVertexes = light->frustumVerts;
		tess.numIndexes  = light->frustumIndexes;

		Tess_DrawElements();
	}
	else
#endif
	{
		// render in light space
		R_RotateLightForViewParms(light, &backEnd.viewParms, &backEnd.orientation);
		GL_LoadModelViewMatrix(backEnd.orientation.modelViewMatrix);
		SetUniformMatrix16(UNIFORM_MODELVIEWPROJECTIONMATRIX, GLSTACK_MVPM);

		tess.multiDrawPrimitives = 0;
		tess.numIndexes          = 0;
		tess.numVertexes         = 0;

		switch (light->l.rlType)
		{
		case RL_OMNI:
		{
			Tess_AddCube(vec3_origin, light->localBounds[0], light->localBounds[1], colorWhite);

			Tess_UpdateVBOs(ATTR_POSITION | ATTR_COLOR);
			Tess_DrawElements();
			break;
		}
		case RL_PROJ:
		{
			vec3_t farCorners[4];
			vec4_t *frustum = light->localFrustum;

			PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_FAR], farCorners[0]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_FAR], farCorners[1]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_FAR], farCorners[2]);
			PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_FAR], farCorners[3]);

			tess.multiDrawPrimitives = 0;
			tess.numVertexes         = 0;
			tess.numIndexes          = 0;

			if (!VectorCompare(light->l.projStart, vec3_origin))
			{
				vec3_t nearCorners[4];

				// calculate the vertices defining the top area
				PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[0]);
				PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[1]);
				PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[2]);
				PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[3]);

				// draw outer surfaces
				for (j = 0; j < 4; j++)
				{
					Vector4Set(quadVerts[0], nearCorners[j][0], nearCorners[j][1], nearCorners[j][2], 1);
					Vector4Set(quadVerts[1], farCorners[j][0], farCorners[j][1], farCorners[j][2], 1);
					Vector4Set(quadVerts[2], farCorners[(j + 1) % 4][0], farCorners[(j + 1) % 4][1], farCorners[(j + 1) % 4][2], 1);
					Vector4Set(quadVerts[3], nearCorners[(j + 1) % 4][0], nearCorners[(j + 1) % 4][1], nearCorners[(j + 1) % 4][2], 1);
					Tess_AddQuadStamp2(quadVerts, colorCyan);
				}

				// draw far cap
				Vector4Set(quadVerts[0], farCorners[3][0], farCorners[3][1], farCorners[3][2], 1);
				Vector4Set(quadVerts[1], farCorners[2][0], farCorners[2][1], farCorners[2][2], 1);
				Vector4Set(quadVerts[2], farCorners[1][0], farCorners[1][1], farCorners[1][2], 1);
				Vector4Set(quadVerts[3], farCorners[0][0], farCorners[0][1], farCorners[0][2], 1);
				Tess_AddQuadStamp2(quadVerts, colorRed);

				// draw near cap
				Vector4Set(quadVerts[0], nearCorners[0][0], nearCorners[0][1], nearCorners[0][2], 1);
				Vector4Set(quadVerts[1], nearCorners[1][0], nearCorners[1][1], nearCorners[1][2], 1);
				Vector4Set(quadVerts[2], nearCorners[2][0], nearCorners[2][1], nearCorners[2][2], 1);
				Vector4Set(quadVerts[3], nearCorners[3][0], nearCorners[3][1], nearCorners[3][2], 1);
				Tess_AddQuadStamp2(quadVerts, colorGreen);
			}
			else
			{
				vec3_t top;

				// no light_start, just use the top vertex (doesn't need to be mirrored)
				PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], top);

				// draw pyramid
				for (j = 0; j < 4; j++)
				{
					VectorCopy(farCorners[j], tess.xyz[tess.numVertexes]);
					Vector4Copy(colorCyan, tess.colors[tess.numVertexes]);
					tess.indexes[tess.numIndexes++] = tess.numVertexes;
					tess.numVertexes++;

					VectorCopy(farCorners[(j + 1) % 4], tess.xyz[tess.numVertexes]);
					Vector4Copy(colorCyan, tess.colors[tess.numVertexes]);
					tess.indexes[tess.numIndexes++] = tess.numVertexes;
					tess.numVertexes++;

					VectorCopy(top, tess.xyz[tess.numVertexes]);
					Vector4Copy(colorCyan, tess.colors[tess.numVertexes]);
					tess.indexes[tess.numIndexes++] = tess.numVertexes;
					tess.numVertexes++;
				}

				Vector4Set(quadVerts[0], farCorners[3][0], farCorners[3][1], farCorners[3][2], 1);
				Vector4Set(quadVerts[1], farCorners[2][0], farCorners[2][1], farCorners[2][2], 1);
				Vector4Set(quadVerts[2], farCorners[1][0], farCorners[1][1], farCorners[1][2], 1);
				Vector4Set(quadVerts[3], farCorners[0][0], farCorners[0][1], farCorners[0][2], 1);
				Tess_AddQuadStamp2(quadVerts, colorRed);
			}

			Tess_UpdateVBOs(ATTR_POSITION | ATTR_COLOR);
			Tess_DrawElements();
			break;
		}
		default:
			break;
		}
	}
