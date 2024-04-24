#ifndef ADC_H
#define ADC_H

class ADC
{
public:
    static void init(); // 初始化 ADC 設定
    static int readYaw();
    static int readThrottle();
    static int readPitch();
    static int readRoll();
    static void readAll(int *yaw, int *throttle, int *pitch, int *roll);
};

#endif // ADC_H