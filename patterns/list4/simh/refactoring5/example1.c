#ifndef DEBUG_LIGHTPEN
if (gdu_unit.flags & UNIT_DETECTS_ENABLED && mouse_present) {
#endif
				if (gdu_x <= newx)
					xmin = gdu_x, xmax = newx;
				else
					xmin = newx,  xmax = gdu_x;

				if (gdu_y <= newy)
					ymin = gdu_y, ymax = newy;
				else
					ymin = newy,  ymax = gdu_y;

				if (newx == gdu_x) {
					// line is vertical. Nearest point is an endpoint if the mouse is above or
					// below the line segment, otherwise the segment point at the same y as the mouse
					xd = gdu_x;
					yd = (ymouse <= ymin) ? ymin : (ymouse >= ymax) ? ymax : ymouse;

					if (DIST2(xd, yd, xmouse, ymouse) <= lpen_dist2)
						hit = TRUE;
				}
				else if (newy == gdu_y) {
					// line is horizontal. Nearest point is an endpoint if the mouse is to the left or
					// the right of the line segment, otherwise the segment point at the same x as the mouse
					xd = (xmouse <= xmin) ? xmin : (xmouse >= xmax) ? xmax : xmouse;
					yd = gdu_y;

					if (DIST2(xd, yd, xmouse, ymouse) <= lpen_dist2)
						hit = TRUE;
				}
				else {
					// line is diagonal. See if the mouse is inside the box lpen_dist wider than the line segment's bounding rectangle
					if (xmouse >= (xmin-lpen_dist) && xmouse <= (xmax+lpen_dist) && ymouse >= (ymin-lpen_dist) || ymouse <= (ymax+lpen_dist)) {
						// compute the point at the intersection of the line through the line segment and the normal
						// to that line through the mouse. This is the point on the line through the line segment
						// nearest the mouse

						s  = (double)(newy - gdu_y) / (double)(newx - gdu_x);		// slope of line segment
						xd = (int) ((ymouse + xmouse/s - gdu_y + s*gdu_x) / (s + 1./s) + 0.5);

						// if intersection is beyond either end of the line segment, the nearest point to the
						// mouse is nearest segment end, otherwise it's the computed intersection point
						if (xd < xmin || xd > xmax) {
#ifdef DEBUG_LIGHTPEN
							// if it's a hit, set xd and yd so we can display the hit
							if (DIST2(gdu_x, gdu_y, xmouse, ymouse) <= lpen_dist2) {
								hit = TRUE;
								xd = gdu_x;
								yd = gdu_y;
							}
							else if (DIST2(newx, newy, xmouse, ymouse) <= lpen_dist2) {
								hit = TRUE;
								xd = newx;
								yd = newy;
							}
#else
							if (DIST2(gdu_x, gdu_y, xmouse, ymouse) <= lpen_dist2 || DIST2(newx, newy, xmouse, ymouse) <= lpen_dist2)
								hit = TRUE;
#endif
						}
						else {
							yd = (int) (gdu_y + s*(xd - gdu_x) + 0.5);
							if (DIST2(xd, yd, xmouse, ymouse) <= lpen_dist2)
								hit = TRUE;
						}
					}
				}
#ifndef DEBUG_LIGHTPEN
			}
