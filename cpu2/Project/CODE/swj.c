/*
 * ���ܳ���λ��  qqȺ:297809802 qq1849057843
 */
#include "headfile.h"

/*
 * �޸�˵��:
 * sw_write_byte ȥ�Ҵ��ڿ��еķ����ֽں���
 * sw_write_buffer ȥ�� *���ߴ��� �� �еķ������麯��

 *
 * ���ʹ�õ���ɵĿ� �� ��ɵ�����ģ�� sw_write_buffer���ע��һ��
 * */

//--------------------------------------------------����ģ��-----------------------------------------------//
/*
 * ����ģ�� �Ƽ�ʹ����ɵ�����ģ�飨usb to nrf��*����ʱ����ͬʱ����ttl����������С��������ģ��
 * �����ʿ����������460800 *��ӦС���ϵĳ���,С��������ģ�飬�����ϵ�����ģ�飬��λ��������һ��
 * ����ģ���ٶȱ�wifi�� ���ŵ����ȶ� ���ڻҶ�ͼ���ٶȲ�̫���ã����ж�ֵ��ͼ���Ż� �ʺϱ�ͼ����ʾ����
 *
 */

//--------------ʾ����-------------------//
// name���ݱ�ʶ(ͨ��) dat:����
//��:int a=0;put_int32(0,a);

//����У�������ʾ��
void put_int32(uint8 name, int dat)
{
    uint8 datc[10] = {197, name, 1, 0, 0, 0, 0, 0, 0, 198};
    datc[3] = (uint8)(dat & 0xFF);
    datc[4] = (uint8)((dat & 0xFF00) >> 8);
    datc[5] = (uint8)((dat & 0xFF0000) >> 16);
    datc[6] = (uint8)((dat >> 24) & 0xFF);
    uint8 crc[6] = {name, 1, datc[3], datc[4], datc[5], datc[6]};
    uint16 CRC16 = swj_CRC(crc, 0, 6);
    datc[7] = (uint8)(CRC16 & 0xff);
    datc[8] = (uint8)(CRC16 >> 8);
    sw_write_buffer(datc, 10);
}

void put_float(uint8 name, float dat)
{
    uint8 datc[10] = {197, name, 2, 0, 0, 0, 0, 0, 0, 198};
    unsigned char *p = (unsigned char *)&dat + 3;
    datc[3] = *(p - 3);
    datc[4] = *(p - 2);
    datc[5] = *(p - 1);
    datc[6] = *p;
    uint8 crc[6] = {name, 2, datc[3], datc[4], datc[5], datc[6]};
    uint16 CRC16 = swj_CRC(crc, 0, 6);
    datc[7] = (uint8)(CRC16 & 0xff);
    datc[8] = (uint8)(CRC16 >> 8);
    sw_write_buffer(datc, 10);
}
//--------------�Ҷ�ͼ��-------------------//
//*imageͼ���ַ widthͼ��� heightͼ���
//����sendimg(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H);
void sendimg(uint8 *image, uint8 width, uint8 height)
{
    uint8 dat[6] = {0x21, 0x7A, width, height, 0x21, 0x7A};
    sw_write_buffer(dat, 6);
    sw_write_buffer(image, width * height);
}
//���б��ߵĻҶ�ͼ��

