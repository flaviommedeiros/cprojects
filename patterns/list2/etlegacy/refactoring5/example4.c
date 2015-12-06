#if 1
if (light->isStatic && light->frustumVBO && light->frustumIBO)
				{
					// go back to the world modelview matrix
					backEnd.orientation = backEnd.viewParms.world;
					GL_LoadModelViewMatrix(backEnd.viewParms.world.modelViewMatrix);

					SetUniformMatrix16(UNIFORM_MODELVIEWPROJECTIONMATRIX, GLSTACK_MVPM);

					R_BindVBO(light->frustumVBO);
					R_BindIBO(light->frustumIBO);

					GLSL_VertexAttribsState(ATTR_POSITION);

					tess.numVertexes = light->frustumVerts;
					tess.numIndexes  = light->frustumIndexes;

					Tess_DrawElements();

					tess.multiDrawPrimitives = 0;
					tess.numIndexes          = 0;
					tess.numVertexes         = 0;
				}
				else
#endif
				{
					tess.multiDrawPrimitives = 0;
					tess.numIndexes          = 0;
					tess.numVertexes         = 0;

					switch (light->l.rlType)
					{
					case RL_OMNI:
					case RL_DIRECTIONAL:
					{
#if 1
						// set up the transformation matrix
						R_RotateLightForViewParms(light, &backEnd.viewParms, &backEnd.orientation);

						GL_LoadModelViewMatrix(backEnd.orientation.modelViewMatrix);

						SetUniformMatrix16(UNIFORM_MODELVIEWPROJECTIONMATRIX, GLSTACK_MVPM);

						Tess_AddCube(vec3_origin, light->localBounds[0], light->localBounds[1], lightColor);

						if (!VectorCompare(light->l.center, vec3_origin))
						{
							Tess_AddCube(light->l.center, minSize, maxSize, colorYellow);
						}

						Tess_UpdateVBOs(ATTR_POSITION | ATTR_COLOR);
						Tess_DrawElements();
#else
						matrix_t transform, scale, rot;

						MatrixSetupScale(scale, light->l.radius[0], light->l.radius[1], light->l.radius[2]);
						MatrixMultiplyMOD(light->transformMatrix, scale, transform);

						GL_LoadModelViewMatrix(transform);
						//GL_LoadProjectionMatrix(backEnd.viewParms.projectionMatrix);

						gl_genericShader->SetUniform_ModelViewProjectionMatrix(GLSTACK_MVPM);

						R_BindVBO(tr.unitCubeVBO);
						R_BindIBO(tr.unitCubeIBO);

						GLSL_VertexAttribsState(ATTR_POSITION);

						tess.multiDrawPrimitives = 0;
						tess.numVertexes         = tr.unitCubeVBO->vertexesNum;
						tess.numIndexes          = tr.unitCubeIBO->indexesNum;

						Tess_DrawElements();
#endif
						break;
					}
					case RL_PROJ:
					{
						vec3_t farCorners[4];
						//vec4_t			frustum[6];
						vec4_t *frustum = light->localFrustum;

						// set up the transformation matrix
						R_RotateLightForViewParms(light, &backEnd.viewParms, &backEnd.orientation);
						GL_LoadModelViewMatrix(backEnd.orientation.modelViewMatrix);

						SetUniformMatrix16(UNIFORM_MODELVIEWPROJECTIONMATRIX, GLSTACK_MVPM);

#if 0
						// transform frustum from world space to local space
						for (j = 0; j < 6; j++)
						{
							MatrixTransformPlane(light->transformMatrix, light->localFrustum[j], frustum[j]);
							//Vector4Copy(light->localFrustum[j], frustum[j]);
							//MatrixTransformPlane2(light->viewMatrix, frustum[j]);
						}

						// go back to the world modelview matrix
						backEnd.orientation = backEnd.viewParms.world;
						GL_LoadModelViewMatrix(backEnd.viewParms.world.modelViewMatrix);
						GLSL_SetUniform_ModelViewProjectionMatrix(&tr.genericShader, GLSTACK_MVPM);
#endif

						PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_FAR], farCorners[0]);
						PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_FAR], farCorners[1]);
						PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_FAR], farCorners[2]);
						PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_FAR], farCorners[3]);

						// the planes of the frustum are measured at world 0,0,0 so we have to position the intersection points relative to the light origin
#if 0
						Ren_Print("pyramid farCorners\n");
						for (j = 0; j < 4; j++)
						{
							Ren_Print("(%5.3f, %5.3f, %5.3f)\n", farCorners[j][0], farCorners[j][1], farCorners[j][2]);
						}
#endif

						tess.numVertexes         = 0;
						tess.numIndexes          = 0;
						tess.multiDrawPrimitives = 0;

						if (!VectorCompare(light->l.projStart, vec3_origin))
						{
							vec3_t nearCorners[4];

							// calculate the vertices defining the top area
							PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[0]);
							PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], frustum[FRUSTUM_NEAR], nearCorners[1]);
							PlanesGetIntersectionPoint(frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[2]);
							PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_BOTTOM], frustum[FRUSTUM_NEAR], nearCorners[3]);

