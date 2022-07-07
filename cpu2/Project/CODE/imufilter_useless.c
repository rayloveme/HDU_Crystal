/*
 * All rights reserved.
 * @file       		imufilter_useless.c
 * @brief               imu无效滤波算法
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-30
 * @note                感觉一些用处不大的算法就放这里了
 */

#include "headfile.h"

////-------------------------------------------------------------------------------------------------------------------
////  @brief      一阶卡尔曼滤波
////  @param      ResrcData   需要滤波的值
////  @param      ProcessNiose_Q   过程噪声Q
////  @param      MeasureNoise_R   测量噪声R
////  @return     x_now   滤波后的值
////  @note
////  Sample usage:       KalmanFilter();
////-------------------------------------------------------------------------------------------------------------------
//#define KALMAN_Q 0.08	//过程噪声0.01  0.01
//#define KALMAN_R 0.32	//测量噪声0.5   0.3
// float KalmanFilter_1(const float ResrcData,float ProcessNiose_Q,float MeasureNoise_R)
//{
//
//    float R = MeasureNoise_R;
//    float Q = ProcessNiose_Q;
//
//    static float x_last;
//    float x_mid = x_last;
//    float x_now;
//
//    static float p_last;
//    float p_mid ;
//    float p_now;
//
//    float kg;
//
//    x_mid=x_last;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
//    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
//
//    /*
//     *  卡尔曼滤波的五个重要公式
//     */
//    kg=p_mid/(p_mid+R);                 //kg为kalman filter，R 为噪声
//    x_now= (1-kg) * x_mid+kg * ResrcData;   //估计出的最优值
//    p_now= (1-kg) * p_mid;                 //最优值对应的covariance
//    p_last = p_now;                     //更新covariance 值
//    x_last = x_now;                     //更新系统状态值
//
//    return x_now;
//
//}



////二阶互补滤波
//float Complementary2(float Angle_acc, float Angle_gyro)
//{
//  float k = 10;
//  float dt = 5;
//  //以下代码更改成白色，下载后恢复成其他颜色即可看到
//  x1 = (Angle_acc - angle_out) * k * k;
//  y1 = dt * x1 + y1;
//  z1 = y1 + (Angle_acc - angle_out) * 2 * k + Angle_gyro;
//  angle_out = dt * z1 + angle_out;
//  return angle_out;
//}