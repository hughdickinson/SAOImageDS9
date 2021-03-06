/*
    NB: MAKE SURE YOU EDIT THE TEMPLATE FILE!!!!
*/

#ifndef FILTER_PTYPE
#include <regions.h>
#endif


#ifndef UNUSED
#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif
#endif

/* panda and pie incorrectly used astronomical angles. fixed 4/2004 */
#define USE_ASTRO_ANGLE 0

/* we might want to avoid (x86) extended precision problems */
#define USE_FPU_DOUBLE 0
#if USE_FPU_DOUBLE
#include <fpu_control.h>
static fpu_control_t _cw;
#define FPU_DOUBLE {fpu_control_t _cw2; _FPU_GETCW(_cw); _cw2 = _cw & ~_FPU_EXTENDED; _cw2 |= _FPU_DOUBLE; _FPU_SETCW(_cw2);}
#define FPU_RESTORE {_FPU_SETCW(_cw);}
#else
#define FPU_DOUBLE
#define FPU_RESTORE
#endif

/* alternate method of avoiding (x86) extended precision problems */
#define USE_FLOAT_COMPARE 0

/* add this to FilterOpen to cause this module to be loaded for dynamic linking */
static int evregno=0;
void initevregions(void)
{
  evregno++;
  return;
}

static int polypt(double x, double y, double* poly, int count,
		  double UNUSED(xstart), double ystart, int flag)
{
  /*    x-- x value of point being tested */
  /* y-- y value of point being tested */
  /* poly-- bounding polygon, array of length (count*2) */
  /* count-- number of edges of bounding polygon  */

  /* This algorithm is from "An Introduction to Ray Tracing", Academic Press, */
  /* 1989, edited by Andrew Glassner, pg 53 */
  /* a point lies in a polygon if a line is extended from the point to infinite */
  /* in any direction and the number of intersections with the polygon is odd. */
  /* This is valid for both concave and convex polygons. */
  /* Points on a vertex are considered inside. */
  /* Points on a edge are considered inside. */

  /* number of crossings */
  int crossings = 0;

  /* init sign for first vertice */
  int sign = ((poly[1] - y)>=0) ? 1 : -1;

  /* for all edges */
  int i;

  /* if flag is set, we check x, y against first point */
  if( flag && (x == poly[0]) && (y == poly[1]) ) return 1;

  for(i=0; i<count; i++) {
    int j = (i!=(count-1)) ? i+1 : 0;

    /* Vertex 1 */
    double x1 = poly[i*2] - x;
    double y1 = poly[i*2+1] - y;

    /* Vertex 2 */
    double x2 = poly[j*2] - x;
    double y2 = poly[j*2+1] - y;

    /* sign holder for p2 */
    int nextSign = (y2>=0) ? 1 : -1;

    /* horiz line */
    if( (y1==0) && (y2==0) ){
      if( ((x2>=0) && (x1<=0)) || ((x1>=0) && (x2<=0)) ){
	/* we always return true for ystart horiz lines */
	if( y == ystart )
	  return 1;
	else
	  return fmod((double)crossings+1,2.0) ? 1 : 0;
      }
    }
    /* vertical line */
    else if( (x1==0) && (x2==0) ){
      if( ((y2>=0) && (y1<=0)) || ((y1>=0) && (y2<=0)) ){
	return fmod((double)crossings+1,2.0) ? 1 : 0;
      }
    }
    /* point on line */
    else if( feq((y1*(x2-x1)),(x1*(y2-y1))) ){
      if( (((x2>=0) && (x1<=0)) || ((x1>=0) && (x2<=0))) &&
	  (((y2>=0) && (y1<=0)) || ((y1>=0) && (y2<=0))) ){
	return fmod((double)crossings+1,2.0) ? 1 : 0;
      }
    }
#if 0
    /* horiz line */
    if( (y1==0) && (y2==0) ){
      if( ((x2>=0) && (x1<=0)) || ((x1>=0) && (x2<=0)) ){
	if( y == ystart ){
	  return 1;
	}
      }
    }
    /* vertical line */
    else if( (x1==0) && (x2==0) ){
      if( ((y2>=0) && (y1<=0)) || ((y1>=0) && (y2<=0)) ){
	if( x == xstart ){
	  return 1;
	}
      }
    }
    /* point on line */
    else if( feq((y1*(x2-x1)),(x1*(y2-y1))) ){
      if( (((x2>=0) && (x1<=0)) || ((x1>=0) && (x2<=0))) &&
	  (((y2>=0) && (y1<=0)) || ((y1>=0) && (y2<=0))) ){
	return 0;
      }
    }
#endif
    if (sign != nextSign) {
      if (x1>0 && x2>0)
	crossings++;
      else if (x1>0 || x2>0) {
	if (x1-(y1*(x2-x1)/(y2-y1)) > 0)
	  crossings++;
      }
      sign = nextSign;
    }
  }

  return crossings%2 ? 1 : 0;          /* if odd, point is inside */
}

static void quadeq(double a, double b, double c,
	    double *x1, double *x2, int *nr, int *nc)
{
  double dis, q;
  if( feq(a,0.0) ){
    *nc = 0;
    if( feq(b,0.0) ){
      *nr = 0; *x1 = 0.0;
    }
    else{
      *nr = 1; *x1 = -c / b;
    }
    *x2 = *x1;
  }
  else{
    dis = b*b - 4.0 * a * c;
    if( dis > 0.0 ){
      *nr = 2; *nc = 0;
      dis = sqrt(dis);
      if( b < 0.0 ) dis = -dis;
      q = -0.5 * (b + dis);
      *x1 = q/a; *x2 = c/q;
      if(*x1 > *x2){
	q = *x1; *x1 = *x2; *x2 = q;
      }
    } 
    else if( feq(dis,0.0) ){
      *nr = 1; *nc = 0; *x1 = - 0.5 * b / a; *x2 = *x1;
    }
    else{
      *nr = 0; *nc = 2; *x1 = - 0.5 * b / a; *x2 = 0.5 * sqrt(-dis) / a;
    }
  }
}

