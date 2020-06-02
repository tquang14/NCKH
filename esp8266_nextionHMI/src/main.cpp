#include <Arduino.h>
#include "SoftwareSerial.h"
#include "SD.h"
#include "SPI.h"
#include "Nextion.h"

#define passMaxLen 10
#define led 2
const char *defaultPass = "1401";
NexButton bEnter = NexButton(0, 13, "bEnter");
NexText inptTxt = NexText(0, 1, "inptTxt");
NexVariable pass = NexVariable(0, 14, "pass");
NexTouch *listenList[] = {&bEnter, NULL};
void bEnterPressed(void *ptr);
void setup() {
  // put your setup code here, to run once:
  nexInit();
  nexSerial.begin(9600);
  bEnter.attachPop(bEnterPressed, &bEnter);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  nexLoop(listenList);
}

void bEnterPressed(void *ptr) {
  char *buff = (char*)malloc(sizeof(char) * (passMaxLen + 1));
  uint32_t retLen = pass.getText(buff, (passMaxLen + 1));
  // buffer will get some redundancy bytes need to remove
  char *retPass = (char*)malloc(sizeof(char) * (passMaxLen + 1));
  for (int i = 0; i < retLen; i++)
  {
    retPass[i] = buff[i];
  }
  retPass[retLen] = '\0';
  if (!strcmp(retPass, defaultPass))
    digitalWrite(led, !digitalRead(led));
  pass.setText("");
  free(buff);
  free(retPass);
}