//����ѹ��ͼ�� ���� 120x180��ͼ��̫�� �����ٶ���  ����Է��� 60x90��ͼ��������ٶ�
//*imageͼ���ַ widthͼ��� heightͼ���dis_widthѹ�����ͼ��� dis_heightѹ�����ͼ���
//����sendimg(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H,MT9V03X_DVP_W/2,MT9V03X_DVP_H/2);
void sendimg_zoom(uint8 *image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height)
{
    uint8 dat[6] = {0x21, 0x7A, dis_width, dis_height, 0x21, 0x7A};
    sw_write_buffer(dat, 6);
    uint8 i, j;
    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            sw_write_byte(*(image + (j * height / dis_height) * width + i * width / dis_width)); //��ȡ���ص�
        }
    }
}
//--------------��ֵ��ͼ��-------------------//
// imageͼ���ַ widthͼ��� heightͼ��� otu��ֵ����ֵ
//����sendimg_binary(mt9v03x_image_dvp[0], MT9V03X_DVP_W, MT9V03X_DVP_H,100);
void sendimg_binary(uint8 *image, uint8 width, uint8 height, uint8 otu)
{

    uint8 dat[6] = {0x7A, 0x21, width, height, 0x7A, 0x21};
    sw_write_buffer(dat, 6);
    int databool = 255;
    uint8 lon = 1;
    int data = 255;
    uint8 line = 0, col = 0;

    for (line = 0; line < width; line++)
    {
        for (col = 0; col < height; col++)
        {
            if (*(image + line * height + col) > otu)
                data = 255;
            else
                data = 0;
            if (data == databool)
            {
                lon++;
            }
            else
            {
                sw_write_byte(lon);
                lon = 1;
            }
            if (lon == 190)
            {
                sw_write_byte(lon - 1);
                sw_write_byte(0);
                lon = 1;
            }
            databool = data;
        }
    }
}
//ѹ����ֵͼ��
// uint16 dis_width, uint16 dis_height Ҫѹ��ͼ���С
void sendimg_binary_zoom(uint8 *image, uint8 width, uint8 height, uint8 dis_width, uint8 dis_height, uint8 otu)
{

    uint8 dat[6] = {0x7A, 0x21, dis_width, dis_height, 0x7A, 0x21};
    sw_write_buffer(dat, 6);
    int databool = 255;
    uint8 lon = 1;
    int data = 255;
    uint8 i, j;
    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            if (*(image + (j * height / dis_height) * width + i * width / dis_width) > otu) //��ȡ���ص�
                data = 255;
            else
                data = 0;
            if (data == databool)
            {
                lon++;
            }
            else
            {
                sw_write_byte(lon);
                lon = 1;
            }
            if (lon == 190)
            {
                sw_write_byte(lon - 1);
                sw_write_byte(0);
                lon = 1;
            }
            databool = data;
        }
    }
}
//����У��Ķ�ֵͼ��
// chkֵԽ�� ������Խǿ ֵ0-55
//�����ʵ��ʹ��������е���
void sendimg_binary_CHK(uint8 *image, uint8 width, uint8 height, uint8 otu, uint8 chk)
{
    chk = chk > 0 ? chk : 0;
    chk = chk < 56 ? chk : 55;
    uint8 dat[7] = {0x7A, 0x21, width, height, 0x7A, 0x21, 200 + chk};
    sw_write_buffer(dat, 7);
    int databool = 255;
    uint8 lon = 0;
    int data = 255;
    uint8 line = 0, col = 0;
    int imglon = 0;
    int imgdatlo = width * height / chk;
    uint8 CHK = 0;
    for (line = 0; line < width; line++)
    {
        for (col = 0; col < height; col++)
        {
            imglon++;

            if (*(image + line * height + col) > otu)
                data = 255;
            else
                data = 0;
            if (data == databool)
            {
                lon++;
            }
            else
            {
                sw_write_byte(lon);
                lon = 1;
            }

            if (imglon == imgdatlo)
            {
                CHK++;
                sw_write_byte(lon);
                data = 255;
                databool = 255;
                sw_write_byte(200 + CHK);
                lon = 0;
                imglon = 0;
            }
            if (lon == 190)
            {
                sw_write_byte(lon);
                sw_write_byte(0);
                lon = 0;
            }
            databool = data;
        }
    }
}
//--------------����-------------------//
/*
 * ���Խ�Ѱ�ߵõ������ұ��ߣ�������߷��͵���λ���鿴
 * ���磺
 * ���� ͼ��img[H][W];�õ����ұ��ߴ����zx[H] yx[H] �����������Ϊw[H]
 * sendline_clear(swj_BLACK,H,W);//���� ������ɫ
 * sendline(swj_WHITE,zx,H);//���������
 * sendline(swj_WHITE,yx,H);//�����ұ���
 * sendline(swj_WHITE,wx,H);//��������
 * ���磺
 * sendline_clear(swj_BLACK,H,W);//���� ������ɫ
 * sendline_xy(zx,yx,H)//�������ұ���
 * sendline(swj_WHITE,wx,H);//��������
 *
 * ������������Ч��һ�µģ��������������λ���϶�Ӧʹ��������ԭ����
 * ע�⣺
 * ��ÿ������һ֡��ͼ����� ��Ҫ����sendline_clear��������
 * ���������sendline_xy������ʹ����λ��������ԭ����ʱ�����ٵ���sendline һ������sendline_xy���� ��ֹ������
 * */
