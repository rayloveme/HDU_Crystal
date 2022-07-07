/*
 * All rights reserved.
 * @file       		mymath.c
 * @brief         抄来的数学库
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-6-26
 * @note
 */

#include "headfile.h"

/********************************************************************************************************/
/*                                               mymath                                                 */
/********************************************************************************************************/
//int16 Math_Abs(int16 value) //求绝对值
//{
//  if (value < 0)
//  {
//    return -value;
//  }
//  else
//  {
//    return value;
//  }
//}
//
//float Math_Sign(float value, float range) //单位斜坡函数
//{
//  if (Math_Abs(value) < range)
//  {
//    return value / range;
//  }
//  else
//  {
//    if (value > 0)
//    {
//      return 1;
//    }
//    else if (value < 0)
//    {
//      return -1;
//    }
//    else
//    {
//      return 0;
//    }
//  }
//}
//
//float Math_Limit(float value, int limit) //限制幅度
//{
//  if (value > limit)
//  {
//    return limit;
//  }
//  else if (value < -limit)
//  {
//    return -limit;
//  }
//  else
//  {
//    return value;
//  }
//}
//float fast_atan_table[257] =
//    {
//        0.000000e+00, 3.921549e-03, 7.842976e-03, 1.176416e-02,
//        1.568499e-02, 1.960533e-02, 2.352507e-02, 2.744409e-02,
//        3.136226e-02, 3.527947e-02, 3.919560e-02, 4.311053e-02,
//        4.702413e-02, 5.093629e-02, 5.484690e-02, 5.875582e-02,
//        6.266295e-02, 6.656816e-02, 7.047134e-02, 7.437238e-02,
//        7.827114e-02, 8.216752e-02, 8.606141e-02, 8.995267e-02,
//        9.384121e-02, 9.772691e-02, 1.016096e-01, 1.054893e-01,
//        1.093658e-01, 1.132390e-01, 1.171087e-01, 1.209750e-01,
//        1.248376e-01, 1.286965e-01, 1.325515e-01, 1.364026e-01,
//        1.402496e-01, 1.440924e-01, 1.479310e-01, 1.517652e-01,
//        1.555948e-01, 1.594199e-01, 1.632403e-01, 1.670559e-01,
//        1.708665e-01, 1.746722e-01, 1.784728e-01, 1.822681e-01,
//        1.860582e-01, 1.898428e-01, 1.936220e-01, 1.973956e-01,
//        2.011634e-01, 2.049255e-01, 2.086818e-01, 2.124320e-01,
//        2.161762e-01, 2.199143e-01, 2.236461e-01, 2.273716e-01,
//        2.310907e-01, 2.348033e-01, 2.385093e-01, 2.422086e-01,
//        2.459012e-01, 2.495869e-01, 2.532658e-01, 2.569376e-01,
//        2.606024e-01, 2.642600e-01, 2.679104e-01, 2.715535e-01,
//        2.751892e-01, 2.788175e-01, 2.824383e-01, 2.860514e-01,
//        2.896569e-01, 2.932547e-01, 2.968447e-01, 3.004268e-01,
//        3.040009e-01, 3.075671e-01, 3.111252e-01, 3.146752e-01,
//        3.182170e-01, 3.217506e-01, 3.252758e-01, 3.287927e-01,
//        3.323012e-01, 3.358012e-01, 3.392926e-01, 3.427755e-01,
//        3.462497e-01, 3.497153e-01, 3.531721e-01, 3.566201e-01,
//        3.600593e-01, 3.634896e-01, 3.669110e-01, 3.703234e-01,
//        3.737268e-01, 3.771211e-01, 3.805064e-01, 3.838825e-01,
//        3.872494e-01, 3.906070e-01, 3.939555e-01, 3.972946e-01,
//        4.006244e-01, 4.039448e-01, 4.072558e-01, 4.105574e-01,
//        4.138496e-01, 4.171322e-01, 4.204054e-01, 4.236689e-01,
//        4.269229e-01, 4.301673e-01, 4.334021e-01, 4.366272e-01,
//        4.398426e-01, 4.430483e-01, 4.462443e-01, 4.494306e-01,
//        4.526070e-01, 4.557738e-01, 4.589307e-01, 4.620778e-01,
//        4.652150e-01, 4.683424e-01, 4.714600e-01, 4.745676e-01,
//        4.776654e-01, 4.807532e-01, 4.838312e-01, 4.868992e-01,
//        4.899573e-01, 4.930055e-01, 4.960437e-01, 4.990719e-01,
//        5.020902e-01, 5.050985e-01, 5.080968e-01, 5.110852e-01,
//        5.140636e-01, 5.170320e-01, 5.199904e-01, 5.229388e-01,
//        5.258772e-01, 5.288056e-01, 5.317241e-01, 5.346325e-01,
//        5.375310e-01, 5.404195e-01, 5.432980e-01, 5.461666e-01,
//        5.490251e-01, 5.518738e-01, 5.547124e-01, 5.575411e-01,
//        5.603599e-01, 5.631687e-01, 5.659676e-01, 5.687566e-01,
//        5.715357e-01, 5.743048e-01, 5.770641e-01, 5.798135e-01,
//        5.825531e-01, 5.852828e-01, 5.880026e-01, 5.907126e-01,
//        5.934128e-01, 5.961032e-01, 5.987839e-01, 6.014547e-01,
//        6.041158e-01, 6.067672e-01, 6.094088e-01, 6.120407e-01,
//        6.146630e-01, 6.172755e-01, 6.198784e-01, 6.224717e-01,
//        6.250554e-01, 6.276294e-01, 6.301939e-01, 6.327488e-01,
//        6.352942e-01, 6.378301e-01, 6.403565e-01, 6.428734e-01,
//        6.453808e-01, 6.478788e-01, 6.503674e-01, 6.528466e-01,
//        6.553165e-01, 6.577770e-01, 6.602282e-01, 6.626701e-01,
//        6.651027e-01, 6.675261e-01, 6.699402e-01, 6.723452e-01,
//        6.747409e-01, 6.771276e-01, 6.795051e-01, 6.818735e-01,
//        6.842328e-01, 6.865831e-01, 6.889244e-01, 6.912567e-01,
//        6.935800e-01, 6.958943e-01, 6.981998e-01, 7.004964e-01,
//        7.027841e-01, 7.050630e-01, 7.073330e-01, 7.095943e-01,
//        7.118469e-01, 7.140907e-01, 7.163258e-01, 7.185523e-01,
//        7.207701e-01, 7.229794e-01, 7.251800e-01, 7.273721e-01,
//        7.295557e-01, 7.317307e-01, 7.338974e-01, 7.360555e-01,
//        7.382053e-01, 7.403467e-01, 7.424797e-01, 7.446045e-01,
//        7.467209e-01, 7.488291e-01, 7.509291e-01, 7.530208e-01,
//        7.551044e-01, 7.571798e-01, 7.592472e-01, 7.613064e-01,
//        7.633576e-01, 7.654008e-01, 7.674360e-01, 7.694633e-01,
//        7.714826e-01, 7.734940e-01, 7.754975e-01, 7.774932e-01,
//        7.794811e-01, 7.814612e-01, 7.834335e-01, 7.853983e-01,
//        7.853983e-01};
//
//float my_abs(float f)
//{
//  if (f >= 0.0f)
//  {
//    return f;
//  }
//
//  return -f;
//}
//
//REAL fast_atan2(REAL y, REAL x)
//{
//  REAL x_abs, y_abs, z;
//  REAL alpha, angle, base_angle;
//  int index;
//
//  /* don't divide by zero! */
//  if ((y == 0.0f) || (x == 0.0f)) // if ((y == 0.0f) && (x == 0.0f))
//    angle = 0.0f;
//  else
//  {
//    /* normalize to +/- 45 degree range */
//    y_abs = my_abs(y);
//    x_abs = my_abs(x);
//    // z = (y_abs < x_abs ? y_abs / x_abs : x_abs / y_abs);
//    if (y_abs < x_abs)
//      z = y_abs / x_abs;
//    else
//      z = x_abs / y_abs;
//    /* when ratio approaches the table resolution, the angle is */
//    /*      best approximated with the argument itself...       */
//    if (z < TAN_MAP_RES)
//      base_angle = z;
//    else
//    {
//      /* find index and interpolation value */
//      alpha = z * (REAL)TAN_MAP_SIZE - .5f;
//      index = (int)alpha;
//      alpha -= (REAL)index;
//      /* determine base angle based on quadrant and */
//      /* add or subtract table value from base angle based on quadrant */
//      base_angle = fast_atan_table[index];
//      base_angle += (fast_atan_table[index + 1] - fast_atan_table[index]) * alpha;
//    }
//
//    if (x_abs > y_abs)
//    { /* -45 -> 45 or 135 -> 225 */
//      if (x >= 0.0f)
//      { /* -45 -> 45 */
//        if (y >= 0.0f)
//          angle = base_angle; /* 0 -> 45, angle OK */
//        else
//          angle = -base_angle; /* -45 -> 0, angle = -angle */
//      }
//      else
//      { /* 135 -> 180 or 180 -> -135 */
//        angle = 3.14159265358979323846;
//
//        if (y >= 0.0f)
//          angle -= base_angle; /* 135 -> 180, angle = 180 - angle */
//        else
//          angle = base_angle - angle; /* 180 -> -135, angle = angle - 180 */
//      }
//    }
//    else
//    { /* 45 -> 135 or -135 -> -45 */
//      if (y >= 0.0f)
//      { /* 45 -> 135 */
//        angle = 1.57079632679489661923;
//
//        if (x >= 0.0f)
//          angle -= base_angle; /* 45 -> 90, angle = 90 - angle */
//        else
//          angle += base_angle; /* 90 -> 135, angle = 90 + angle */
//      }
//      else
//      { /* -135 -> -45 */
//        angle = -1.57079632679489661923;
//
//        if (x >= 0.0f)
//          angle += base_angle; /* -90 -> -45, angle = -90 + angle */
//        else
//          angle -= base_angle; /* -135 -> -90, angle = -90 - angle */
//      }
//    }
//  }
//
//float Math_Max(float value1, float value2) //求最大值
//{
//  if (value1 > value2)
//  {
//    return value1;
//  }
//  else
//  {
//    return value2;
//  }
//}
//
//float Math_Min(float value1, float value2) //求最小值
//{
//  if (value1 > value2)
//  {
//    return value2;
//  }
//  else
//  {
//    return value1;
//  }
//}
//
//float Math_Hysteresis(float value, float Hys_range) //迟滞函数
//{
//  static uint8_t Hys_Flag = 0;
//  if (Hys_Flag)
//  {
//    if (value > -Hys_range)
//    {
//      Hys_Flag = 0;
//      return 1;
//    }
//    else
//    {
//      return -1;
//    }
//  }
//  if (!Hys_Flag)
//  {
//    if (value < Hys_range)
//    {
//      Hys_Flag = 1;
//      return -1;
//    }
//    else
//    {
//      return 1;
//    }
//  }
//  return 0;
//}
///****************************************************/
///*函数功能：快速求ln(x)*/
///*函数特点：cnt为运算次数*/
///*函数特点：减少运算量，并提高运算速度*/
///*函数注意：为增加运算速度可以将double改为float*/
///****************************************************/
//double Math_In(double Value, int cnt)
//{
//  int i = 0;
//  double tmp = (Value - 1) / (Value + 1);
//  double func = 0;
//  for (i = cnt; i >= 0; i--)
//  {
//    func = func * tmp + 1 / (2 * i + 1); //秦九昭算法求多项式值
//  }
//  func = func * tmp * 2;
//  return func;
//}
//
///****************************************************/
///*函数功能：泰勒展开级数求sin(x)*/
///*函数注意：要求绝对误差小Q=0.775,P=0.225，相对误差小 Q=0.782,P=0.218，输入为弧度不是角度*/
///*函数注意：为增加运算速度可以将double改为float*/
///****************************************************/
//double Math_sin(double Value)
//{
//  const double P = 0.225;         // Q=0.775;// Q=0.782,P=0.218
//  const double div4PI = 1.27324;  // 4/PI
//  const double div4PI2 = 0.40528; //-4/PI/PI
//  double func;
//  const double mPI = 3.14159; // 4/PI
//  while (Math_Abs(Value) >= mPI)
//  {
//    if (Value > 0)
//    {
//      Value = Value - mPI;
//    }
//    else
//    {
//      Value = Value + mPI;
//    }
//  }
//  func = div4PI * Value - div4PI2 * Value * Math_Abs(Value);
//  func = P * (func * Math_Abs(func) - func) + func;
//  return func;
//}
//
///****************************************************/
///*函数功能：泰勒展开级数求cos(x)*/
///*函数注意：要求绝对误差小Q=0.775,P=0.225，相对误差小 Q=0.782,P=0.218，输入为弧度不是角度*/
///*函数注意：为增加运算速度可以将double改为float*/
///****************************************************/
//double Math_cos(double Value)
//{
//  const double div2PI = 1.57080;
//  return Math_sin(div2PI - Value);
//}
//
///****************************************************/
///*函数功能：迭代法求sqrt(a)*/
///*函数特点：cnt为运算次数*/
///*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
///****************************************************/
//double Math_Sqrt(double Value, int cnt)
//{
//  int i = 0;
//  double tmp;
//  double func = 0;
//  for (i = cnt; i >= 0; i--)
//  {
//    tmp = (tmp + Value / tmp) / 2; //迭代法求多项式值
//  }
//  func = tmp;
//  return func;
//}
//
///****************************************************/
///*函数功能：迭代法求勒让德多项式值*/
///*函数特点：n为运算次数*/
///*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
///****************************************************/
//
//float LegendreP(int n, float Value)
//{
//  if (n == 0)
//  {
//    return 1;
//  }
//  else if (n == 1)
//  {
//    return Value;
//  }
//  else
//  {
//    return (float)((2 * n - 1) * Value * LegendreP(n - 1, Value) - (n - 1) * LegendreP(n - 2, Value)) / n;
//  }
//}
//
///****************************************************/
///*函数功能：迭代法求拉盖尔多项式值*/
///*函数特点：n为运算次数*/
///*函数注意：当alpha!=0时该算法自动转换为广义拉盖尔*/
///*函数注意：为增加运算速度可以将double改为float,并且输入值可以适当归一化*/
///****************************************************/
//double LaguerreL(int N, double alpha, double Value)
//{
//  int i;
//  double Lagu = 1, Bin = 1;
//  for (i = N; i > 0; i--) //使用秦九昭算法
//  {
//    Bin = Bin * (alpha + i) / (N + 1 - i);
//    Lagu = Bin - Value * Lagu / i;
//  }
//  return Lagu;
//}
///********************************************************************************************************/
///*                                               Buffer                                                 */
///********************************************************************************************************/
//
//float FIFO(double data_in, double *data_out, int DATACNT) //先入先出寄存器
//{
//  int i;
//
//  float result;
//
//  result = *(data_out + DATACNT - 1);
//
//  for (i = 1; i < DATACNT; i++)
//  {
//
//    *(data_out + i) = *(data_out + i - 1); //对数据进行移位操作
//  }
//
//  *data_out = data_in;
//
//  return result; //返还先入先出结果
//}
//
///********************************************************************************************************/
///*                                               Filter                                                 */
///********************************************************************************************************/
//
//float Kalman_Buffer(float *Data, int DataCnt) //卡曼滤波
//{
//  float kg, x_mid, x_now, x_last, p_mid, p_now;
//
//  static float p_last = 10;
//
//  const float Q = 100;
//
//  const float R = 1;
//
//  int i;
//
//  for (i = 0; i < DataCnt; i++)
//  { // x(k|k-1)=F(k)*x^(k-1|k-1)+B(k)*u(k-1)   //隐含条件
//
//    x_mid = x_last; // x_last=x(k-1|k-1),   x_mid=x(k|k-1)
//
//    p_mid = p_last + Q; // p_mid=p(k|k-1),      p_last=p(k-1|k-1),Q=噪声  //F(k)=1 H(k)=1
//
//    kg = p_mid / (p_mid + R); // kg为kalman filter，R为噪声      //kg=p(k|k-1)/(p(k|k-1)+R(k))
//
//    x_now = x_mid + kg * (*(Data + i) - x_mid); //估计出的最优值       //e(k)=y(k)-x(k|k-1)      //x^(k)=x(k|k-1)+Kg*e(k)
//
//    p_now = (1 - kg) * p_mid; //最优值对应的covariance   //p(k|k)=(1-kg)*p(k|k-1)
//
//    p_last = p_now; //更新covariance值
//
//    x_last = x_now; //更新系统状态值
//  }
//
//  return x_now;
//}
//
//int kalman_ACC1(int data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const int q = 5;
//  const int r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
//int kalman_ACC2(int data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const int q = 5;
//  const int r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
//int kalman_GYRO1(int data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const int q = 3;
//  const int r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
//int kalman_GYRO2(int data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const int q = 5;
//  const int r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
//int kalman_OUT(int data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const int q = 2;
//  const int r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
//float kalman_Steer(float data)
//{
//  static float p1 = 6;
//  static float c1 = 5;
//  const float q = 5;
//  const float r = 10;
//  float kg, c2, p2;
//
//  p2 = p1 + q;
//  kg = p2 * p2 / (p2 * p2 + r * r);
//  c2 = c1 + kg * (data - c1);
//  p1 = (1 - kg) / p2;
//  c1 = c2;
//
//  return c1;
//}
//
////数字滤波
//float Buffer(float data)
//{
//  static float Y[5];
//  static float YBuffer[5];
//
//  YBuffer[0] = YBuffer[1];
//  YBuffer[1] = YBuffer[2];
//  YBuffer[2] = YBuffer[3];
//  YBuffer[3] = YBuffer[4];
//  YBuffer[4] = data;
//
//  Y[0] = Y[1];
//  Y[1] = Y[2];
//  Y[2] = Y[3];
//  Y[3] = Y[4];
//  Y[4] = 0.0022 * YBuffer[4] + 0.0089 * YBuffer[3] + 0.0134 * YBuffer[2] + 0.0089 * YBuffer[1] + 0.0022 * YBuffer[0] - (0.2645 * Y[0] - 1.4035 * Y[1] + 2.8674 * Y[2] - 2.6926 * Y[3]);
//  return Y[4];
//}
