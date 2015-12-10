switch (msg)
  {
    case WM_CHAR:  // Keypress notification
#ifdef DEBUG_BUILD
//      printf("WM_CHAR\n"); fflush(stdout);
#endif
      pVideo = WinQueryWindowPtr(hwnd, 0);
      if (pVideo)
      {
        /*
        // We skip repeated keys:
        if (CHARMSG(&msg)->cRepeat>1)
        {
#ifdef DEBUG_BUILD
//          printf("Repeated key (%d), skipping...\n", CHARMSG(&msg)->cRepeat); fflush(stdout);
#endif
          return (MRESULT) TRUE;
        }
        */

        // If it's not repeated, then let's see if its pressed or released!
        if (SHORT1FROMMP(mp1) & KC_KEYUP)
        {
          // A key has been released
          SDL_keysym keysym;

#ifdef DEBUG_BUILD
//          printf("WM_CHAR, keyup, code is [0x%0x]\n", CHAR4FROMMP(mp1)); // HW scan code
#endif

          // One problem is with F1, which gets only the keyup message because
          // it is a system key.
          // So, when we get keyup message, we simulate keydown too!
          // UPDATE:
          //  This problem should be solved now, that the accelerator keys are
          //  disabled for this window!
          /*
          if (SHORT2FROMMP(mp2)==VK_F1)
          {
            SDL_PrivateKeyboard(SDL_PRESSED, TranslateKey(SHORT2FROMMP(mp2), // VK_ code
                                                           SHORT1FROMMP(mp2), // Character code
                                                           CHAR4FROMMP(mp1),  // HW Scan code
                                                           &keysym,0));
          }*/

          SDL_PrivateKeyboard(SDL_RELEASED, TranslateKey(SHORT2FROMMP(mp2), // VK_ code
                                                         SHORT1FROMMP(mp2), // Character code
                                                         CHAR4FROMMP(mp1),  // HW Scan code
                                                         &keysym,0));
          
        } else
        {
          // A key has been pressed
          SDL_keysym keysym;

#ifdef DEBUG_BUILD
//          printf("WM_CHAR, keydown, code is [0x%0x]\n", CHAR4FROMMP(mp1)); // HW scan code
#endif
          // Check for fastkeys: ALT+HOME to toggle FS mode
          //                     ALT+END to close app
          if ((SHORT1FROMMP(mp1) & KC_ALT) &&
              (SHORT2FROMMP(mp2) == VK_HOME))
          {
#ifdef DEBUG_BUILD
            printf(" Pressed ALT+HOME!\n"); fflush(stdout);
#endif
            // Only switch between fullscreen and back if it's not
            // a resizable mode!
            if (
                (!pVideo->hidden->pSDLSurface) ||
                ((pVideo->hidden->pSDLSurface)
                 && ((pVideo->hidden->pSDLSurface->flags & SDL_RESIZABLE)==0)
                )
               )
              FSLib_ToggleFSMode(hwnd, !FSLib_QueryFSMode(hwnd));
#ifdef DEBUG_BUILD
            else
              printf(" Resizable mode, so discarding ALT+HOME!\n"); fflush(stdout);
#endif
          } else
          if ((SHORT1FROMMP(mp1) & KC_ALT) &&
              (SHORT2FROMMP(mp2) == VK_END))
          {
#ifdef DEBUG_BUILD
            printf(" Pressed ALT+END!\n"); fflush(stdout);
#endif
            // Close window, and get out of loop!
            // Also send event to SDL application, but we won't
            // wait for it to be processed!
            SDL_PrivateQuit();
            WinPostMsg(hwnd, WM_QUIT, 0, 0);
          } else
          {
            
            SDL_PrivateKeyboard(SDL_PRESSED, TranslateKey(SHORT2FROMMP(mp2), // VK_ code
                                                          SHORT1FROMMP(mp2), // Character code
                                                          CHAR4FROMMP(mp1),  // HW Scan code
                                                          &keysym,1));
            
          }
        }
      }
      return (MRESULT) TRUE;

    case WM_TRANSLATEACCEL:
      {
        PQMSG pqmsg;
        pqmsg = (PQMSG) mp1;
        if (mp1)
        {
          if (pqmsg->msg == WM_CHAR)
          {
            // WM_CHAR message!
            // Let's filter the ALT keypress and all other acceleration keys!
            return (MRESULT) FALSE;
          }
        }
        break; // Default processing (pass to parent until frame control)
      }

    case WM_PAINT:  // Window redraw!
#ifdef DEBUG_BUILD
      printf("WM_PAINT (0x%x)\n", hwnd); fflush(stdout);
#endif
      ps = WinBeginPaint(hwnd,0,&rcl);
      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        if (!pVideo->hidden->pSDLSurface)
        {
          RECTL rclRect;
          // So, don't blit now!
#ifdef DEBUG_BUILD
          printf("WM_PAINT : Skipping blit while resizing (Pre!)!\n"); fflush(stdout);
#endif
          WinQueryWindowRect(hwnd, &rclRect);
          // Fill with black
          WinFillRect(ps, &rclRect, CLR_BLACK);
        } else
        {
          if (DosRequestMutexSem(pVideo->hidden->hmtxUseSrcBuffer, 1000)==NO_ERROR)
          {
            int iTop, iLeft, iWidth, iHeight;
            int iXScaleError, iYScaleError;
            int iXScaleError2, iYScaleError2;
            SWP swp;
            
            // Re-blit the modified area!
            // For this, we have to calculate the points, scaled!
            WinQueryWindowPos(hwnd, &swp);
#ifdef DEBUG_BUILD
            printf("WM_PAINT : WinSize: %d %d, BufSize: %d %d\n",
                   swp.cx,
                   swp.cy,
                   pVideo->hidden->SrcBufferDesc.uiXResolution,
                   pVideo->hidden->SrcBufferDesc.uiYResolution
                  );
            fflush(stdout);
#endif

#ifndef RESIZE_EVEN_IF_RESIZABLE
            // But only blit if the window is not resizable, or if
            // the window is resizable and the source buffer size is the
            // same as the destination buffer size!
            if ((!pVideo->hidden->pSDLSurface) ||
                ((pVideo->hidden->pSDLSurface) &&
                 (pVideo->hidden->pSDLSurface->flags & SDL_RESIZABLE) &&
                 ((swp.cx != pVideo->hidden->SrcBufferDesc.uiXResolution) ||
                  (swp.cy != pVideo->hidden->SrcBufferDesc.uiYResolution)
                 ) &&
                 (!FSLib_QueryFSMode(hwnd))
                )
               )
            {
              RECTL rclRect;
              // Resizable surface and in resizing!
              // So, don't blit now!
#ifdef DEBUG_BUILD
              printf("WM_PAINT : Skipping blit while resizing!\n"); fflush(stdout);
#endif
              WinQueryWindowRect(hwnd, &rclRect);
              // Fill with black
              WinFillRect(ps, &rclRect, CLR_BLACK);
            } else
#endif
            {
  
              iXScaleError = (pVideo->hidden->SrcBufferDesc.uiXResolution-1) / swp.cx;
              iYScaleError = (pVideo->hidden->SrcBufferDesc.uiYResolution-1) / swp.cy;
              if (iXScaleError<0) iXScaleError = 0;
              if (iYScaleError<0) iYScaleError = 0;
              iXScaleError2 = (swp.cx-1)/(pVideo->hidden->SrcBufferDesc.uiXResolution);
              iYScaleError2 = (swp.cy-1)/(pVideo->hidden->SrcBufferDesc.uiYResolution);
              if (iXScaleError2<0) iXScaleError2 = 0;
              if (iYScaleError2<0) iYScaleError2 = 0;
      
              iTop = (swp.cy - rcl.yTop) * pVideo->hidden->SrcBufferDesc.uiYResolution / swp.cy - iYScaleError;
              iLeft = rcl.xLeft * pVideo->hidden->SrcBufferDesc.uiXResolution / swp.cx - iXScaleError;
              iWidth = ((rcl.xRight-rcl.xLeft) * pVideo->hidden->SrcBufferDesc.uiXResolution + swp.cx-1)
                / swp.cx + 2*iXScaleError;
              iHeight = ((rcl.yTop-rcl.yBottom) * pVideo->hidden->SrcBufferDesc.uiYResolution + swp.cy-1)
                / swp.cy + 2*iYScaleError;
      
              iWidth+=iXScaleError2;
              iHeight+=iYScaleError2;
      
              if (iTop<0) iTop = 0;
              if (iLeft<0) iLeft = 0;
              if (iTop+iHeight>pVideo->hidden->SrcBufferDesc.uiYResolution) iHeight = pVideo->hidden->SrcBufferDesc.uiYResolution-iTop;
              if (iLeft+iWidth>pVideo->hidden->SrcBufferDesc.uiXResolution) iWidth = pVideo->hidden->SrcBufferDesc.uiXResolution-iLeft;
    
#ifdef DEBUG_BUILD
              printf("WM_PAINT : BitBlt: %d %d -> %d %d (Buf %d x %d)\n",
                     iTop, iLeft, iWidth, iHeight,
                     pVideo->hidden->SrcBufferDesc.uiXResolution,
                     pVideo->hidden->SrcBufferDesc.uiYResolution
                    );
              fflush(stdout);
#endif
                    
              FSLIB_BITBLT(hwnd, pVideo->hidden->pchSrcBuffer, iTop, iLeft, iWidth, iHeight);
            }
  
            DosReleaseMutexSem(pVideo->hidden->hmtxUseSrcBuffer);
          }
        }
      }
