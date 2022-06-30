/*
 * All rights reserved.
 * @file       		imufilter_useless.c
 * @brief               imu��Ч�˲��㷨
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2021-11-30
 * @note                �о�һЩ�ô�������㷨�ͷ�������
 */

#include "headfile.h"

////-------------------------------------------------------------------------------------------------------------------
////  @brief      һ�׿������˲�
////  @param      ResrcData   ��Ҫ�˲���ֵ
////  @param      ProcessNiose_Q   ��������Q
////  @param      MeasureNoise_R   ��������R
////  @return     x_now   �˲����ֵ
////  @note
////  Sample usage:       KalmanFilter();
////-------------------------------------------------------------------------------------------------------------------
//#define KALMAN_Q 0.08	//��������0.01  0.01
//#define KALMAN_R 0.32	//��������0.5   0.3
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
//    p_mid=p_last+Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
//
//    /*
//     *  �������˲��������Ҫ��ʽ
//     */
//    kg=p_mid/(p_mid+R);                 //kgΪkalman filter��R Ϊ����
//    x_now= (1-kg) * x_mid+kg * ResrcData;   //���Ƴ�������ֵ
//    p_now= (1-kg) * p_mid;                 //����ֵ��Ӧ��covariance
//    p_last = p_now;                     //����covariance ֵ
//    x_last = x_now;                     //����ϵͳ״ֵ̬
//
//    return x_now;
//
//}



////���׻����˲�
//float Complementary2(float Angle_acc, float Angle_gyro)
//{
//  float k = 10;
//  float dt = 5;
//  //���´�����ĳɰ�ɫ�����غ�ָ���������ɫ���ɿ���
//  x1 = (Angle_acc - angle_out) * k * k;
//  y1 = dt * x1 + y1;
//  z1 = y1 + (Angle_acc - angle_out) * 2 * k + Angle_gyro;
//  angle_out = dt * z1 + angle_out;
//  return angle_out;
//}