static int corner_vertex(int index, int width, int height,
			 double *x, double *y)
{
  switch (index) {
  case 1:
    *x = 0.0;
    *y = height + 1;
    break;
  case 2:
    *x = 0.0;
    *y = 0.0;
    break;
  case 3:
    *x = width + 1;
    *y = 0.0;
    break;
  case 4:
    *x = width + 1;
    *y = height + 1;
  default:
    break;
  }
  index = index + 1;
  if(index > 4) index = 1;
  return(index);
}

static int pie_intercept(double width, double height, double xcen, double ycen,
			 double angle, double *xcept, double *ycept)
{
  double angl, slope;	/* l: angle and slope of ray */
  angl = angle;
  /* put angles in normal range */
  while (angl < 0.0)
    angl = angl + 360.0;
  while (angl >= 360.0)
    angl = angl - 360.0;
  /* check for a horizontal angle */
#if USE_ASTRO_ANGLE
  if(fabs(angl - 90.0) < SMALL_NUMBER) {
#else
  if(fabs(angl - 180.0) < SMALL_NUMBER) {
#endif
    *xcept = 0.0;
    *ycept = ycen;
    return(2);
  }
#if USE_ASTRO_ANGLE
  if(fabs(angl - 270.0) < SMALL_NUMBER) {
#else
  if(fabs(angl - 0.0) < SMALL_NUMBER) {
#endif
    *xcept = width + 1;
    *ycept = ycen;
    return(4);
  }
  /* convert to a Cartesian angle */
#if USE_ASTRO_ANGLE
  angl = angl + 90.0;
#endif
  if(angl >= 360.0)
    angl = angl - 360.0;
  if(angl < 180.0) {
    *ycept = height + 1;
    /* rule out vertical line */
    if(fabs(angl - 90.0) < SMALL_NUMBER) {
      *xcept = xcen;
      return(1);
    }
  } else {
    *ycept = 0.0;
    /* rule out vertical line */
    if(fabs(angl - 270.0) < SMALL_NUMBER) {
      *xcept = xcen;
      return(3);
    }
  }
  /* convert to radians */
  angl = (angl / 180.0) * M_PI;
  /* calculate slope */
  slope = tan(angl);
  /* calculate intercept with designated y edge */
  *xcept = xcen + ((*ycept - ycen) / slope);
  if(*xcept < 0) {
    *ycept = (ycen - (xcen * slope));
    *xcept = 0.0;
    return(2);
  } else if(*xcept > (width + 1)) {
    *ycept = (ycen + ((width + 1 - xcen) * slope));
    *xcept = width + 1;
    return(4);
  } else {
    if(*ycept < height)
      return(3);
    else
      return(1);
  }
}

/* ***************************** shapes ********************************** */

int evannulus(GFilt g, int rno, int sno, int flag, int type,
	      double x, double y,
	      double xcen, double ycen, double ri, double ro)
{
  /* use circle if possible */
  if( ri == 0 ){
    return(evcircle(g, rno, sno, flag, type, x, y, xcen, ycen, ro));
  }

  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    g->shapes[sno].ystart = ycen - ro;
    g->shapes[sno].ystop = ycen + ro;
    g->shapes[sno].r1sq = ri * ri;
    g->shapes[sno].r2sq = ro * ro;
  }

  if((((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))	            &&
     (((xcen-x)*(xcen-x))+((ycen-y)*(ycen-y))<=g->shapes[sno].r2sq)	    &&
     (((xcen-x)*(xcen-x))+((ycen-y)*(ycen-y))>g->shapes[sno].r1sq)) == flag ){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else{
    return 0;
  }
}

int evbox(GFilt g, int rno, int sno, int flag, int UNUSED(type),
	  double x, double y,
	  double xcen, double ycen, double xwidth, double yheight,
	  double angle)
{
  int i;
  double angl;			 /* l: Cartesian angle in radians */
  double half_width, half_height;/* l: radii (1/2 width and height) */
  double cosangl, sinangl;	 /* l: sine, cosine of the Cartesian angle */
  double hw_cos, hw_sin;	 /* l: products of half_width with sin, cos */
  double hh_cos, hh_sin;	 /* l: products of half_height with sin, cos */
  double xstart=0.0;

  if( (xwidth == 0) && (yheight==0) ){
    return(!flag);
  }
  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
#if USE_ASTRO_ANGLE
    /* convert to a Cartesian angle; save angle for use in multi or slices */
    angl = angle + 90.0;
#else
    angl = angle;
#endif
    while (angl >= 360.0) angl = angl - 360.0;
    /* convert to radians */
    angl = (angl / 180.0) * M_PI;
    sinangl = sin (angl);
    cosangl = cos (angl);
#if USE_ASTRO_ANGLE
    /* since we rotate by 90.0 degrees to get from astro angle to cartesian, */
    /* we also need to switch the width and height. we do this secretly so */
    /* that the display will turn out right, by doing it in the half terms */
    half_width = yheight / 2.0;
    half_height = xwidth / 2.0;
#else
    half_width = xwidth / 2.0;
    half_height = yheight / 2.0;
#endif
    hw_cos = half_width * cosangl;
    hw_sin = half_width * sinangl;
    hh_cos = half_height * cosangl;
    hh_sin = half_height * sinangl;
    g->shapes[sno].pts = (double *)calloc(8, sizeof(double));
#if USE_ASTRO_ANGLE
    g->shapes[sno].pts[0] = xcen - hw_cos - hh_sin;
    g->shapes[sno].pts[1] = ycen - hw_sin + hh_cos;
    g->shapes[sno].pts[2] = xcen + hw_cos - hh_sin;
    g->shapes[sno].pts[3] = ycen + hw_sin + hh_cos;
    g->shapes[sno].pts[4] = xcen + hw_cos + hh_sin;
    g->shapes[sno].pts[5] = ycen + hw_sin - hh_cos;
    g->shapes[sno].pts[6] = xcen - hw_cos + hh_sin;
    g->shapes[sno].pts[7] = ycen - hw_sin - hh_cos;
#else
    g->shapes[sno].pts[0] = xcen - hw_cos + hh_sin;
    g->shapes[sno].pts[1] = ycen - hh_cos - hw_sin;
    g->shapes[sno].pts[2] = xcen - hw_cos - hh_sin;
    g->shapes[sno].pts[3] = ycen + hh_cos - hw_sin;
    g->shapes[sno].pts[4] = xcen + hw_cos - hh_sin;
    g->shapes[sno].pts[5] = ycen + hh_cos + hw_sin;
    g->shapes[sno].pts[6] = xcen + hw_cos + hh_sin;
    g->shapes[sno].pts[7] = ycen - hh_cos + hw_sin;
#endif
    g->shapes[sno].npt = 8;
    /* now find the y limits */
    if( g->shapes[sno].npt ){
      xstart = g->shapes[sno].pts[0];
      g->shapes[sno].ystart = g->shapes[sno].pts[1];
      g->shapes[sno].ystop = g->shapes[sno].ystart;
      for(i=1; i<g->shapes[sno].npt; i+=2){
	if(g->shapes[sno].pts[i-1] < xstart)
	  xstart = g->shapes[sno].pts[i-1];
	if(g->shapes[sno].pts[i] > g->shapes[sno].ystop)
	  g->shapes[sno].ystop = g->shapes[sno].pts[i];
	if(g->shapes[sno].pts[i] < g->shapes[sno].ystart)
	  g->shapes[sno].ystart = g->shapes[sno].pts[i];
      }
    }
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))	&&
       polypt(x, y, g->shapes[sno].pts, g->shapes[sno].npt/2,
	      xstart, g->shapes[sno].ystart, 0)) == flag		){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

int evcircle(GFilt g, int rno, int sno, int flag, int UNUSED(type),
	     double x, double y,
	     double xcen, double ycen, double radius)
{
  if( radius == 0 ){
    return(!flag);
  }
  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    g->shapes[sno].ystart = ycen - radius;
    g->shapes[sno].ystop = ycen + radius;
    g->shapes[sno].r1sq = radius * radius;
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))		    &&
      (((xcen-x)*(xcen-x))+((ycen-y)*(ycen-y))<=g->shapes[sno].r1sq)) == flag  ){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

int evellipse(GFilt g, int rno, int sno, int flag, int type,
	      double x, double y,
	      double xcen, double ycen, double xrad, double yrad, double angle)
{
  double yhi, yoff;
  double b, c;
  double b_partial, c_partial;
  double xboff, xfoff;
  int nr, nc;

  /* use circle if possible */
  if( xrad == yrad ){
    return(evcircle(g, rno, sno, flag, type, x, y, xcen, ycen, xrad));
  }

  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    /* set worst case limits (xrad axis parallel to vertical axis) */
#if USE_ASTRO_ANGLE
    /* convert to a Cartesian angle; save "angle" for use by other routines */
    g->shapes[sno].angl = angle + 90.0;
#else
    g->shapes[sno].angl = angle;
#endif
    while( g->shapes[sno].angl >= 360.0 )
      g->shapes[sno].angl = g->shapes[sno].angl - 360.0;
    /* convert to radians */
    g->shapes[sno].angl = (g->shapes[sno].angl / 180.0) * M_PI;
    g->shapes[sno].sinangl = sin(g->shapes[sno].angl);
    g->shapes[sno].cosangl = cos(g->shapes[sno].angl);
    /* calculate approximate y limits */
    /* choose lesser of containing rotbox and circle */
#if USE_ASTRO_ANGLE
    yhi = fabs(g->shapes[sno].sinangl * yrad) + 
          fabs(g->shapes[sno].cosangl * xrad);
#else
    yhi = fabs(g->shapes[sno].sinangl * xrad) + 
          fabs(g->shapes[sno].cosangl * yrad);
#endif
    yhi = min(yhi, max(yrad, xrad));
    g->shapes[sno].ystart = ycen - yhi;
    g->shapes[sno].ystop = ycen + yhi;
    /* prepare partials for quadratic equation solutions to coordinates */
    g->shapes[sno].cossq = g->shapes[sno].cosangl * g->shapes[sno].cosangl;
    g->shapes[sno].sinsq = g->shapes[sno].sinangl * g->shapes[sno].sinangl;
#if USE_ASTRO_ANGLE
    /* because we rotate by 90.0 degrees to get from astro angle to */
    /* cartesian, we also need to switch the x and y axes. we do this */
    /* secretly so that the display will turn out right, by doing it in */
    /* the sq terms */
    g->shapes[sno].xradsq = yrad * yrad;
    g->shapes[sno].yradsq = xrad * xrad;
#else
    g->shapes[sno].xradsq = xrad * xrad;
    g->shapes[sno].yradsq = yrad * yrad;
#endif
    /* fill in as much of a,b,c as we can */
    g->shapes[sno].a = (g->shapes[sno].cossq / g->shapes[sno].xradsq) + 
       		       (g->shapes[sno].sinsq / g->shapes[sno].yradsq);
  }
  if( ((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop)) ){
    b_partial = (2.0 * g->shapes[sno].sinangl) * 
                ((g->shapes[sno].cosangl / g->shapes[sno].xradsq) - 
                (g->shapes[sno].cosangl / g->shapes[sno].yradsq));
    c_partial = (g->shapes[sno].sinsq / g->shapes[sno].xradsq) + 
                (g->shapes[sno].cossq / g->shapes[sno].yradsq);
    yoff = y - ycen;
    b = b_partial * yoff;
    c = (c_partial * yoff * yoff) - 1.0;
    /* solve quadratic */
    quadeq (g->shapes[sno].a, b, c, &xboff, &xfoff, &nr, &nc);
    /* if real roots */
    if( nr != 0 ) {
      FPU_DOUBLE
#if USE_FLOAT_COMPARE
      if( (((float)x>=(float)(xcen+xboff)) && 
	   ((float)x<=(float)(xcen+xfoff))) == flag ){
#else
      if( ((x>=(xcen+xboff)) && (x<=(xcen+xfoff))) == flag ){
#endif
	if( rno && flag ) g->rid = rno;
	FPU_RESTORE
	return 1;
      }
      else{
	FPU_RESTORE
	return 0;
      }
    }
    else
      return !flag;
  }
  return !flag;
}

int evfield(GFilt g, int rno, int UNUSED(sno), int flag, int UNUSED(type),
	    double UNUSED(x), double UNUSED(y))
{
  if( flag ){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

int evline(GFilt g, int rno, int sno, int flag, int UNUSED(type),
	   double x, double y,
	   double x1, double y1, double x2, double y2)
{
  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    g->shapes[sno].ystart = min(y1,y2);
    g->shapes[sno].ystop = max(y1,y2);
    g->shapes[sno].x1 = x1;
    g->shapes[sno].x2 = x2;
    g->shapes[sno].y1 = y1;
    if( feq(y1,y2) ){
      g->shapes[sno].xonly = 1;
      g->shapes[sno].invslope = 0;
    }
    else{
      g->shapes[sno].xonly = 0;
      g->shapes[sno].invslope = (x1 - x2) / (y1 - y2);
    }
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))		 &&
      ((!g->shapes[sno].xonly &&
       feq((((y-g->shapes[sno].y1)*g->shapes[sno].invslope)+g->shapes[sno].x1),x)) ||
      (g->shapes[sno].xonly &&
       ((x>=g->shapes[sno].x1)&&(x<=g->shapes[sno].x2))))) == flag){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

int evpie(GFilt g, int rno, int sno, int flag, int type,
	  double x, double y,
	  double xcen, double ycen, double angle1, double angle2)
{
  int i;
  int width, height;		/* l: image mask width and height */
  double sweep;			/* l: sweep between cut angles */
  int intrcpt1, intrcpt2;	/* l: side intercepted by each cut */
  double x2, y2;		/* l: coordinates of second intercept */
  double xstart=0.0;

  /* use field if possible */
  if( (angle1==0) && (angle2==360) ){
    return(evfield(g, rno, sno, flag, type, x, y));
  }

  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    /* we have to fake width and height, since we do not know them! */
    width = LARGE_NUMBER;
    height = LARGE_NUMBER;
    /* start listing vertices of polygon */
    g->shapes[sno].pts = (double *)calloc(14, sizeof(double));
    g->shapes[sno].pts[0] = xcen;
    g->shapes[sno].pts[1] = ycen;
    sweep = angle2 - angle1;
    /* if sweep is too small to be noticed, don't bother */
    if(fabs(sweep) < SMALL_NUMBER)
      return !flag;
    if (sweep < 0.0) sweep = sweep + 360.0;
    intrcpt1 = pie_intercept((double)width, (double)height, xcen, ycen, angle1,
			     &(g->shapes[sno].pts[2]),
			     &(g->shapes[sno].pts[3]));
    intrcpt2 = pie_intercept((double)width, (double)height, xcen, ycen, angle2,
			     &x2, &y2);
    g->shapes[sno].npt = 4;
    /* if angles intercept same side and slice is between them, no corners */
    /* else, mark corners until reaching side with second angle intercept */
    if((intrcpt1 != intrcpt2) || (sweep > 180.0)){
      do{
	intrcpt1 = corner_vertex(intrcpt1, width, height,  
				 &(g->shapes[sno].pts[g->shapes[sno].npt]),
				 &(g->shapes[sno].pts[g->shapes[sno].npt+1]));
	g->shapes[sno].npt = g->shapes[sno].npt + 2;
      }while(intrcpt1 != intrcpt2);
    }
    g->shapes[sno].pts[g->shapes[sno].npt] = x2;
    g->shapes[sno].pts[g->shapes[sno].npt+1] = y2;
    g->shapes[sno].npt = g->shapes[sno].npt + 2;
    /* now find the y limits */
    if( g->shapes[sno].npt ){
      xstart = g->shapes[sno].pts[0];
      g->shapes[sno].ystart = g->shapes[sno].pts[1];
      g->shapes[sno].ystop = g->shapes[sno].ystart;
      for(i=1; i<g->shapes[sno].npt; i+=2){
	if(g->shapes[sno].pts[i-1] < xstart)
	  xstart = g->shapes[sno].pts[i-1];
	if(g->shapes[sno].pts[i] > g->shapes[sno].ystop)
	  g->shapes[sno].ystop = g->shapes[sno].pts[i];
	if(g->shapes[sno].pts[i] < g->shapes[sno].ystart)
	  g->shapes[sno].ystart = g->shapes[sno].pts[i];
      }
    }
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))	&&
       polypt(x, y, g->shapes[sno].pts, g->shapes[sno].npt/2,
	      xstart, g->shapes[sno].ystart, 1)) == flag		){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else{
    return 0;
  }
}

