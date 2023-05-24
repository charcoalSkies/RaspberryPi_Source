/*copyright*/

#ifndef JSON_H_
#define JSON_H_

#include <json-c/json.h>

struct SENSORS {
  char* led;  // LED 사용 여부

  char* buzzer_usage;  // 부저 사용 여부
  char* buzzer_hertz;  // 부저 주파수

  char* motor_usage;  // 모터 사용 여부
  char* motor_angle;  // 모터 각도

  char* lcd_usage;  // LCD 사용 여부
  char* lcd_text;   // LCD 출력 텍스트

  char* sound;  // 소리 센서 값
  char* light;  // 조도 센서 값
} typedef sensors;

// JSON 데이터를 파싱하는 함수
sensors json_parser(json_object* data);

// 문자열을 자르는 함수
char* str_slicing(char* s, int start, int end);

#endif  // JSON_H_
