/*
 * All rights reserved.
 * @file       		imu.c
 * @brief               imu数据处理及姿态解算
 * @author     		ray
 * @Target core		MM32F3277
 * @date       		2022-5-22
 * @note
 */

#include "headfile.h"
#include "math.h"
//-------------------------------------------------------------------------------------------------------------------
//  @brief      陀螺仪初始化
//  @param      void
//  @return     void
//  @note
//  Sample usage:       IMU_Init();
//-------------------------------------------------------------------------------------------------------------------
void IMU_Init(void)
{
    icm20602_init_spi();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取IMU数值
//  @param      void
//  @return     void
//  @note
//  Sample usage:       IMU_Get();
//-------------------------------------------------------------------------------------------------------------------
void IMU_Get(void)
{

    get_icm20602_accdata_spi();
    get_icm20602_gyro_spi();
    icm_gyro_y = icm_gyro_y -8;
}

//float ang_acc = 0.0, ang_gyro = 0.0, ang = 0.0;
//int16 ang_con = 0;
//void angel_cacul(void)
//{
//    ang_acc = 57.29578 * (float)(atan2f(icm_acc_z, icm_acc_x)) + 125;
//    //    if(ang_acc>90)ang_acc=90;
//    //    if(ang_acc<-90)ang_acc=-90;
//    ang_gyro = (float)(ang_gyro + (icm_gyro_y * 1.0 - 10.0) * 0.00029386);
//    ang_gyro = ang_gyro + (ang_acc - ang_gyro) * 0.00425;
//    ang_con = ang_gyro * 100.0 - 100;
//}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      一阶互补滤波
//  @param      void
//  @return     void
//  @note
//  Sample usage:       Complementary_Filter();
//-------------------------------------------------------------------------------------------------------------------
int16 angle = 0;       //滤波后角度
int16 angle_final = 0; //换算后角度
void Complementary_Filter(void)
{
    static float p1 = 0.0800000, p2 = -0.01300000;
    angle = p1 * icm_acc_x + (1 - p1) * (angle + p2 * icm_gyro_y); //直立 ace x gyr y
    // angle -1000（抬头）到 -4000（低头）
    angle_final = angle + 4500;
    // angle_final 3800（抬头）1600（平衡）940（低头）
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      二阶卡尔曼滤波融合
//  @param      angle_m   角度
//  @param      gyro_m    角速度
//  @return     void
//  @note       卡尔曼滤波，得到最优估计的角度。
//  Sample usage:       IMU_Init();
//-------------------------------------------------------------------------------------------------------------------
void Kalman_Filter(float angle_m, float gyro_m)
{
    const float Q_angle = 0.001, Q_gyro = 0.001, R_angle = 5, dt = 0.005;
    //注意：dt的取值为kalman滤波器采样时间;Q增大，动态响应增大
    static float P[2][2] = {{1, 0}, {0, 1}};
    static float Pdot[4] = {0, 0, 0, 0};
    static float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;
    angle += (gyro_m - q_bias) * dt;
    Pdot[0] = Q_angle - P[0][1] - P[1][0];
    Pdot[1] = -P[1][1];
    Pdot[2] = -P[1][1];
    Pdot[3] = Q_gyro;
    P[0][0] += Pdot[0] * dt;
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;
    angle_err = angle_m - angle;
    PCt_0 = P[0][0];
    PCt_1 = P[1][0];
    E = R_angle + PCt_0;
    K_0 = PCt_0 / E;
    K_1 = PCt_1 / E;
    t_0 = PCt_0;
    t_1 = P[0][1];
    P[0][0] -= K_0 * t_0;
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;
    angle += K_0 * angle_err; //最终融合角度
    q_bias += K_1 * angle_err;
    //   angle_speed = gyro_m - q_bias;
}
