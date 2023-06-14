#include "./main.h"

int main(int args, char** argv) 
{
    getCommand getcmd = { 0, }; // getCommand 구조체 변수 getcmd 선언 및 초기화
    sensors sensor = { 0, };    // sensors 구조체 변수 sensor 선언 및 초기화
    connection(&getcmd);        // Socket 연결 대기
    init_sensor();              // 센서 초기화
    uint8_t led_change = 0x00;
    while (true) 
    {
        json_object* data = json_object_object_get(getcmd.rootObj, "data"); // getcmd.rootObj에서 "data" 키에 해당하는 json_object를 가져옴
        sensor = json_parser(data); // 가져온 json_object를 파싱하여 sensor 변수에 저장함

        if (strcmps(sensor.led, "True") == 0) 
        {  
            led_change = ~led_change;            // led_change 값을 반전시킨다.
            led(led_change, getcmd);              // led_change 값을 이용하여 LED를 켜거나 끈다.
            led_change ? response("200", &getcmd) : response("LED OFF!", &getcmd);  // led_change 값에 따라 응답을 보낸다.
            led_change ? printf("LED ON!\n") : printf("LED OFF!\n");                    // led_change 값에 따라 콘솔에 출력한다.
        }

        if (strcmps(sensor.buzzer_usage, "True") == 0) 
        {  
            uint16_t HZ = (uint16_t)atoi(sensor.buzzer_hertz);  // buzzer_hertz 값을 정수형으로 변환하여 HZ에 저장한다.
            response("200", &getcmd);  
            printf("BUZZER ON! %d\n", HZ);  // 콘솔에 "BUZZER ON! HZ"를 출력한다.

            for (int i = 0; i < 3; i++) 
            {
                buzzer(HZ, getcmd);          // HZ 주파수로 부저를 울린다.
                delay(300);                  // 300ms 딜레이를 준다.
                HZ += 15;                    // HZ 값을 15 증가시킨다.
            }
            buzzer(0, getcmd);  // 부저를 끈다.
        }

        if (strcmps(sensor.motor_usage, "True") == 0)
        {
            printf("MotorMove! %d\n", atoi(sensor.motor_angle));  // 콘솔에 "MotorMove! motor_angle"를
                                             // 출력한다.
            response("Motor Move!", &getcmd);  // "Motor Move!" 응답을 보낸다.
            for (int i = 0; i < atoi(sensor.motor_angle); i++) {
                motor(i);
            }  // motor_angle 값만큼 모터를 회전시킨다.
        }

        // LCD 한줄에 최대 16자
        if (strcmps(sensor.lcd_usage, "True") == 0) 
        { 
            response(sensor.lcd_text, &getcmd);  // lcd_text 값을 응답으로 보낸다.
            if (strlen(sensor.lcd_text) > 16)  // 만약 lcd_text의 길이가 16보다 크면
            {  
                lcdLoc(LINE1);  // 첫 번째 줄에 커서를 위치시킨다.
                char* lcd_print1 = str_slicing( sensor.lcd_text, 0, 16);  // lcd_text의 0~15번째 문자열을 lcd_print1에 저장한다.
                typeln(lcd_print1);  // lcd_print1을 첫 번째 줄에 출력한다.

                char* lcd_print2 = str_slicing( sensor.lcd_text, 16, strlen(sensor.lcd_text) + 1);  // lcd_text의 16번째 이후 문자열을 lcd_print2에 저장한다.
                lcdLoc(LINE2);       // 두 번째 줄에 커서를 위치시킨다.
                typeln(lcd_print2);  // lcd_print2를 두 번째 줄에 출력한다.
                // delay(2000);
                // ClrLcd();

                // typeln("Int  ");
                // int value = 201904;
                // typeInt(value);

                // delay(2000);
                // lcdLoc(LINE2);
                // typeln("Float ");
                // float FloatVal = 10045.25989;
                // typeFloat(FloatVal);
                // delay(2000);
            }
        }
    }
}

void init_sensor() 
{
    if (wiringPiSetup() == -1) return -1;
    pinMode(LED_PIN, OUTPUT);    // LED_PIN을 출력으로 설정한다.
    softToneCreate(BUZZER_PIN);  // BUZZER_PIN을 소프트톤으로 설정한다.
    lcd_init();                  // LCD를 초기화한다.

    pinMode(MOTOR_PIN, OUTPUT);    // MOTOR_PIN을 출력으로 설정한다.
    motor_init(200);

    digitalWrite(MOTOR_PIN, LOW);  // MOTOR_PIN을 LOW로 설정한다.

    pinMode(LIGHTSEN_OUT, INPUT);  // LIGHTSEN_OUT을 입력으로 설정한다.

    pinMode(SOUND_IN, INPUT);  // SOUND_IN을 입력으로 설정한다.

    pinMode(TRIG_PIN, OUTPUT);  // TRIG_PIN을 출력으로 설정한다.
    pinMode(ECHO_PIN, INPUT);   // ECHO_PIN을 입력으로 설정한다.
}
