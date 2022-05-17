/*
 * C program to find maximum and minimum between two numbers or more numbers using functions
 */

#include <stdio.h>
#include <limits.h>
#include <stdarg.h>


/**
 * Find maximum between two or more integer variables
 * @param args Total number of integers
 * @param ... List of integer variables to find maximum
 * @return Maximum among all integers passed
 */
// int max(int args, ...)
// {
//     int i, max, cur;
//     va_list valist;
//     va_start(valist, args);
//
//     max = INT_MIN;
//
//     for(i=0; i<args; i++)
//     {
//         cur = va_arg(valist, int); // Get next elements in the list
//         if(max < cur)
//             max = cur;
//     }
//
//     va_end(valist); // Clean memory assigned by valist
//
//     return max;
// }

/**
 * Find minimum between two or more integer variables
 * @param args Total number of integers
 * @param ... List of integer variables to find minimum
 * @return Minimum among all integers passed
 */
// int min(int args, ...)
// {
//     int i, min, cur;
//     va_list valist;
//     va_start(valist, args);
//
//     min = INT_MAX;
//
//     for(i=0; i<args; i++)
//     {
//         cur = va_arg(valist, int);
//         if(min > cur)
//             min = cur;
//     }
//
//     va_end(valist);
//
//     return min;
// }


static double maxi(size_t length, ...){

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






int main(){

  double MAX = maxi(6,2.0,5.02,7.0,91.05,3.0,10.0);
  double MAX2 = maxi(6,2.0,5.02,7.0,9.0,3.0,10.0);
  double MAX3 = maxi(6,200.058,57.02,7.0,9.0,3.0,10.00902);
  printf("max is : %lf \n", MAX);
  printf("max is : %lf \n", MAX2);
  printf("max is : %lf \n", MAX3);
  return 0;
}
