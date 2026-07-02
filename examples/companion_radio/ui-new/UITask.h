#pragma once

#include <MeshCore.h>
#include <helpers/ui/DisplayDriver.h>
#include <helpers/ui/UIScreen.h>
#include <helpers/SensorManager.h>
#include <helpers/BaseSerialInterface.h>
#include <Arduino.h>
#include <helpers/sensors/LPPDataHelpers.h>
#define UI_SENSORS_PAGE 1
#define ENV_INCLUDE_GPS 0
#ifndef LED_STATE_ON
  #define LED_STATE_ON 1
#endif

#ifdef PIN_BUZZER
  #include <helpers/ui/buzzer.h>
#endif
#ifdef PIN_VIBRATION
  #include <helpers/ui/GenericVibration.h>
#endif

#include "../AbstractUITask.h"
#include "../NodePrefs.h"

class UITask : public AbstractUITask {
  DisplayDriver* _display;
  SensorManager* _sensors;
#ifdef PIN_BUZZER
  genericBuzzer buzzer;
#endif
#ifdef PIN_VIBRATION
  GenericVibration vibration;
#endif
  unsigned long _next_refresh, _auto_off;
  NodePrefs* _node_prefs;
  char _alert[80];
  unsigned long _alert_expiry;
  int _msgcount;
  unsigned long ui_started_at, next_batt_chck;
  int next_backlight_btn_check = 0;
#ifdef PIN_STATUS_LED
  int led_state = 0;
  int next_led_change = 0;
  int last_led_increment = 0;
#endif

#ifdef PIN_USER_BTN_ANA
  unsigned long _analogue_pin_read_millis = millis();
#endif

  // ====== RGB LED СОСТОЯНИЯ ======
  bool m_isNetworkConnected = false;
  uint32_t m_lastStatusColor = 0;
  bool m_rgbLedEnabled = true;  // Включен ли RGB светодиод
  
  // Счетчики для разных типов сообщений
  int m_unreadChannelMessages = 0;  // Непрочитанные сообщения в каналах
  int m_unreadPrivateMessages = 0;  // Непрочитанные личные сообщения
  
  // Таймеры для мигания
  unsigned long m_lastBlinkTime = 0;
  bool m_isBlinking = false;
  // ================================

  UIScreen* splash;
  UIScreen* home;
  UIScreen* msg_preview;
  UIScreen* curr;

  void userLedHandler();

  // Button action handlers
  char checkDisplayOn(char c);
  char handleLongPress(char c);
  char handleDoubleClick(char c);
  char handleTripleClick(char c);

  void setCurrScreen(UIScreen* c);

public:

  UITask(mesh::MainBoard* board, BaseSerialInterface* serial) : AbstractUITask(board, serial), _display(NULL), _sensors(NULL) {
    next_batt_chck = _next_refresh = 0;
    ui_started_at = 0;
    curr = NULL;
  }
  void begin(DisplayDriver* display, SensorManager* sensors, NodePrefs* node_prefs);
  void showAlert(const char* text, int duration_millis);
  int  getMsgCount() const { return _msgcount; }
  bool hasDisplay() const { return _display != NULL; }
  bool isButtonPressed() const;

  bool isBuzzerQuiet() { 
#ifdef PIN_BUZZER
    return buzzer.isQuiet();
#else
    return true;
#endif
  }

  void toggleBuzzer();
  bool getGPSState();
  void toggleGPS();

  // from AbstractUITask
  void msgRead(int msgcount) override;
  void newMsg(uint8_t path_len, const char* from_name, const char* text, int msgcount) override;
  void notify(UIEventType t = UIEventType::none) override;
  void loop() override;

  void gotoHomeScreen() { 
  // Если мы были на экране сообщений - сбрасываем счетчики
    if (curr == msg_preview) {
    markAllMessagesRead();
    }
    setCurrScreen(home); 
  }
  void shutdown(bool restart = false);

  // ====== RGB LED МЕТОДЫ ======
  void onPrivateMessage(const char* from_name, const char* text);
  void onChannelMessage(const char* from_name, const char* text);
  void onMessageSent();
  void markAllMessagesRead();
  void markPrivateMessagesRead();
  void markChannelMessagesRead();
  // =============================
};