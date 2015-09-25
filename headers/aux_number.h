/*
  AUXILIARY CHAR FUNCTIONS

  Defined to help build-up a TRANSITION TABLE
*/

#ifndef AUX_CHAR_H
#define AUX_CHAR_H
 
  // reverses a string 'str' of length 'len'
  void reverse(char *str, int len);
   
   // Converts a given integer x to string str[].  d is the number
   // of digits required in output. If d is more than the number
   // of digits in x, then 0s are added at the beginning.
  int intToStr(int x, char str[], int d);
   
  void floatToStr(float n, char *res, int afterpoint);

#endif