int evqtpie(GFilt g, int rno, int sno, int flag, int type,
	    double x, double y,
	    double xcen, double ycen, double angle1, double angle2)
{
  return evpie(g, rno, sno, flag, type, x, y, xcen, ycen, angle1, angle2);
}

int evpoint(GFilt g, int rno, int UNUSED(sno), int flag, int UNUSED(type),
	    double x, double y,
	    double xcen, double ycen)
{
  if( ((x==xcen) && (y==ycen)) == flag ){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

#ifdef __STDC__
int
evpolygon(GFilt g, int rno, int sno, int flag, int UNUSED(type),
	  double x, double y, ...)
{
  int i, maxpts;
  double xstart=0.0;
  va_list args;
  va_start(args, y);
#else
int evpolygon(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double xstart=0.0;
  int i, maxpts;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
#endif
  if( !g->shapes[sno].init ){
    g->shapes[sno].init = 1;
    /* allocate space for x,y arguments */
    maxpts = MASKINC;
    g->shapes[sno].pts = (double *)calloc(maxpts, sizeof(double));
    /* gather up arguments */
    g->shapes[sno].npt = 0;
    while( 1 ){
      if( g->shapes[sno].npt >= maxpts ){
	maxpts += MASKINC;
	g->shapes[sno].pts = (double *)realloc(g->shapes[sno].pts,
					    maxpts*sizeof(double));
      }
      g->shapes[sno].pts[g->shapes[sno].npt] = va_arg(args, double);
      /* two negatives in a row means we are at end of args */
      if( feq(g->shapes[sno].pts[g->shapes[sno].npt],PSTOP)	&&
	  feq(g->shapes[sno].pts[g->shapes[sno].npt-1],PSTOP) ){
	g->shapes[sno].npt--;
	break;
      }
      g->shapes[sno].npt++;
    }
    va_end(args);
    /* realloc to actual size */
    g->shapes[sno].pts = (double *)realloc(g->shapes[sno].pts,
					g->shapes[sno].npt*sizeof(double));
    /* now find the y limits */
    if( g->shapes[sno].npt ){
      xstart = g->shapes[sno].pts[0];
      g->shapes[sno].ystart = g->shapes[sno].pts[1];
      g->shapes[sno].ystop = g->shapes[sno].ystart;
      for(i=1; i<g->shapes[sno].npt; i+=2){
	if(g->shapes[sno].pts[i-1] < xstart)
	  xstart = g->shapes[sno].pts[i-1];
	if(g->shapes[sno].pts[i] > g->shapes[sno].ystop)
	  g->shapes[sno].ystop = g->shapes[sno].pts[i];
	if(g->shapes[sno].pts[i] < g->shapes[sno].ystart)
	  g->shapes[sno].ystart = g->shapes[sno].pts[i];
      }
    }
  }
  if( (((y>=g->shapes[sno].ystart) && (y<=g->shapes[sno].ystop))	&&
       polypt(x, y, g->shapes[sno].pts, g->shapes[sno].npt/2,
	      xstart, g->shapes[sno].ystart, 0)) == flag		){
    if( rno && flag ) g->rid = rno;
    return 1;
  }
  else
    return 0;
}

/* accelerator regions -- lower and upper limits are given for n regions */

int evnannulus(GFilt g, int rno, int sno, int flag, int type,
	     double x, double y, double xcen, double ycen,
	     double lo, double hi, int n)
{
  int i;
  int xsno;
  double dinc;

  /* get limits */
  dinc = (hi - lo)/(double)n;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evannulus(g, 0, xsno, flag, type, x, y, xcen, ycen, lo, hi) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evannulus(g, rno+i, sno+i, flag, type, x, y,
		    xcen, ycen, lo+(i*dinc), lo+((i+1)*dinc)) ){
	return(1);
      }
    }
    return(0);
  }
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evannulus(g, 0, xsno, 1, type, x, y, xcen, ycen, lo, hi) ){
      return(1);
    }
    return(0);
  }
}

