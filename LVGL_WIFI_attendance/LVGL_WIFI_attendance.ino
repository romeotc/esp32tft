#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include <Arduino_JSON.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
WiFiMulti wifiMulti;

#include <lvgl.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

/************* RFID ***************/
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 26
#define RST_PIN 27

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];
char str[32] = "";
String inStringHex = "";

int screenWidth = 320;
int screenHeight = 240;
static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10];
static lv_disp_buf_t disp_buf;

String json_serv = "https://docs.google.com/forms/d/e/1FAIpQLSc_2B6rJudNn18wCVAzzmHrDLzZaIhX0ZPmYzYR7p8UegnH8Q/formResponse?usp=pp_url&entry.1101217131=";

String ssidName, password;
const char* remote_host = "www.google.com";
unsigned long timeout = 10000; // 10sec

String jsonString = "";
uint8_t money = 0;
String json_name,json_money;
/* LVGL objects */
IPAddress ip;
  long rssi;
  unsigned long lastcheck = 0;

static lv_obj_t * label;
static lv_obj_t * btn1;
static lv_obj_t * label_btn1;
static lv_obj_t * label_pay;
static lv_obj_t *  slider;
static lv_obj_t *  slider_label;
static lv_obj_t *  preload;
static lv_obj_t * ddlist;
static lv_obj_t * ta_password;
static lv_obj_t * kb;
static lv_obj_t * mbox_connect;
static lv_obj_t * tab1;
static lv_obj_t * tab2;
static lv_obj_t * my_label_ip;
static lv_obj_t * my_label_ssid;
static lv_obj_t * my_label_wifi_icon;

void guiTask( void *pvParameters );
void TaskBlink(void *pvParameters);  // This is a task.


/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint16_t c;

  tft.startWrite(); /* Start new TFT transaction */
  tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      c = color_p->full;
      tft.writeColor(c, 1);
      color_p++;
    }
  }
  tft.endWrite(); /* terminate TFT transaction */
  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch(&touchX, &touchY, 600);

    if(!touched)
    {
      return false;
    }

    if(touchX>screenWidth || touchY > screenHeight)
    {
      Serial.println("Y or y outside of expected parameters..");
      Serial.print("y:");
      Serial.print(touchX);
      Serial.print(" x:");
      Serial.print(touchY);
    }
    else
    {

      data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
      data->point.x = touchX;
      data->point.y = touchY;
    }

    return false; /*Return `false` because we are not buffering and no more data to read*/
}

void setup() {
  Serial.begin(115200);
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

 
  
  WiFi.begin("com4", "1122334455");
  //wifiMulti.addAP("com4", "1122334455");
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
  HTTPClient http;

  
 
    /*rfid setup */
  xTaskCreate(guiTask,
                  "gui",
                  4096*2,
                  NULL,
                  2,
                  NULL);

  xTaskCreatePinnedToCore(
    TaskBlink
    ,  "TaskBlink"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);

    
             
}



void loop() {
   char buf[64];
  // Serial.println("please scan");
   //
    if(millis()-lastcheck>5000)
          {
          Serial.println(String( millis()-lastcheck));
          rssi = WiFi.RSSI();
          ip = WiFi.localIP();
          lv_snprintf(buf, sizeof(buf), "%d.%d.%d.%d ( %d  )", ip[0], ip[1], ip[2], ip[3] , rssi);
          lv_label_set_text(my_label_ip,  buf ); 

          lv_snprintf(buf, sizeof(buf), "SSID: %s ", WiFi.SSID().c_str() );
          lv_label_set_text(my_label_ssid, buf); 
          lastcheck = millis();
          }
   // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  lv_label_set_text(label, "Check..." );
  lv_label_set_text(label_pay, LV_SYMBOL_REFRESH " Checking....");
  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));
    inStringHex = "";
    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      inStringHex += String(rfid.uid.uidByte[i], HEX);
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
     Serial.println();
    Serial.println(F("Hex normal"));
    Serial.print(inStringHex);
    Serial.println();
    Serial.println();
    static char buf[32];
     snprintf(buf, 32, "RFID %s  ", inStringHex);
    
     getData();
  }
  else{
    Serial.println(F("Card read previously."));
     inStringHex = "";
    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      inStringHex += String(rfid.uid.uidByte[i], HEX);
    }
      Serial.println();
    Serial.println(F("Hex normal"));
    Serial.print(inStringHex);
    Serial.println();
    getData();
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
  
         
  
  }

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