#define swj_BLACK 0
#define swj_WHITE 1
#define swj_RED 2
#define swj_GREEN 3
#define swj_BLUE 4
#define swj_PURPLE 5
#define swj_YELLOW 6
#define swj_CYAN 7
#define swj_ORANGE 8
//�������   color������ı�����ɫ  uint16 width uint16 height ͼ��Ĵ�С
void sendline_clear(uint8 color, uint8 width, uint8 height)
{
    sw_write_byte(0x21);
    sw_write_byte(0x7A);
    sw_write_byte(width);
    sw_write_byte(height);
    sw_write_byte(color);
    sw_write_byte(0x21);
}
//ͼ�������߽�  uint8_t *zx:��߽�   uint8_t *yx:�ұ߽�, uint32_t len���͵ı��߳���
//�ú������·ź����ֱ������������кβ�ͬ? �ú����ɶ�Ӧ��λ����ԭ�����Ĺ���*  ע���Ⱥ�˳��
void sendline_xy(uint8 *line_zx, uint8 *line_yx, uint32 len)
{
    sw_write_byte(0x21);
    sw_write_byte(9);
    sw_write_byte(len);
    sw_write_byte(255);
    sw_write_byte(255);
    sw_write_buffer(line_zx, len);
    sw_write_buffer(line_yx, len);
}
/*Ĭ��ÿ��һ����*/
//���Ʊ���   color������ɫ  uint8_t *buff ���͵ı��������ַ  len���͵ı��߳���
void sendline(uint8 color, uint8 *buff, uint32 len)
{
    sw_write_byte(0x21);
    sw_write_byte(color);
    sw_write_byte(len);
    sw_write_byte(255);
    sw_write_byte(255);
    sw_write_buffer(buff, len);
}
/*˵��:
 * ������������ a(x1,y1)b(x2,y2)c(x3,y3)
 * �� uint8 x[3]={x1,x2,x3};uint8 y[3]={y1,y2,y3};
 *  sendline2(swj_WHITE,x,y,3);
 *  sendline����ֻ�ܰ�˳��ÿ��һ�㷢�ͱ߽��
 *  sendline2��������ڰ������ ÿ�в��̶������ı߽�
 *           Ҳ�����ڷ�������� ����յ� �������
 *
 * */
//������Ʊ���  color������ɫ linex��Ӧ���x���꼯�� liney��Ӧ���y���꼯��  len���͵ı��߳���
void sendline2(uint8 color, uint8 *linex, uint8 *liney, uint32 len)
{
    sw_write_byte(0x21);
    sw_write_byte(color);
    sw_write_byte(len);
    sw_write_byte(254);
    sw_write_byte(255);
    sw_write_buffer(linex, len);
    sw_write_buffer(liney, len);
}
/*
 * ����ģ��������߲����ʣ� �Ա��ٷ���������������� ���Ը��Źٷ��ֲ���Ľ̳���
 * ����������߲����ʣ� ���ڳ�ʼ��������
 * �ٶ�̫����ô�죿�ٽ�������������ߢ��Ƽ�ʹ�ö�ֵ��ͼ��
 * */

//--------------------------------------------------wifiģ��-----------------------------------------------//
/*
 *
 * ��Ƭ��-����-wifi-tcp(udp)-��λ�� ��Ҳ�ǽ�����ͨ�����ڷ��͵�wifiģ����
 * �Ƽ�hc-25(tcp ��ֵ�� ʾ��) Pic -o link(udp �Ҷ�)
 *
 */

