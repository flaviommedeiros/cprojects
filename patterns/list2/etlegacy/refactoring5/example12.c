#ifdef ALWAYS_BBOX_VS_BBOX
if (model == BOX_MODEL_HANDLE || model == CAPSULE_MODEL_HANDLE)
			{
				tw.sphere.use = qfalse;
				CM_TraceThroughLeaf(&tw, &cmod->leaf);
			}
			else
#elif defined(ALWAYS_CAPSULE_VS_CAPSULE)
			if (model == BOX_MODEL_HANDLE || model == CAPSULE_MODEL_HANDLE)
			{
				CM_TraceCapsuleThroughCapsule(&tw, model);
			}
			else
#else // this is dead code when ALWAYS_BBOX_VS_BBOX or ALWAYS_CAPSULE_VS_CAPSULE are active
			if (model == CAPSULE_MODEL_HANDLE)
			{
				if (tw.sphere.use)
				{
					CM_TraceCapsuleThroughCapsule(&tw, model);
				}
				else
				{
					CM_TraceBoundingBoxThroughCapsule(&tw, model);
				}
			}
			else
#endif
			{
				CM_TraceThroughLeaf(&tw, &cmod->leaf);
			}
