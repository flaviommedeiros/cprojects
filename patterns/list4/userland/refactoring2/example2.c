#ifndef __RASPBERRYPI__
if(renderWidth != w || renderHeight != h)
#endif
	{
		float clearColor[4] = {1,1,1,1};
		float scale = w / (tigerMaxX - tigerMinX);

		eglSwapBuffers(egldisplay, eglsurface);	//force EGL to recognize resize

		vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
		vgClear(0, 0, w, h);

		vgLoadIdentity();
#ifdef __RASPBERRYPI__
                vgTranslate(w * 0.5f, h * 0.5f);
                vgRotate(rotateN);
                vgTranslate(-w * 0.5f, -h * 0.5f);
#endif
		vgScale(scale, scale);
		vgTranslate(-tigerMinX, -tigerMinY + 0.5f * (h / scale - (tigerMaxY - tigerMinY)));

		PS_render(tiger);
		assert(vgGetError() == VG_NO_ERROR);

		renderWidth = w;
		renderHeight = h;
	}