int evnbox(GFilt g, int rno, int sno, int flag, int type,
	   double x, double y, double xcen, double ycen,
	   double lox, double loy, double hix, double hiy, int n,
	   double ang)
{
  int i;
  int xsno;
  double dincx;
  double dincy;

  /* get limits */
  dincx = (hix - lox)/n;
  dincy = (hiy - loy)/n;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evbox(g, 0, xsno, flag, type, x, y, xcen, ycen, hix, hiy, ang) ){
      return(0);
    }
    /* if its in the inner region we lose */
    if( evbox(g, 0, xsno+1, flag, type, x, y, xcen, ycen, lox, loy, ang) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evbox(g, rno+i, sno+i, flag, type, x, y,
		xcen, ycen, lox+((i+1)*dincx), loy+((i+1)*dincy), ang) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evbox(g, 0, xsno, 1, type, x, y, xcen, ycen, hix, hiy, ang) ){
      return(1);
    }
    /* if its in the inner region we win */
    if( evbox(g, 0, xsno+1, 1, type, x, y, xcen, ycen, lox, loy, ang) ){
      return(1);
    }
    return(0);
  }
}

int evnellipse(GFilt g, int rno, int sno, int flag, int type,
	       double x, double y, double xcen, double ycen,
	       double lox, double loy, double hix, double hiy, int n,
	       double ang)
{
  int i;
  int xsno;
  double dincx;
  double dincy;

  /* get limits */
  dincx = (hix - lox)/n;
  dincy = (hiy - loy)/n;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evellipse(g, 0, xsno, flag, type, x, y, xcen, ycen, hix, hiy, ang) ){
      return(0);
    }
    /* if its in the inner region we lose */
    if( evellipse(g, 0, xsno+1, flag, type, x, y, xcen, ycen, lox, loy, ang) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evellipse(g, rno+i, sno+i, flag, type, x, y,
		    xcen, ycen, lox+((i+1)*dincx), loy+((i+1)*dincy), ang) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evellipse(g, 0, xsno, 1, type, x, y, xcen, ycen, hix, hiy, ang) ){
      return(1);
    }
    /* if its in the inner region we win */
    if( evellipse(g, 0, xsno+1, 1, type, x, y, xcen, ycen, lox, loy, ang) ){
      return(1);
    }
    return(0);
  }
}

