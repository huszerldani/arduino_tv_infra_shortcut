#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2
#define IR_SEND_PIN 4

#define DEBUG false

enum Key {
    KEY_UP = 0x60,
    KEY_DOWN = 0x61,
    KEY_LEFT = 0x65,
    KEY_RIGHT = 0x62,
    KEY_OK = 0x68,
    KEY_BACK = 0x58,
    KEY_HOME = 0x79,
    KEY_SETTINGS = 0x1A,
    KEY_A = 0x6C,
    KEY_B = 0x14,
    KEY_C = 0x15,
    KEY_D = 0x16,
};

bool turnOffReceiving = false;

// Define button sequences for shortcuts
int sleep60Shortcut[] = {
  KEY_SETTINGS,
  KEY_DOWN,KEY_DOWN,KEY_DOWN,KEY_DOWN,
  KEY_OK,KEY_OK,
  KEY_DOWN,
  KEY_OK,
  KEY_DOWN,KEY_DOWN,
  KEY_OK,
  KEY_SETTINGS,
  KEY_SETTINGS,
};

int sleep90Shortcut[] = {
  KEY_SETTINGS,
  KEY_DOWN,KEY_DOWN,KEY_DOWN,KEY_DOWN,
  KEY_OK,KEY_OK,
  KEY_DOWN,
  KEY_OK,
  KEY_DOWN,KEY_DOWN,KEY_DOWN,
  KEY_OK,
  KEY_SETTINGS,
  KEY_SETTINGS,
};

int darkenScreenShortcut[] = {
  KEY_SETTINGS,
  KEY_OK,
  KEY_DOWN,KEY_DOWN,KEY_DOWN,KEY_DOWN,
  KEY_OK, KEY_OK,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_DOWN,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_DOWN,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,KEY_LEFT,
  KEY_SETTINGS,
  KEY_SETTINGS,
  KEY_SETTINGS,
};

int lightScreenShortcut[] = {
  KEY_SETTINGS,
  KEY_OK,
  KEY_DOWN,KEY_DOWN,KEY_DOWN,KEY_DOWN,
  KEY_OK, KEY_OK,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_DOWN,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_DOWN,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,KEY_RIGHT,
  KEY_SETTINGS,
  KEY_SETTINGS,
  KEY_SETTINGS,
};

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  
  IrSender.begin(IR_SEND_PIN);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (!turnOffReceiving && IrReceiver.decode()) {
      // Check if the received value matches any shortcut keys
      if (IrReceiver.decodedIRData.command == KEY_A) {
        Serial.println("Sleep 60 mins shortcut pressed!");
        executeShortcut(sleep60Shortcut, sizeof(sleep60Shortcut) / sizeof(sleep60Shortcut[0]));
      }

      if (IrReceiver.decodedIRData.command == KEY_B) {
        Serial.println("Sleep 90 mins shortcut pressed!");
        executeShortcut(sleep90Shortcut, sizeof(sleep90Shortcut) / sizeof(sleep90Shortcut[0]));
      }

      if (IrReceiver.decodedIRData.command == KEY_C) {
        Serial.println("Darken screen shortcut pressed!");
        executeShortcut(darkenScreenShortcut, sizeof(darkenScreenShortcut) / sizeof(darkenScreenShortcut[0]));
      }

      if (IrReceiver.decodedIRData.command == KEY_D) {
        Serial.println("Light screen shortcut pressed!");
        executeShortcut(lightScreenShortcut, sizeof(lightScreenShortcut) / sizeof(lightScreenShortcut[0]));
      }

      if (DEBUG) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.printIRSendUsage(&Serial);
      }

      IrReceiver.resume();
  }
}

// Function to send a key via IR
void sendKey(Key key) {
  IrSender.sendSamsung(0x7, key, 1);
  delay(250);  // Small delay between key presses
}

// Function to execute a shortcut by sending a sequence of keys
void executeShortcut(int keys[], int length) {
  turnOffReceiving = true;
  delay(500);
  for (int i = 0; i < length; i++) {
    sendKey((Key)keys[i]);
  }
  turnOffReceiving = false;
}
