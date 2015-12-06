#ifdef ALWAYS_BBOX_VS_BBOX
if (model == BOX_MODEL_HANDLE || model == CAPSULE_MODEL_HANDLE)
			{
				tw.sphere.use = qfalse;
				CM_TestInLeaf(&tw, &cmod->leaf);
			}
			else
#elif defined(ALWAYS_CAPSULE_VS_CAPSULE)
			if (model == BOX_MODEL_HANDLE || model == CAPSULE_MODEL_HANDLE)
			{
				CM_TestCapsuleInCapsule(&tw, model);
			}
			else
#else // this is dead code when ALWAYS_BBOX_VS_BBOX or ALWAYS_CAPSULE_VS_CAPSULE are active
			if (model == CAPSULE_MODEL_HANDLE)
			{
				if (tw.sphere.use)
				{
					CM_TestCapsuleInCapsule(&tw, model);
				}
				else
				{
					CM_TestBoundingBoxInCapsule(&tw, model);
				}
			}
			else
#endif
			{
				CM_TestInLeaf(&tw, &cmod->leaf);
			}