int evnpie(GFilt g, int rno, int sno, int flag, int type,
	 double x, double y, double xcen, double ycen,
	 double lo, double hi, int n)
{
  int i;
  int xsno;
  double dinc;

  /* get limits */
  while( lo > hi ) lo -= 360.0;
  dinc = (hi - lo)/n;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* check limits */
    if( !evpie(g, 0, xsno, flag, type, x, y, xcen, ycen, lo, hi) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evpie(g, rno+i, sno+i, flag, type, x, y,
		xcen, ycen, lo+(i*dinc), lo+((i+1)*dinc)) ){
	return(1);
      }
    }
    return(0);
  }
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evpie(g, 0, xsno, 1, type, x, y, xcen, ycen, lo, hi) ){
      return(1);
    }
    return(0);
  }
}

int evpanda(GFilt g, int rno, int sno, int flag, int type,
	    double x, double y,
	    double xcen, double ycen,
	    double anglo, double anghi, double angn,
	    double radlo, double radhi, double radn)
{
    
  int a, r;
  int ahi, rhi;
  int xsno;
  int n=0;
  double ainc, rinc;

  /* get limits */
  ainc = (anghi - anglo)/angn;
  ahi = (int)angn;
  rinc = (radhi - radlo)/radn;
  rhi = (int)radn;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evannulus(g, 0, xsno, flag, type, x, y, xcen, ycen, radlo, radhi) ||
	!evpie(g, 0, xsno+1, flag, type, x, y, xcen, ycen, anglo, anghi)   ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(a=1; a<=ahi; a++){
      for(r=1; r<=rhi; r++){
	if( evannulus(g, rno+n, sno+(2*n), flag, type, x, y,
		      xcen, ycen, radlo+((r-1)*rinc), radlo+(r*rinc)) &&
	    evpie(g, rno+n, sno+(2*n+1), flag, type, x, y,
		  xcen, ycen, anglo+((a-1)*ainc), anglo+(a*ainc))     ){
	  return(1);
	}
	n++;
      }
    }
    return(0);
  }
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evannulus(g, 0, xsno, 1, type, x, y, xcen, ycen, radlo, radhi) )
      return(1);
    else if( !evpie(g, 0, xsno+1, 1, type, x, y, xcen, ycen, anglo, anghi) ){
      return(1);
    }
    else{
      return(0);
    }
  }
}

