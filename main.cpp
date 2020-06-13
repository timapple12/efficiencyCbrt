#include <stdio.h>
#include <math.h>
#include <ctime>
#include <xmmintrin.h>

using namespace std;

float cbrt_f(double number){

  float n=number;
  double result;
  double fraction;
  int exponent;
  int shx;
  if(number==0){
    return 0;
  }
  if(number<0){
    number=-number;
  }
  float x=0;
  float y=1;
  float h=0.0000001;


    fraction = frexp(number, &exponent);
    shx = exponent % 3;
    if (shx > 0) {
      shx -= 3;
    }
    exponent = (exponent - shx) / 3.0f;
    printf("%i\n",exponent);
    fraction = ldexp(fraction, shx);
    fraction = 2.2789164958172441577749231688981350+(-2.9490015573458797575689646419590799+1.7327200102199398501700376844679917*fraction)*fraction;
    result = ldexp(fraction, exponent);
    /** Використовуємо приближення Ньютона-Рапсона
   * використовуємо змінні типу float для того щоб прискорити виконання алгоритму
   * **/
    result = (float)(2.0 / 3.0) * result +
             (float)(1.0 / 3.0) * number * (1 / (result * result));
    result = (float)(2.0 / 3.0) * result +
             (float)(1.0 / 3.0) * number * (1 / (result * result));

  return  n>0?result:-result;
}
void errors(){
  float min=INFINITY;
  double max=-INFINITY;

  float min2=INFINITY;
  float max2=-INFINITY;

  float min3=INFINITY;
  float max3=-INFINITY;
  float x=1.0f;
  float y=8.0f;
  float z= 1.01f;
  double result;
  float fraction;
  int exponent;
  int shx;
  float tr=(float)(2.0/3.0);
  float t=(float)(1.0/3.0);
  while(x<y) {
    while (x < z) {

      fraction = frexp(x, &exponent);
      shx = exponent % 3;
      if (shx > 0) {
        shx -= 3;
      }
      exponent = (exponent - shx) * t;
      fraction = ldexp(fraction, shx);
      fraction = 2.2789164958172441577749231688981350+(-2.9490015573458797575689646419590799+1.7327200102199398501700376844679917*fraction)*fraction;
      result = ldexp(fraction, exponent);
      float rez3 = (result / cbrt(x)) - 1;
      result = tr * result + t * x * (1 / (result * result));
      float rez2 = (result / cbrt(x)) - 1;
      result = tr * result + t * x * (1 / (result * result));

      float rez = (result / cbrt(x)) - 1;
      if (rez > max) {
        max = rez;
      }
      if (rez < min) {
        min = rez;
      }

      if (rez2 > max2) {
        max2 = rez2;
      }
      if (rez2 < min2) {
        min2 = rez2;
      }

      if (rez3 > max3) {
        max3 = rez3;
      }
      if (rez3 < min3) {
        min3 = rez3;
      }

      // printf("%.40f\n",x);
      x = nextafterf(x, z);
    }
    z += 0.01f;

    //printf("(%.20f;%f)\n", x, y);
   // printf("%.20f\n", min3);
   // printf("%.20f\n", max3);
    //printf("%.20f\n", min2);
    //printf("%.20f\n", max2);

   // printf("%.20f\n", min);
    printf("%.20f\n", max);

    min=INFINITY;
    max=-INFINITY;
    min2=INFINITY;
    max2=-INFINITY;
    min3=INFINITY;
    max3=-INFINITY;
  }
}
float cb(float numb){
  float number;
  float x=0;
  float y=1;
  float h=0.0000001;

  while(x<y) {
    x += h;
    number = pow(numb, 1.0f / 3.0f);
  }
  return number;
}
float cbr(float numb){

  float number;
  float x=0;
  float y=1;
  float h=0.0000001;
  while(x<y) {
    x+=h;
    number = cbrt(numb);
  }
  return number;
}
int main() {
  float start_time =  clock();
  printf("%.50f\n",cbrt_f(15));
  float end_time = clock();
  float search_time = end_time - start_time;
  printf("time = %.40f",search_time/(1000));

  return 0;
}