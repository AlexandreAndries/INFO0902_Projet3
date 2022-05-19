#include "Sketch.h"
#include "DynamicTimeWarping.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

/*============================================================================*/
/*============================== STATIC FUNCTIONS ============================*/
/*============================================================================*/
/** ------------------------------------------------------------------------ *
 * Compute the average absolute distance between two points.
 *
 * PARAMETERS
 * p1       The first point.
 * p2       The second point.
 *
 *
 * RETURN
 * d        The average absolute distance between p1 and p2.
 *
 * ------------------------------------------------------------------------- */
static double d(Point p1, Point p2){
  double x1 = (double)p1.x ;
  double y1 = (double)p1.y ;
  double x2 = (double)p2.x ;
  double y2 = (double)p2.y ;

  return 0.5*(fabs(x1 - x2)+fabs(y1 - y2)) ;
}
/* ========================================================================== */
/** ------------------------------------------------------------------------ *
 * Returns the maximum in a series of inputs (the number of inputs can vary)
 *
 * PARAMETERS
 * length       The number of inputs.
 * ...          The ellipsis () containing the inputs.
 *
 *
 * RETURN
 * max          The maximum element from the series of inputs.
 *
 * ------------------------------------------------------------------------- */
static double max(size_t length, ...){

  va_list valist;
  va_start(valist, length);
  double MAX = va_arg(valist, double);

  for(size_t i = 1; i < length; i++){
      double tmp = va_arg(valist, double);

      if(tmp > MAX)
          MAX = tmp ;
  }

  va_end(valist);

  return MAX;
}
/* ========================================================================== */
/** ------------------------------------------------------------------------ *
 * Returns the minimum in a series of inputs (the number of inputs can vary)
 *
 * PARAMETERS
 * length       The number of inputs.
 * ...          The ellipsis () containing the inputs.
 *
 *
 * RETURN
 * min          The minimum element from the series of inputs.
 *
 * ------------------------------------------------------------------------- */
static double min(size_t length, ...){

  va_list valist;
  va_start(valist, length);
  double MIN = va_arg(valist, double);

  for(size_t i = 1; i < length; i++){
      double tmp = va_arg(valist, double);

      if(tmp < MIN)
          MIN = tmp ;
  }

  va_end(valist);

  return MIN;
}
/*============================================================================*/
/*================================ FUNCTIONS =================================*/
/*============================================================================*/

// /* 2D point structure */
// typedef struct point_t {
//     int x, y;                // Coordinates of the point
// } Point;
//
// /* Sketch structure */
// typedef struct sketch_t {
//     int class;               // The class of this sketch
//     size_t size;             // The number of points of this sketch
//     bool* strokeStarts;      // strokeStarts[i] == 1 iff points[i] is the start
//                                                          // of a new polyline
//     Point* points;           // The array of points of this sketch
// } Sketch;


double dtw(Sketch sketch1, Sketch sketch2, double maxDistance) {
  // A optimiser !!!

  size_t n = sketch1.size ;
  size_t m = sketch2.size ;

  double **DTWmtx = (double**)malloc(n*sizeof(double*));
  for(size_t i = 0; i < n; i++)
      DTWmtx[i] = (double*)malloc(m*sizeof(double));

  for(size_t i = 0; i < n ; i++){
    for(size_t j = 0; j < m; j++){
        DTWmtx[i][j] = (double)INFINITY ;
    }
  }
  DTWmtx[0][0] = 0;

  for(size_t i = 1; i < n ; i++){
    for(size_t j = 1 ; j < m ; j++){
        double dist = d(sketch1.points[i], sketch2.points[j]);
        DTWmtx[i][j] = dist + min(3, DTWmtx[i-1][j],
                                     DTWmtx[i][j-1],
                                     DTWmtx[i-1][j-1]);
    }
  }

  return DTWmtx[n-1][m-1] ;
}
