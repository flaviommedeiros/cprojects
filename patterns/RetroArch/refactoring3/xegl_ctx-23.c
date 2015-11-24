/*  RetroArch - A frontend for libretro.
*  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
*  Copyright (C) 2011-2015 - Daniel De Matteis
* 
*  RetroArch is free software: you can redistribute it and/or modify it under the terms
*  of the GNU General Public License as published by the Free Software Found-
*  ation, either version 3 of the License, or (at your option) any later version.
*
*  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
*  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
*  PURPOSE.  See the GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License along with RetroArch.
*  If not, see <http://www.gnu.org/licenses/>.
*/

/* X/EGL context. Mostly used for testing GLES code paths. */

#include <stdint.h>

#include "../../driver.h"
#include "../common/egl_common.h"
#include "../common/gl_common.h"
#include "../common/x11_common.h"

#ifndef EGL_OPENGL_ES3_BIT_KHR
#define EGL_OPENGL_ES3_BIT_KHR 0x0040
#endif

static unsigned g_screen;

static XF86VidModeModeInfo g_desktop_mode;
static bool g_should_reset_mode;

static unsigned g_major;
static unsigned g_minor;

static int egl_nul_handler(Display *dpy, XErrorEvent *event)
{
   (void)dpy;
   (void)event;
   return 0;
}

static void gfx_ctx_xegl_destroy(void *data)
{
   x11_input_ctx_destroy();
   egl_destroy(data);

   if (g_x11_win)
   {
      /* Save last used monitor for later. */
#ifdef HAVE_XINERAMA
      XWindowAttributes target;
      Window child;

      int x = 0, y = 0;
      XGetWindowAttributes(g_x11_dpy, g_x11_win, &target);
      XTranslateCoordinates(g_x11_dpy, g_x11_win, RootWindow(g_x11_dpy, DefaultScreen(g_x11_dpy)),
            target.x, target.y, &x, &y, &child);

      g_screen = x11_get_xinerama_monitor(g_x11_dpy, x, y,
            target.width, target.height);

      RARCH_LOG("[X/EGL]: Saved monitor #%u.\n", g_screen);
#endif

      x11_window_destroy(false);
   }

   x11_colormap_destroy();

   if (g_should_reset_mode)
   {
      x11_exit_fullscreen(g_x11_dpy, &g_desktop_mode);
      g_should_reset_mode = false;
   }

   /* Do not close g_x11_dpy. We'll keep one for the entire application 
    * lifecycle to work-around nVidia EGL limitations.
    */
}

static void gfx_ctx_xegl_set_resize(void *data,
   unsigned width, unsigned height)
{
   (void)data;
   (void)width;
   (void)height;
}

#define XEGL_ATTRIBS_BASE \
EGL_SURFACE_TYPE,    EGL_WINDOW_BIT, \
EGL_RED_SIZE,        1, \
EGL_GREEN_SIZE,      1, \
EGL_BLUE_SIZE,       1, \
EGL_ALPHA_SIZE,      0, \
EGL_DEPTH_SIZE,      0

static bool gfx_ctx_xegl_init(void *data)
{
   static const EGLint egl_attribs_gl[] = {
      XEGL_ATTRIBS_BASE,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
      EGL_NONE,
   };

   static const EGLint egl_attribs_gles[] = {
      XEGL_ATTRIBS_BASE,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
      EGL_NONE,
   };

#ifdef EGL_KHR_create_context
   static const EGLint egl_attribs_gles3[] = {
      XEGL_ATTRIBS_BASE,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
      EGL_NONE,
   };
#endif

   static const EGLint egl_attribs_vg[] = {
      XEGL_ATTRIBS_BASE,
      EGL_RENDERABLE_TYPE, EGL_OPENVG_BIT,
      EGL_NONE,
   };

   const EGLint *attrib_ptr;
   EGLint major, minor;
   EGLint n;

   if (g_egl_inited)
      return false;

   XInitThreads();

   switch (g_egl_api)
   {
      case GFX_CTX_OPENGL_API:
         attrib_ptr = egl_attribs_gl;
         break;
      case GFX_CTX_OPENGL_ES_API:
#ifdef EGL_KHR_create_context
         if (g_major >= 3)
            attrib_ptr = egl_attribs_gles3;
         else
#endif
            attrib_ptr = egl_attribs_gles;
         break;
      case GFX_CTX_OPENVG_API:
         attrib_ptr = egl_attribs_vg;
         break;
      default:
         attrib_ptr = NULL;
   }

   if (!x11_connect())
      goto error;

   if (!egl_init_context((EGLNativeDisplayType)g_x11_dpy,
            &major, &minor, &n, attrib_ptr))
   {
      egl_report_error();
      goto error;
   }

   if (n == 0 || !g_egl_config)
   {
      RARCH_ERR("[X/EGL]: No EGL configurations available.\n");
      goto error;
   }

   return true;

error:
   gfx_ctx_xegl_destroy(data);
   return false;
}

