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
    static void readAll(int16_t *yaw, int16_t *throttle, int16_t *pitch, int16_t *roll);
};

#endif // ADC_H