int evbpanda(GFilt g, int rno, int sno, int flag, int type,
	     double x, double y,
	     double xcen, double ycen,
	     double anglo, double anghi, double angn,
	     double xlo, double ylo, double xhi, double yhi, double radn,
	     double ang)
{
    
  int a, r;
  int ahi, rhi;
  int xsno;
  int n=0;
  double ainc, xinc, yinc;

  /* get limits */
  anglo += ang;
  anghi += ang;
  ainc = (anghi - anglo)/angn;
  ahi = (int)angn;
  xinc = (xhi - xlo)/radn;
  yinc = (yhi - ylo)/radn;
  rhi = (int)radn;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evbox(g, 0, xsno, flag, type, x, y, xcen, ycen, xhi, yhi,
	       ang) ){
      return(0);
    }
    /* but if its in the inner region we lose */
    else if( evbox(g, 0, xsno+2, flag, type, x, y, xcen, ycen, xlo, ylo,
		   ang) ){
      return(0);
    }
    /* its in the box .. must also be in the pie */
    else if( !evpie(g, 0, xsno+1, flag, type, x, y, xcen, ycen, anglo, anghi)){
      return(0);
    }
    /* look through all of them to find the right one */
    for(a=0; a<ahi; a++){
      for(r=1; r<=rhi; r++){
	if( evbox(g, rno+n, sno+(2*n), flag, type, x, y,
		  xcen, ycen, xlo+(r*xinc), ylo+(r*yinc), ang)   &&
	    evqtpie(g, rno+n, sno+(2*n+1), flag, type, x, y,
		    xcen, ycen, anglo+(a*ainc), anglo+((a+1)*ainc))  ){
	  return(1);
	}
	n++;
      }
    }
    return(0);
  }
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evbox(g, 0, xsno, 1, type, x, y, xcen, ycen, xhi, yhi, ang) )
      return(1);
    /* if its in the inner region we win */
    else if( !evbox(g, 0, xsno+2, 1, type, x, y, xcen, ycen, xlo, ylo,
		    ang) )
      return(1);
    /* if its not in the pie, we win */
    else if( !evpie(g, 0, xsno+1, 1, type, x, y, xcen, ycen, anglo, anghi) ){
      return(1);
    }
    else{
      return(0);
    }
  }
}

int evepanda(GFilt g, int rno, int sno, int flag, int type,
	     double x, double y,
	     double xcen, double ycen,
	     double anglo, double anghi, double angn,
	     double xlo, double ylo, double xhi, double yhi, double radn,
	     double ang)
{
    
  int a, r;
  int ahi, rhi;
  int xsno;
  int n=0;
  double ainc, xinc, yinc;

  /* get limits */
  anglo += ang;
  anghi += ang;
  ainc = (anghi - anglo)/angn;
  ahi = (int)angn;
  xinc = (xhi - xlo)/radn;
  yinc = (yhi - ylo)/radn;
  rhi = (int)radn;
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evellipse(g, 0, xsno, flag, type, x, y, xcen, ycen, xhi, yhi,
		   ang) ){
      return(0);
    }
    /* but if its in the inner region we lose */
    else if( evellipse(g, 0, xsno+2, flag, type, x, y, xcen, ycen, xlo, ylo,
		       ang) ){
      return(0);
    }
    /* its in the ellipse .. must also be in the pie */
    else if( !evpie(g, 0, xsno+1, flag, type, x, y, xcen, ycen, anglo, anghi)){
      return(0);
    }
    /* look through all of them to find the right one */
    for(a=0; a<ahi; a++){
      for(r=1; r<=rhi; r++){
	if( evellipse(g, rno+n, sno+(2*n), flag, type, x, y,
		      xcen, ycen, xlo+(r*xinc), ylo+(r*yinc), ang) &&
	    evqtpie(g, rno+n, sno+(2*n+1), flag, type, x, y,
		    xcen, ycen, anglo+(a*ainc), anglo+((a+1)*ainc))  ){
	  return(1);
	}
	n++;
      }
    }
    return(0);
  }
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evellipse(g, 0, xsno, 1, type, x, y, xcen, ycen, xhi, yhi, ang) )
      return(1);
    /* if its in the inner region we win */
    else if( !evellipse(g, 0, xsno+2, 1, type, x, y, xcen, ycen, xlo, ylo,
			ang) )
      return(1);
    /* if its not in the pie, we win */
    else if( !evpie(g, 0, xsno+1, 1, type, x, y, xcen, ycen, anglo, anghi) ){
      return(1);
    }
    else{
      return(0);
    }
  }
}