#ifdef DEBUG_BUILD
      else
      {
        printf("WM_PAINT : No pVideo!\n"); fflush(stdout);
      }
#endif
      WinEndPaint(ps);
#ifdef DEBUG_BUILD
      printf("WM_PAINT : Done.\n");
      fflush(stdout);
#endif
      return 0;

    case WM_SIZE:
      {
#ifdef DEBUG_BUILD
        printf("WM_SIZE : (%d %d)\n",
               SHORT1FROMMP(mp2), SHORT2FROMMP(mp2)); fflush(stdout);
#endif
        iWindowSizeX = SHORT1FROMMP(mp2);
        iWindowSizeY = SHORT2FROMMP(mp2);
        bWindowResized = 1;

        // Make sure the window will be redrawn
        WinInvalidateRegion(hwnd, NULL, TRUE);
      }
      break;

    case WM_FSLIBNOTIFICATION:
#ifdef DEBUG_BUILD
        printf("WM_FSLIBNOTIFICATION\n"); fflush(stdout);
#endif
      if ((int)mp1 == FSLN_TOGGLEFSMODE)
      {
        // FS mode changed, reblit image!
        pVideo = FSLib_GetUserParm(hwnd);
        if (pVideo)
        {
          if (!pVideo->hidden->pSDLSurface)
          {
            // Resizable surface and in resizing!
            // So, don't blit now!
#ifdef DEBUG_BUILD
            printf("WM_FSLIBNOTIFICATION : Can not blit if there is no surface, doing nothing.\n"); fflush(stdout);
#endif
          } else
          {
            if (DosRequestMutexSem(pVideo->hidden->hmtxUseSrcBuffer, 1000)==NO_ERROR)
            {
              if (pVideo->hidden->pSDLSurface)
              {
#ifndef RESIZE_EVEN_IF_RESIZABLE
                SWP swp;

                // But only blit if the window is not resizable, or if
                // the window is resizable and the source buffer size is the
                // same as the destination buffer size!
                WinQueryWindowPos(hwnd, &swp);
                if ((!pVideo->hidden->pSDLSurface) ||
                    (
                     (pVideo->hidden->pSDLSurface) &&
                     (pVideo->hidden->pSDLSurface->flags & SDL_RESIZABLE) &&
                     ((swp.cx != pVideo->hidden->SrcBufferDesc.uiXResolution) ||
                      (swp.cy != pVideo->hidden->SrcBufferDesc.uiYResolution)
                     ) &&
                     (!FSLib_QueryFSMode(hwnd))
                    )
                   )
                {
                  // Resizable surface and in resizing!
                  // So, don't blit now!
#ifdef DEBUG_BUILD
                  printf("WM_FSLIBNOTIFICATION : Cannot blit while resizing, doing nothing.\n"); fflush(stdout);
#endif
                } else
#endif
                {
#ifdef DEBUG_BUILD
                  printf("WM_FSLIBNOTIFICATION : Blitting!\n"); fflush(stdout);
#endif
                  FSLIB_BITBLT(hwnd, pVideo->hidden->pchSrcBuffer,
                               0, 0,
                               pVideo->hidden->SrcBufferDesc.uiXResolution,
                               pVideo->hidden->SrcBufferDesc.uiYResolution);
                }
              }
#ifdef DEBUG_BUILD
              else
                printf("WM_FSLIBNOTIFICATION : No public surface!\n"); fflush(stdout);
#endif
  
              DosReleaseMutexSem(pVideo->hidden->hmtxUseSrcBuffer);
            }
          }
        }
      }
      return (MPARAM) 1;

    case WM_ACTIVATE:
#ifdef DEBUG_BUILD
      printf("WM_ACTIVATE\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        pVideo->hidden->fInFocus = (int) mp1;
        if (pVideo->hidden->fInFocus)
        {
          // Went into focus
          if ((pVideo->hidden->iMouseVisible) && (!bMouseCaptured))
            WinSetPointer(HWND_DESKTOP, WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW, FALSE));
          else
            WinSetPointer(HWND_DESKTOP, NULL);

          if (bMouseCapturable)
          {
            // Re-capture the mouse, if we captured it before!
            WinSetCapture(HWND_DESKTOP, hwnd);
            bMouseCaptured = 1;
            {
              SWP swpClient;
              POINTL ptl;
              // Center the mouse to the middle of the window!
              WinQueryWindowPos(pVideo->hidden->hwndClient, &swpClient);
              ptl.x = 0; ptl.y = 0;
              WinMapWindowPoints(pVideo->hidden->hwndClient, HWND_DESKTOP, &ptl, 1);
              pVideo->hidden->iSkipWMMOUSEMOVE++; /* Don't take next WM_MOUSEMOVE into account!  */
              WinSetPointerPos(HWND_DESKTOP,
                               ptl.x + swpClient.cx/2,
                               ptl.y + swpClient.cy/2);
            }
          }
        } else
        {
          // Went out of focus
          WinSetPointer(HWND_DESKTOP, WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW, FALSE));

          if (bMouseCaptured)
          {
            // Release the mouse
            WinSetCapture(HWND_DESKTOP, hwnd);
            bMouseCaptured = 0;
          }
        }
      }