void sendimg_WIFI(uint8 *image, uint8 width, uint8 height)
{

    sw_write_byte(0x21);
    sw_write_byte(0x7A);
    sw_write_byte(width);
    sw_write_byte(height);
    sw_write_byte(0x21);
    sw_write_byte(0x7A);

    uint8 line = 0, col = 0;
    for (line = 0; line < width; line++)
    {
        sw_write_byte(21);
        sw_write_byte(line);
        sw_write_byte(133);
        for (col = 0; col < height; col++)
        {
            sw_write_byte(*(image + line * height + col));
        }
    }
}
//����У��Ķ�ֵͼ��
// chkֵԽ�� ������Խǿ ֵ0-55
void sendimg_WIFI_binary_CHK(uint8 *image, uint8 width, uint8 height, uint8 otu, uint8 chk)
{
    chk = chk > 0 ? chk : 0;
    chk = chk < 56 ? chk : 55;

    sw_write_byte(0x7A);
    sw_write_byte(0x21);
    sw_write_byte(width);
    sw_write_byte(height);
    sw_write_byte(0x7A);
    sw_write_byte(0x21);
    sw_write_byte(200 + chk);
    int databool = 255;
    uint8 lon = 0;
    int data = 255;
    uint8 line = 0, col = 0;
    int imglon = 0;
    int imgdatlo = width * height / chk;
    uint8 CHK = 0;
    for (line = 0; line < width; line++)
    {
        for (col = 0; col < height; col++)
        {
            imglon++;

            if (*(image + line * height + col) > otu)
                data = 255;
            else
                data = 0;
            if (data == databool)
            {
                lon++;
            }
            else
            {
                sw_write_byte(lon);
                lon = 1;
            }

            if (imglon == imgdatlo)
            {
                CHK++;
                sw_write_byte(lon);
                data = 255;
                databool = 255;
                sw_write_byte(200 + CHK);
                lon = 0;
                imglon = 0;
            }
            if (lon == 190)
            {
                sw_write_byte(lon);
                sw_write_byte(0);
                lon = 0;
            }
            databool = data;
        }
    }
}

//--------------ʾ����-------------------//
// name���ݱ�ʶ(ͨ��) dat:����
//��:int a=0;put_int32(0,a);

void put_int32_WIFI(uint8 name, int dat)
{
    uint8 datc[10] = {197, name, 1, 0, 0, 0, 0, 0, 0, 198};
    datc[3] = (uint8)(dat & 0xFF);
    datc[4] = (uint8)((dat & 0xFF00) >> 8);
    datc[5] = (uint8)((dat & 0xFF0000) >> 16);
    datc[6] = (uint8)((dat >> 24) & 0xFF);
    uint8 crc[6] = {name, 1, datc[3], datc[4], datc[5], datc[6]};
    uint16 CRC16 = swj_CRC(crc, 0, 6);
    datc[7] = (uint8)(CRC16 & 0xff);
    datc[8] = (uint8)(CRC16 >> 8);
    sw_write_buffer(datc, 10);
}

void put_float_WIFI(uint8 name, float dat)
{
    uint8 datc[10] = {197, name, 2, 0, 0, 0, 0, 0, 0, 198};
    unsigned char *p = (unsigned char *)&dat + 3;
    datc[3] = *(p - 3);
    datc[4] = *(p - 2);
    datc[5] = *(p - 1);
    datc[6] = *p;
    uint8 crc[6] = {name, 2, datc[3], datc[4], datc[5], datc[6]};
    uint16 CRC16 = swj_CRC(crc, 0, 6);
    datc[7] = (uint8)(CRC16 & 0xff);
    datc[8] = (uint8)(CRC16 >> 8);
    sw_write_buffer(datc, 10);
}

//�ڲ�����
uint16 swj_CRC(uint8 *Buf, uint8 CRC_sta, uint8 CRC_CNT)
{
    uint16 CRC_Temp;
    uint8 i, j;
    CRC_Temp = 0xffff;

    for (i = CRC_sta; i < CRC_CNT; i++)
    {
        CRC_Temp ^= Buf[i];
        for (j = 0; j < 8; j++)
        {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >> 1) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return (CRC_Temp);
}
int32 ByteToInt(int8 *ndsk)
{
    int32 m = 0;
    int8 *h = (int8 *)&m;
    h[0] = ndsk[0];
    h[1] = ndsk[1];
    h[2] = ndsk[2];
    h[3] = ndsk[3];

    if (0 == m)
    {
        m = 1;
    }

    return m;
}
float ByteToFloat(unsigned char *byteArry)
{
    return *((float *)byteArry);
}