static EGLint *xegl_fill_attribs(EGLint *attr)
{
   switch (g_egl_api)
   {
#ifdef EGL_KHR_create_context
      case GFX_CTX_OPENGL_API:
         {
            const struct retro_hw_render_callback *hw_render =
               (const struct retro_hw_render_callback*)video_driver_callback();
            unsigned version = g_major * 1000 + g_minor;
            bool core        = version >= 3001;
#ifdef GL_DEBUG
            bool debug = true;
#else
            bool debug       = hw_render->debug_context;
#endif

            if (core)
            {
               *attr++ = EGL_CONTEXT_MAJOR_VERSION_KHR;
               *attr++ = g_major;
               *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
               *attr++ = g_minor;

               /* Technically, we don't have core/compat until 3.2.
                * Version 3.1 is either compat or not depending 
                * on GL_ARB_compatibility.
                */
               if (version >= 3002)
               {
                  *attr++ = EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR;
                  *attr++ = EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR;
               }
            }

            if (debug)
            {
               *attr++ = EGL_CONTEXT_FLAGS_KHR;
               *attr++ = EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR;
            }

            break;
         }
#endif

      case GFX_CTX_OPENGL_ES_API:
         /* Same as EGL_CONTEXT_MAJOR_VERSION. */
         *attr++ = EGL_CONTEXT_CLIENT_VERSION;
         *attr++ = g_major ? (EGLint)g_major : 2;
#ifdef EGL_KHR_create_context
         if (g_minor > 0)
         {
            *attr++ = EGL_CONTEXT_MINOR_VERSION_KHR;
            *attr++ = g_minor;
         }
#endif
         break;

      default:
         break;
   }

   *attr = EGL_NONE;
   return attr;
}

static bool gfx_ctx_xegl_set_video_mode(void *data,
   unsigned width, unsigned height,
   bool fullscreen)
{
   XEvent event;
   EGLint egl_attribs[16];
   EGLint *attr;
   EGLint vid, num_visuals;
   bool windowed_full;
   bool true_full = false;
   int x_off = 0;
   int y_off = 0;
   XVisualInfo temp = {0};
   XSetWindowAttributes swa = {0};
   XVisualInfo *vi = NULL;
   driver_t *driver     = driver_get_ptr();
   settings_t *settings = config_get_ptr();

   int (*old_handler)(Display*, XErrorEvent*) = NULL;

   x11_install_sighandlers();

   windowed_full = settings->video.windowed_fullscreen;

   attr = egl_attribs;
   attr = xegl_fill_attribs(attr);

   if (!eglGetConfigAttrib(g_egl_dpy, g_egl_config, EGL_NATIVE_VISUAL_ID, &vid))
      goto error;

   temp.visualid = vid;

   vi = XGetVisualInfo(g_x11_dpy, VisualIDMask, &temp, &num_visuals);
   if (!vi)
      goto error;

   swa.colormap = g_x11_cmap = XCreateColormap(g_x11_dpy, RootWindow(g_x11_dpy, vi->screen),
         vi->visual, AllocNone);
   swa.event_mask = StructureNotifyMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | KeyReleaseMask;
   swa.override_redirect = fullscreen ? True : False;

   if (fullscreen && !windowed_full)
   {
      if (x11_enter_fullscreen(g_x11_dpy, width, height, &g_desktop_mode))
      {
         g_should_reset_mode = true;
         true_full = true;
      }
      else
         RARCH_ERR("[X/EGL]: Entering true fullscreen failed. Will attempt windowed mode.\n");
   }

   if (settings->video.monitor_index)
      g_screen = settings->video.monitor_index - 1;

#ifdef HAVE_XINERAMA
   if (fullscreen || g_screen != 0)
   {
      unsigned new_width  = width;
      unsigned new_height = height;

      if (x11_get_xinerama_coord(g_x11_dpy, g_screen, &x_off, &y_off, &new_width, &new_height))
         RARCH_LOG("[X/EGL]: Using Xinerama on screen #%u.\n", g_screen);
      else
         RARCH_LOG("[X/EGL]: Xinerama is not active on screen.\n");

      if (fullscreen)
      {
         width  = new_width;
         height = new_height;
      }
   }
#endif

   RARCH_LOG("[X/EGL]: X = %d, Y = %d, W = %u, H = %u.\n",
         x_off, y_off, width, height);

   g_x11_win = XCreateWindow(g_x11_dpy, RootWindow(g_x11_dpy, vi->screen),
         x_off, y_off, width, height, 0,
         vi->depth, InputOutput, vi->visual, 
         CWBorderPixel | CWColormap | CWEventMask | (true_full ? CWOverrideRedirect : 0), &swa);
   XSetWindowBackground(g_x11_dpy, g_x11_win, 0);

   if (!egl_create_context((attr != egl_attribs) ? egl_attribs : NULL))
   {
      egl_report_error();
      goto error;
   }

   if (!egl_create_surface((EGLNativeWindowType)g_x11_win))
      goto error;

   x11_set_window_attr(g_x11_dpy, g_x11_win);

   if (fullscreen)
      x11_show_mouse(g_x11_dpy, g_x11_win, false);

   if (true_full)
   {
      RARCH_LOG("[X/EGL]: Using true fullscreen.\n");
      XMapRaised(g_x11_dpy, g_x11_win);
   }
   else if (fullscreen) 
   {
      /* We attempted true fullscreen, but failed.
       * Attempt using windowed fullscreen. */
      XMapRaised(g_x11_dpy, g_x11_win);
      RARCH_LOG("[X/EGL]: Using windowed fullscreen.\n");

      /* We have to move the window to the screen we 
       * want to go fullscreen on first.
       * x_off and y_off usually get ignored in XCreateWindow().
       */
      x11_move_window(g_x11_dpy, g_x11_win, x_off, y_off, width, height);
      x11_windowed_fullscreen(g_x11_dpy, g_x11_win);
   }
   else
   {
      XMapWindow(g_x11_dpy, g_x11_win);

      /* If we want to map the window on a different screen, 
       * we'll have to do it by force.
       *
       * Otherwise, we should try to let the window manager sort it out.
       * x_off and y_off usually get ignored in XCreateWindow().
       */
      if (g_screen)
         x11_move_window(g_x11_dpy, g_x11_win, x_off, y_off, width, height);
   }

   x11_event_queue_check(&event);
   x11_install_quit_atom();

   egl_set_swap_interval(data, g_interval);

   /* This can blow up on some drivers. It's not fatal, 
    * so override errors for this call.
    */
   old_handler = XSetErrorHandler(egl_nul_handler);
   XSetInputFocus(g_x11_dpy, g_x11_win, RevertToNone, CurrentTime);
   XSync(g_x11_dpy, False);
   XSetErrorHandler(old_handler);

   XFree(vi);
   g_egl_inited    = true;

   if (!x11_input_ctx_new(true_full))
      goto error;

   return true;

error:
   if (vi)
      XFree(vi);

   gfx_ctx_xegl_destroy(data);
   return false;
}