/* varargs regions -- a series of lower and upper limits is specified */

#ifdef __STDC__
int
evvannulus(GFilt g, int rno, int sno, int flag, int type,
	   double x, double y, double xcen, double ycen, ...)
{
  int i, n;
  int maxpts;
  int xsno;
  double *xv;
  va_list args;
  va_start(args, ycen);
#else
int evvannulus(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double xcen, ycen;
  double *xv;
  int i, n;
  int maxpts;
  int xsno;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
  xcen  = va_arg(args, double);
  ycen  = va_arg(args, double);
#endif
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( !g->shapes[xsno].xv ){
    maxpts = MASKINC;
    g->shapes[xsno].xv = (double *)calloc(maxpts, sizeof(double));
    g->shapes[xsno].nv = 0;
    while( 1 ){
      if( g->shapes[xsno].nv >= maxpts ){
        maxpts += MASKINC;
        g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  					      maxpts*sizeof(double));
      }
      g->shapes[xsno].xv[g->shapes[xsno].nv] = va_arg(args, double);
      if( feq(g->shapes[xsno].xv[g->shapes[xsno].nv],PSTOP)   &&
  	feq(g->shapes[xsno].xv[g->shapes[xsno].nv-1],PSTOP) ){
        g->shapes[xsno].nv--;
        break;
      }
      g->shapes[xsno].nv++;
    }
    va_end(args);
    g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  	  	        g->shapes[xsno].nv*sizeof(double));
  }
  n = g->shapes[xsno].nv;
  xv = g->shapes[xsno].xv;
  /* this should be impossible ... */
  if( n == 2 ){
    return(evannulus(g, rno, sno, flag, type, x, y, xcen, ycen, xv[0], xv[1]));
  }
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evannulus(g, 0, xsno, flag, type, x, y, xcen, ycen, xv[0], xv[n-1]) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evannulus(g, rno+i, sno+i, flag, type, x, y, xcen, ycen,
		  xv[i], xv[i+1]) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evannulus(g, 0, xsno, 1, type, x, y, xcen, ycen, xv[0], xv[n-1]) ){
      return(1);
    }
    return(0);
  }
}

#ifdef __STDC__
int
evvbox(GFilt g, int rno, int sno, int flag, int type,
       double x, double y, double xcen, double ycen, ...)
{
  int i, j, n;
  int maxpts;
  int xsno;
  double ang;
  double *xv;
  va_list args;
  va_start(args, ycen);
#else
int evvbox(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double xcen, ycen;
  double ang;
  double *xv;
  int i, j, n;
  int maxpts;
  int xsno;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
  xcen  = va_arg(args, double);
  ycen  = va_arg(args, double);
#endif
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( !g->shapes[xsno].xv ){
    maxpts = MASKINC;
    g->shapes[xsno].xv = (double *)calloc(maxpts, sizeof(double));
    g->shapes[xsno].nv = 0;
    while( 1 ){
      if( g->shapes[xsno].nv >= maxpts ){
        maxpts += MASKINC;
        g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  					      maxpts*sizeof(double));
      }
      g->shapes[xsno].xv[g->shapes[xsno].nv] = va_arg(args, double);
      if( feq(g->shapes[xsno].xv[g->shapes[xsno].nv],PSTOP)   &&
  	feq(g->shapes[xsno].xv[g->shapes[xsno].nv-1],PSTOP) ){
        g->shapes[xsno].nv--;
        break;
      }
      g->shapes[xsno].nv++;
    }
    va_end(args);
    g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  	  	        g->shapes[xsno].nv*sizeof(double));
  }
  n = g->shapes[xsno].nv;
  xv = g->shapes[xsno].xv;
  ang = xv[--n];
  /* this should be impossible ... */
  if( n == 2 ){
    return(evbox(g, rno, sno, flag, type, x, y,
		 xcen, ycen, xv[0], xv[1], ang));
  }
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evbox(g, 0, xsno, flag, type, x, y, xcen, ycen, xv[n-2], xv[n-1],
	       ang) ){
      return(0);
    }
    /* if its in the inner region we lose */
    if( evbox(g, 0, xsno+1, flag, type, x, y, xcen, ycen, xv[0], xv[1], ang) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=2, j=0; i<n; i+=2, j++){
      if( evbox(g, rno+j, sno+j, flag, type, x, y, xcen, ycen,
	      xv[i], xv[i+1], ang) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we win ... */
    if( !evbox(g, 0, xsno, 1, type, x, y, xcen, ycen, xv[n-2], xv[n-1], ang) ){
      return(1);
    }
    /* if its in the inner region we win */
    else if( evbox(g, 0, xsno+1, 1, type, x, y, xcen, ycen, xv[0], xv[1], ang) ){
      return(1);
    }
    return(0);
  }
}