#ifdef DEBUG_BUILD
      printf("WM_ACTIVATE done\n"); fflush(stdout);
#endif

      break;

    case WM_BUTTON1DOWN:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON1DOWN\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        SDL_PrivateMouseButton(SDL_PRESSED,
                               SDL_BUTTON_LEFT,
                               0, 0); // Don't report mouse movement!

        if (bMouseCapturable)
        {
          // We should capture the mouse!
          if (!bMouseCaptured)
          {
            WinSetCapture(HWND_DESKTOP, hwnd);
            WinSetPointer(HWND_DESKTOP, NULL);
            bMouseCaptured = 1;
            {
              SWP swpClient;
              POINTL ptl;
              // Center the mouse to the middle of the window!
              WinQueryWindowPos(pVideo->hidden->hwndClient, &swpClient);
              ptl.x = 0; ptl.y = 0;
              WinMapWindowPoints(pVideo->hidden->hwndClient, HWND_DESKTOP, &ptl, 1);
              pVideo->hidden->iSkipWMMOUSEMOVE++; /* Don't take next WM_MOUSEMOVE into account!  */
              WinSetPointerPos(HWND_DESKTOP,
                               ptl.x + swpClient.cx/2,
                               ptl.y + swpClient.cy/2);
            }
          }
        }
      }
      break;
    case WM_BUTTON1UP:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON1UP\n"); fflush(stdout);
