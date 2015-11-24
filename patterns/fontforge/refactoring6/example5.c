if ((t == m->tstart)
#ifdef FF_RELATIONAL_GEOM
       || (t < m->tstart && t >= m->otstart)
#endif // FF_RELATIONAL_GEOM
      ) {
      SONotify("We do not split at the start.\n");
      id->m = m; id->t;
      id->otherm = NULL; id->othert = 0;
      if (t == 0) {
        id->inter.x = m->s->from->me.x;
        id->inter.y = m->s->from->me.y;
      } else if (m->start != NULL) {
        id->inter.x = m->start->inter.x;
        id->inter.y = m->start->inter.y;
      } else {
        SOError("There is neither a spline end nor an intersection at the start of this monotonic.\n");
        id->inter.x = evalSpline(m->s, t, 0);
        id->inter.y = evalSpline(m->s, t, 0);
      }
    } else if (t != -1) {
      if (Within16RoundingErrors(t,m->tstart) || Within16RoundingErrors(t,m->tend)) {
        SOError("We're about to create a spline with a very small t-value.\n");
      }
      if (doit) SplitMonotonicAtT(m,which,t,coord,id);
      else {
        id->new = 1;
        id->t = t;
        id->inter.x = evalSpline(m->s, t, 0);
        id->inter.y = evalSpline(m->s, t, 1);
      }
    } else {
        id->t = t;
        id->inter.x = 0;
        id->inter.y = 0;
    }
