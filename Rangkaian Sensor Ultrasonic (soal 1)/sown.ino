#include <Arduino_FreeRTOS.h>
#define portCHAR char

void TaskHCSR(void *pvParameters);
void TaskBUZZon(void *pvParameters);
void TaskBUZZoff(void *pvParameters);
void TaskYEL(void *pvParameters);
void TaskREDon(void *pvParameters);
void TaskREDoff(void *pvParameters);

TaskHandle_t hcsrTask, buzzTaskON, buzzTaskOFF, yelTask, redTaskON, redTaskOFF;
uint32_t suspend_monitor;
uint32_t resume_monitor;

void setup(){
  Serial.begin(9600);
  xTaskCreate(TaskHCSR, (const portCHAR *)"HCSR",128, NULL, 1, &hcsrTask);
  xTaskCreate(TaskBUZZon, (const portCHAR *)"BUZZ ON",128, NULL, 1, &buzzTaskON);
  xTaskCreate(TaskBUZZoff, (const portCHAR *)"BUZZ OFF",128, NULL, 1, &buzzTaskOFF);
  xTaskCreate(TaskYEL, (const portCHAR *)"BUZZ OFF",128, NULL, 1, &yelTask);
  xTaskCreate(TaskREDon, (const portCHAR *)"BUZZ OFF",128, NULL, 1, &redTaskON);
  xTaskCreate(TaskREDoff, (const portCHAR *)"BUZZ OFF",128, NULL, 1, &redTaskOFF);
}

void loop(){

}

void TaskHCSR(void *pvParameters){
  (void) pvParameters;
  int pinTrig = 9;
  int pinEcho = 10;
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  for(;;){
    digitalWrite(pinTrig, LOW);
    vTaskDelay(2);
    digitalWrite(pinTrig, HIGH);
    vTaskDelay(10);
    digitalWrite(pinTrig, LOW);

    int duration = pulseIn(pinEcho, HIGH);
    int distance = duration/50.2;

    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");

    if(distance>50){
      vTaskSuspend(buzzTaskON);
      vTaskResume(buzzTaskOFF);
      vTaskSuspend(redTaskON);
      vTaskResume(redTaskOFF);
    }

    if(distance<=50){
      vTaskResume(buzzTaskON);
      vTaskSuspend(buzzTaskOFF);
      vTaskResume(buzzTaskON);
      vTaskSuspend(redTaskOFF);
    }
   
  }
}

void TaskBUZZon(void *pvParameters){
  (void) pvParameters;
  int pinBuzz = 13;
  pinMode(pinBuzz, OUTPUT);

  for(;;){
    digitalWrite(pinBuzz, HIGH);
    Serial.println("BUZZ ON");
    vTaskDelay(10);
  }
}

void TaskBUZZoff(void *pvParameters){
  (void) pvParameters;
  int pinBuzz = 13;
  pinMode(pinBuzz, OUTPUT);

  for(;;){
    digitalWrite(pinBuzz, LOW);
    Serial.println("BUZZ OFF");
    vTaskDelay(10);
  }
}

void TaskYEL(void *pvParameters){
  (void) pvParameters;
  int pinYel = 5;
  pinMode(pinYel, OUTPUT);

  for(;;){
    digitalWrite(pinYel, HIGH);
    vTaskDelay(50);
    digitalWrite(pinYel, LOW);
    vTaskDelay(50);
  }
}

void TaskREDon(void *pvParameters){
  (void) pvParameters;
  int pinRed = 6;
  pinMode(pinRed, OUTPUT);

  for(;;){
    digitalWrite(pinRed, HIGH);
    vTaskDelay(50);
  }
}

void TaskREDoff(void *pvParameters){
  (void) pvParameters;
  int pinRed = 6;
  pinMode(pinRed, OUTPUT);

  for(;;){
    digitalWrite(pinRed, LOW);
    vTaskDelay(50);
  }
}