#endif
      SDL_PrivateMouseButton(SDL_RELEASED,
                             SDL_BUTTON_LEFT,
                             0, 0); // Don't report mouse movement!
      break;
    case WM_BUTTON2DOWN:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON2DOWN\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        SDL_PrivateMouseButton(SDL_PRESSED,
                               SDL_BUTTON_RIGHT,
                               0, 0); // Don't report mouse movement!

        if (bMouseCapturable)
        {
          // We should capture the mouse!
          if (!bMouseCaptured)
          {
            WinSetCapture(HWND_DESKTOP, hwnd);
            WinSetPointer(HWND_DESKTOP, NULL);
            bMouseCaptured = 1;
            {
              SWP swpClient;
              POINTL ptl;
              // Center the mouse to the middle of the window!
              WinQueryWindowPos(pVideo->hidden->hwndClient, &swpClient);
              ptl.x = 0; ptl.y = 0;
              WinMapWindowPoints(pVideo->hidden->hwndClient, HWND_DESKTOP, &ptl, 1);
              pVideo->hidden->iSkipWMMOUSEMOVE++; /* Don't take next WM_MOUSEMOVE into account!  */
              WinSetPointerPos(HWND_DESKTOP,
                               ptl.x + swpClient.cx/2,
                               ptl.y + swpClient.cy/2);
            }
          }
        }

      }
      break;
    case WM_BUTTON2UP:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON2UP\n"); fflush(stdout);
#endif
      SDL_PrivateMouseButton(SDL_RELEASED,
                             SDL_BUTTON_RIGHT,
                             0, 0); // Don't report mouse movement!
      break;
    case WM_BUTTON3DOWN:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON3DOWN\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        SDL_PrivateMouseButton(SDL_PRESSED,
                               SDL_BUTTON_MIDDLE,
                               0, 0); // Don't report mouse movement!
        
        if (bMouseCapturable)
        {
          // We should capture the mouse!
          if (!bMouseCaptured)
          {
            WinSetCapture(HWND_DESKTOP, hwnd);
            WinSetPointer(HWND_DESKTOP, NULL);
            bMouseCaptured = 1;
            {
              SWP swpClient;
              POINTL ptl;
              // Center the mouse to the middle of the window!
              WinQueryWindowPos(pVideo->hidden->hwndClient, &swpClient);
              ptl.x = 0; ptl.y = 0;
              WinMapWindowPoints(pVideo->hidden->hwndClient, HWND_DESKTOP, &ptl, 1);
              pVideo->hidden->iSkipWMMOUSEMOVE++; /* Don't take next WM_MOUSEMOVE into account!  */
              WinSetPointerPos(HWND_DESKTOP,
                               ptl.x + swpClient.cx/2,
                               ptl.y + swpClient.cy/2);
            }
          }
        }
      }
      break;
    case WM_BUTTON3UP:
#ifdef DEBUG_BUILD
      printf("WM_BUTTON3UP\n"); fflush(stdout);
#endif
      SDL_PrivateMouseButton(SDL_RELEASED,
                             SDL_BUTTON_MIDDLE,
                             0, 0); // Don't report mouse movement!
      break;
    case WM_MOUSEMOVE:
#ifdef DEBUG_BUILD
//      printf("WM_MOUSEMOVE\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        if (pVideo->hidden->iSkipWMMOUSEMOVE)
        {
          pVideo->hidden->iSkipWMMOUSEMOVE--;
        } else
        {
          POINTS *ppts = (POINTS *) (&mp1);
          POINTL ptl;

          if (bMouseCaptured)
          {
            SWP swpClient;

            WinQueryWindowPos(pVideo->hidden->hwndClient, &swpClient);

            // Send relative mouse position, and re-center the mouse
            // Reposition the mouse to the center of the screen/window
            SDL_PrivateMouseMotion(0, // Buttons not changed
                                   1, // Relative position
                                   ppts->x - (swpClient.cx/2),
                                   (swpClient.cy/2) - ppts->y);

            ptl.x = 0; ptl.y = 0;
            WinMapWindowPoints(pVideo->hidden->hwndClient, HWND_DESKTOP, &ptl, 1);
            pVideo->hidden->iSkipWMMOUSEMOVE++; /* Don't take next WM_MOUSEMOVE into account!  */
            // Center the mouse to the middle of the window!
            WinSetPointerPos(HWND_DESKTOP,
                             ptl.x + swpClient.cx/2,
                             ptl.y + swpClient.cy/2);
          } else
          {
            CONVERTMOUSEPOSITION();

            // Send absolute mouse position
            SDL_PrivateMouseMotion(0, // Buttons not changed
                                   0, // Absolute position
                                   ppts->x,
                                   ppts->y);
          }
        }
        if ((pVideo->hidden->iMouseVisible) && (!bMouseCaptured))
        {
#ifdef DEBUG_BUILD
//          printf("WM_MOUSEMOVE : ptr = %p\n", hptrGlobalPointer); fflush(stdout);
#endif

          if (hptrGlobalPointer)
            WinSetPointer(HWND_DESKTOP, hptrGlobalPointer);
          else
            WinSetPointer(HWND_DESKTOP, WinQuerySysPointer(HWND_DESKTOP, SPTR_ARROW, FALSE));
        }
        else
        {
          WinSetPointer(HWND_DESKTOP, NULL);
        }
      }
#ifdef DEBUG_BUILD
//      printf("WM_MOUSEMOVE done\n"); fflush(stdout);
#endif

      return (MRESULT) FALSE;
    case WM_CLOSE: // Window close
#ifdef DEBUG_BUILD
      printf("WM_CLOSE\n"); fflush(stdout);
#endif

      pVideo = FSLib_GetUserParm(hwnd);
      if (pVideo)
      {
        // Send Quit message to the SDL application!
        SDL_PrivateQuit();
        return 0;
      }
      break;

#ifdef BITBLT_IN_WINMESSAGEPROC
    case WM_UPDATERECTSREQUEST:
      pVideo = FSLib_GetUserParm(hwnd);
      if ((pVideo) && (pVideo->hidden->pSDLSurface))
      {
        if (DosRequestMutexSem(pVideo->hidden->hmtxUseSrcBuffer, SEM_INDEFINITE_WAIT)==NO_ERROR)
        {
          int numrects;
          SDL_Rect *rects;
          int i;
          SWP swp;

          numrects = (int) mp1;
          rects = (SDL_Rect *) mp2;

          WinQueryWindowPos(hwnd, &swp);
#ifndef RESIZE_EVEN_IF_RESIZABLE
          if ((!pVideo->hidden->pSDLSurface) ||
              (
               (pVideo->hidden->pSDLSurface) &&
               (pVideo->hidden->pSDLSurface->flags & SDL_RESIZABLE) &&
               ((swp.cx != pVideo->hidden->SrcBufferDesc.uiXResolution) ||
                (swp.cy != pVideo->hidden->SrcBufferDesc.uiYResolution)
               ) &&
               (!FSLib_QueryFSMode(hwnd))
              )
             )
          {
            // Resizable surface and in resizing!
            // So, don't blit now!
#ifdef DEBUG_BUILD
            printf("[WM_UPDATERECTSREQUEST] : Skipping blit while resizing!\n"); fflush(stdout);
#endif
          } else
#endif
          {
#ifdef DEBUG_BUILD
            printf("[WM_UPDATERECTSREQUEST] : Blitting!\n"); fflush(stdout);
#endif
          
            // Blit the changed areas
            for (i=0; i<numrects; i++)
              FSLIB_BITBLT(hwnd, pVideo->hidden->pchSrcBuffer,
                           rects[i].y, rects[i].x, rects[i].w, rects[i].h);
          }
          DosReleaseMutexSem(pVideo->hidden->hmtxUseSrcBuffer);
        }
      }
      return 0;
#endif

    default:
#ifdef DEBUG_BUILD
      printf("Unhandled: %x\n", msg); fflush(stdout);
#endif

      break;
  }