#if 0
							Ren_Print("pyramid nearCorners\n");
							for (j = 0; j < 4; j++)
							{
								Ren_Print("(%5.3f, %5.3f, %5.3f)\n", nearCorners[j][0], nearCorners[j][1], nearCorners[j][2]);
							}
#endif

							// draw outer surfaces
							for (j = 0; j < 4; j++)
							{
								Vector4Set(quadVerts[3], nearCorners[j][0], nearCorners[j][1], nearCorners[j][2], 1);
								Vector4Set(quadVerts[2], farCorners[j][0], farCorners[j][1], farCorners[j][2], 1);
								Vector4Set(quadVerts[1], farCorners[(j + 1) % 4][0], farCorners[(j + 1) % 4][1], farCorners[(j + 1) % 4][2], 1);
								Vector4Set(quadVerts[0], nearCorners[(j + 1) % 4][0], nearCorners[(j + 1) % 4][1], nearCorners[(j + 1) % 4][2], 1);
								Tess_AddQuadStamp2(quadVerts, lightColor);
							}

							// draw far cap
							Vector4Set(quadVerts[0], farCorners[0][0], farCorners[0][1], farCorners[0][2], 1);
							Vector4Set(quadVerts[1], farCorners[1][0], farCorners[1][1], farCorners[1][2], 1);
							Vector4Set(quadVerts[2], farCorners[2][0], farCorners[2][1], farCorners[2][2], 1);
							Vector4Set(quadVerts[3], farCorners[3][0], farCorners[3][1], farCorners[3][2], 1);
							Tess_AddQuadStamp2(quadVerts, lightColor);

							// draw near cap
							Vector4Set(quadVerts[3], nearCorners[0][0], nearCorners[0][1], nearCorners[0][2], 1);
							Vector4Set(quadVerts[2], nearCorners[1][0], nearCorners[1][1], nearCorners[1][2], 1);
							Vector4Set(quadVerts[1], nearCorners[2][0], nearCorners[2][1], nearCorners[2][2], 1);
							Vector4Set(quadVerts[0], nearCorners[3][0], nearCorners[3][1], nearCorners[3][2], 1);
							Tess_AddQuadStamp2(quadVerts, lightColor);
						}
						else
						{
							vec3_t top;

							// no light_start, just use the top vertex (doesn't need to be mirrored)
							PlanesGetIntersectionPoint(frustum[FRUSTUM_LEFT], frustum[FRUSTUM_RIGHT], frustum[FRUSTUM_TOP], top);

							// draw pyramid
							for (j = 0; j < 4; j++)
							{
								VectorCopy(top, tess.xyz[tess.numVertexes]);
								Vector4Copy(lightColor, tess.colors[tess.numVertexes]);
								tess.indexes[tess.numIndexes++] = tess.numVertexes;
								tess.numVertexes++;

								VectorCopy(farCorners[(j + 1) % 4], tess.xyz[tess.numVertexes]);
								Vector4Copy(lightColor, tess.colors[tess.numVertexes]);
								tess.indexes[tess.numIndexes++] = tess.numVertexes;
								tess.numVertexes++;

								VectorCopy(farCorners[j], tess.xyz[tess.numVertexes]);
								Vector4Copy(lightColor, tess.colors[tess.numVertexes]);
								tess.indexes[tess.numIndexes++] = tess.numVertexes;
								tess.numVertexes++;
							}

							// draw far cap
							Vector4Set(quadVerts[0], farCorners[0][0], farCorners[0][1], farCorners[0][2], 1);
							Vector4Set(quadVerts[1], farCorners[1][0], farCorners[1][1], farCorners[1][2], 1);
							Vector4Set(quadVerts[2], farCorners[2][0], farCorners[2][1], farCorners[2][2], 1);
							Vector4Set(quadVerts[3], farCorners[3][0], farCorners[3][1], farCorners[3][2], 1);
							Tess_AddQuadStamp2(quadVerts, lightColor);
						}

						// draw light_target
						Tess_AddCube(light->l.projTarget, minSize, maxSize, colorRed);
						Tess_AddCube(light->l.projRight, minSize, maxSize, colorGreen);
						Tess_AddCube(light->l.projUp, minSize, maxSize, colorBlue);

						if (!VectorCompare(light->l.projStart, vec3_origin))
						{
							Tess_AddCube(light->l.projStart, minSize, maxSize, colorYellow);
						}

						if (!VectorCompare(light->l.projEnd, vec3_origin))
						{
							Tess_AddCube(light->l.projEnd, minSize, maxSize, colorMagenta);
						}

						Tess_UpdateVBOs(ATTR_POSITION | ATTR_COLOR);
						Tess_DrawElements();
						break;
					}
					default:
						break;
					}

					tess.multiDrawPrimitives = 0;
					tess.numIndexes          = 0;
					tess.numVertexes         = 0;
				}