#ifdef __STDC__
int
evvellipse(GFilt g, int rno, int sno, int flag, int type,
	   double x, double y, double xcen, double ycen, ...)
{
  int i, j, n;
  int maxpts;
  int xsno;
  double ang;
  double *xv;
  va_list args;
  va_start(args, ycen);
#else
int evvellipse(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double xcen, ycen;
  double ang;
  double *xv;
  int i, j, n;
  int maxpts;
  int xsno;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
  xcen  = va_arg(args, double);
  ycen  = va_arg(args, double);
#endif
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( !g->shapes[xsno].xv ){
    maxpts = MASKINC;
    g->shapes[xsno].xv = (double *)calloc(maxpts, sizeof(double));
    g->shapes[xsno].nv = 0;
    while( 1 ){
      if( g->shapes[xsno].nv >= maxpts ){
        maxpts += MASKINC;
        g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  					      maxpts*sizeof(double));
      }
      g->shapes[xsno].xv[g->shapes[xsno].nv] = va_arg(args, double);
      if( feq(g->shapes[xsno].xv[g->shapes[xsno].nv],PSTOP)   &&
  	feq(g->shapes[xsno].xv[g->shapes[xsno].nv-1],PSTOP) ){
        g->shapes[xsno].nv--;
        break;
      }
      g->shapes[xsno].nv++;
    }
    va_end(args);
    g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  	  	        g->shapes[xsno].nv*sizeof(double));
  }
  n = g->shapes[xsno].nv;
  xv = g->shapes[xsno].xv;
  ang = xv[--n];
  /* this should be impossible ... */
  if( n == 2 ){
    return(evellipse(g, rno, sno, flag, type, x, y,
		     xcen, ycen, xv[0], xv[1], ang));
  }
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evellipse(g, 0, xsno, flag, type, x, y, xcen, ycen, xv[n-2], xv[n-1],
		   ang) ){
      return(0);
    }
    /* if its in the inner region we lose */
    if( evellipse(g, 0, xsno+1, flag, type, x, y, xcen, ycen, xv[0], xv[1],
		  ang) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=2, j=0; i<n; i+=2, j++){
      if( evellipse(g, rno+j, sno+j, flag, type, x, y, xcen, ycen,
		  xv[i], xv[i+1], ang) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we lose ... */
    if( !evellipse(g, 0, xsno, 1, type, x, y, xcen, ycen, xv[n-2], xv[n-1],
		   ang) ){
      return(1);
    }
    /* if its in the inner region we win */
    if( evellipse(g, 0, xsno+1, 1, type, x, y, xcen, ycen, xv[0], xv[1], ang) ){
      return(1);
    }
    return(0);
  }
}

#ifdef __STDC__
int
evvpie(GFilt g, int rno, int sno, int flag, int type,
       double x, double y, double xcen, double ycen, ...)
{
  int i, n;
  int maxpts;
  int xsno;
  double *xv;
  va_list args;
  va_start(args, ycen);
#else
int evvpie(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double xcen, ycen;
  double *xv;
  int i, n;
  int maxpts;
  int xsno;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
  xcen  = va_arg(args, double);
  ycen  = va_arg(args, double);
#endif
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( !g->shapes[xsno].xv ){
    maxpts = MASKINC;
    g->shapes[xsno].xv = (double *)calloc(maxpts, sizeof(double));
    g->shapes[xsno].nv = 0;
    while( 1 ){
      if( g->shapes[xsno].nv >= maxpts ){
        maxpts += MASKINC;
        g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  					      maxpts*sizeof(double));
      }
      g->shapes[xsno].xv[g->shapes[xsno].nv] = va_arg(args, double);
      if( feq(g->shapes[xsno].xv[g->shapes[xsno].nv],PSTOP)   &&
  	feq(g->shapes[xsno].xv[g->shapes[xsno].nv-1],PSTOP) ){
        g->shapes[xsno].nv--;
        break;
      }
      g->shapes[xsno].nv++;
    }
    va_end(args);
    g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  	  	        g->shapes[xsno].nv*sizeof(double));
  }
  n = g->shapes[xsno].nv;
  xv = g->shapes[xsno].xv;
  /* this should be impossible ... */
  if( n == 2 ){
    return(evpie(g, rno, sno, flag, type, x, y,
		 xcen, ycen, xv[0], xv[1]));
  }
  if( flag ){
    /* if its not somewhere inside the entire region we lose ... */
    if( !evpie(g, 0, xsno, flag, type, x, y, xcen, ycen, xv[0], xv[n-1]) ){
      return(0);
    }
    /* look through all of them to find the right one */
    for(i=0; i<n; i++){
      if( evpie(g, rno+i, sno+i, flag, type, x, y, xcen, ycen, xv[i], xv[i+1]) ){
	return(1);
      }
    }
    return(0);
  }
  /* for excludes, we have to check that we are not in any of them */
  else{
    /* if its not somewhere inside the entire region we lose ... */
    if( !evpie(g, 0, xsno, 1, type, x, y, xcen, ycen, xv[0], xv[n-1]) ){
      return(1);
    }
    return(1);
  }
}

#ifdef __STDC__
int
evvpoint(GFilt g, int rno, int sno, int flag, int type,
	 double x, double y, ...)
{
  int i, j, n;
  int maxpts;
  int xsno;
  double *xv;
  va_list args;
  va_start(args, y);
#else
int evvpoint(va_alist) va_dcl
{
  GFilt g;
  int rno, sno, flag, type;
  double x, y;
  double *xv;
  int i, j, n;
  int maxpts;
  int xsno;
  va_list args;
  va_start(args);
  g  = va_arg(args, GFilt);
  rno  = va_arg(args, int);
  sno  = va_arg(args, int);
  flag  = va_arg(args, int);
  type  = va_arg(args, int);
  x  = va_arg(args, double);
  y  = va_arg(args, double);
#endif
  xsno = (g->nshapes+1)+((sno-1)*XSNO);
  if( !g->shapes[xsno].xv ){
    maxpts = MASKINC;
    g->shapes[xsno].xv = (double *)calloc(maxpts, sizeof(double));
    g->shapes[xsno].nv = 0;
    while( 1 ){
      if( g->shapes[xsno].nv >= maxpts ){
        maxpts += MASKINC;
        g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  					      maxpts*sizeof(double));
      }
      g->shapes[xsno].xv[g->shapes[xsno].nv] = va_arg(args, double);
      if( feq(g->shapes[xsno].xv[g->shapes[xsno].nv],PSTOP)   &&
  	feq(g->shapes[xsno].xv[g->shapes[xsno].nv-1],PSTOP) ){
        g->shapes[xsno].nv--;
        break;
      }
      g->shapes[xsno].nv++;
    }
    va_end(args);
    g->shapes[xsno].xv = (double *)realloc(g->shapes[xsno].xv,
  	  	        g->shapes[xsno].nv*sizeof(double));
  }
  n = g->shapes[xsno].nv;
  xv = g->shapes[xsno].xv;
  /* look through all of them to find the right one */
  for(i=0, j=0; i<n; i+=2, j++){
    if( evpoint(g, rno+j, sno+j, flag, type, x, y, xv[i], xv[i+1]) ){
      return(1);
    }
  }
  return(0);
}