static void gfx_ctx_xegl_input_driver(void *data,
   const input_driver_t **input, void **input_data)
{
   void *xinput = input_x.init();

   (void)data;

   *input       = xinput ? &input_x : NULL;
   *input_data  = xinput;
}

static bool gfx_ctx_xegl_has_focus(void *data)
{
   if (!g_egl_inited)
      return false;

   return x11_has_focus(data);
}

static bool gfx_ctx_xegl_suppress_screensaver(void *data, bool enable)
{
   driver_t *driver = driver_get_ptr();

   (void)data;
   (void)enable;

   if (driver->display_type != RARCH_DISPLAY_X11)
      return false;

   x11_suspend_screensaver(driver->video_window);

   return true;
}

static bool gfx_ctx_xegl_has_windowed(void *data)
{
   (void)data;

   /* TODO - verify if this has windowed mode or not. */
   return true;
}

static bool gfx_ctx_xegl_bind_api(void *data,
   enum gfx_ctx_api api, unsigned major, unsigned minor)
{
   (void)data;

   g_major   = major;
   g_minor   = minor;
   g_egl_api = api;

   switch (api)
   {
      case GFX_CTX_OPENGL_API:
#ifndef EGL_KHR_create_context
         if ((major * 1000 + minor) >= 3001)
            return false;
#endif
         return eglBindAPI(EGL_OPENGL_API);
      case GFX_CTX_OPENGL_ES_API:
#ifndef EGL_KHR_create_context
         if (major >= 3)
            return false;
#endif
         return eglBindAPI(EGL_OPENGL_ES_API);
      case GFX_CTX_OPENVG_API:
         return eglBindAPI(EGL_OPENVG_API);
      default:
         break;
   }

   return false;
}

static void gfx_ctx_xegl_show_mouse(void *data, bool state)
{
   (void)data;
   x11_show_mouse(g_x11_dpy, g_x11_win, state);
}

const gfx_ctx_driver_t gfx_ctx_x_egl =
{
   gfx_ctx_xegl_init,
   gfx_ctx_xegl_destroy,
   gfx_ctx_xegl_bind_api,
   egl_set_swap_interval,
   gfx_ctx_xegl_set_video_mode,
   x11_get_video_size,
   NULL, /* get_video_output_size */
   NULL, /* get_video_output_prev */
   NULL, /* get_video_output_next */
   x11_get_metrics,
   NULL,
   x11_update_window_title,
   x11_check_window,
   gfx_ctx_xegl_set_resize,
   gfx_ctx_xegl_has_focus,
   gfx_ctx_xegl_suppress_screensaver,
   gfx_ctx_xegl_has_windowed,
   egl_swap_buffers,
   gfx_ctx_xegl_input_driver,
   egl_get_proc_address,
   NULL,
   NULL,
   gfx_ctx_xegl_show_mouse,
   "x-egl",
   egl_bind_hw_render,
};
