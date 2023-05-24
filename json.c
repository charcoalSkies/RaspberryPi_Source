/*Copyright*/
#include "./json.h"

sensors json_parser(json_object *data) 
{
    json_object* led_data = json_object_object_get(data, "LED");

    json_object* buzzer_data = json_object_object_get(data, "BUZZER");
    json_object* buzzer_usage = json_object_object_get(buzzer_data, "usage");
    json_object* buzzer_hertz = json_object_object_get(buzzer_data, "hertz");

    json_object* motor_data = json_object_object_get(data, "MOTOR");
    json_object* motor_usage = json_object_object_get(motor_data, "usage");
    json_object* motor_angle = json_object_object_get(motor_data, "angle");

    json_object* lcd_data = json_object_object_get(data, "LCD");
    json_object* lcd_usage = json_object_object_get(lcd_data, "usage");
    json_object* lcd_text = json_object_object_get(lcd_data, "text");

    json_object* sound_data = json_object_object_get(data, "SOUND");
    json_object* light_data = json_object_object_get(data, "LIGHT");

    sensors sensor = {0, };

    sensor.led = json_object_get_string(led_data);
    
    sensor.buzzer_usage = json_object_get_string(buzzer_usage);
    sensor.buzzer_hertz = json_object_get_string(buzzer_hertz);
    
    sensor.motor_usage = json_object_get_string(motor_usage);
    sensor.motor_angle = json_object_get_string(motor_angle);

    sensor.lcd_usage = json_object_get_string(lcd_usage);
    sensor.lcd_text = json_object_get_string(lcd_text);
    
    sensor.sound = json_object_get_string(sound_data);
    sensor.light = json_object_get_string(light_data);

    return sensor;
}

char* str_slicing(char* s, int start, int end) 
{
    // 시작과 끝 인덱스를 이용하여 문자열의 크기를 계산
    int str_size = end - start;
    // 슬라이싱된 문자열을 저장할 포인터 변수를 동적 할당
    char* slice_str = (char*)malloc(sizeof(char) * str_size);

    // 슬라이싱된 문자열을 생성
    for (int i = 0; i < str_size; i++) {
      slice_str[i] = s[start + i];
    }

    // 슬라이싱된 문자열을 반환
    return slice_str;
}
