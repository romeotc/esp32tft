# esp32tft

esp32tft เป็นบอร์ดสำหรับการเรียนรู้การเขียนโปรแกรมเพื่อควบคุม Board esp32 กับจอ tft9341 ทัชสกรีน โดยมีโมดูล RC522 สำหรับติดต่อ RFID 
<hr>
<table >
  <tr>
    <td>
      <img src="https://scontent.fhdy1-1.fna.fbcdn.net/v/t1.15752-9/135781673_1125694967864478_3048273404046962822_n.jpg?_nc_cat=107&ccb=2&_nc_sid=ae9488&_nc_eui2=AeHVtP2OpruCRBSYUCNs4d2NQhgNd-ypoDVCGA137KmgNU0zKa30bDeBnytddL7dHf0wStpJDTeqWO2usT7cx35W&_nc_ohc=u_ttwJgC_XkAX-r3FEj&_nc_ht=scontent.fhdy1-1.fna&oh=ef4ab3b31bbc807cb8d06401aae874df&oe=601FDE66" width="350">
    </td>
    <td>
      <img src="https://scontent.fhdy1-1.fna.fbcdn.net/v/t1.15752-9/137051682_192388372615063_4757542291784061185_n.jpg?_nc_cat=109&ccb=2&_nc_sid=ae9488&_nc_eui2=AeH02L_wBQ0B8VJMQgIqIcT-eL1-cp54eip4vX5ynnh6Ku5ow2Jg3tp9E2eWmXgWyEwmSHifMZi7mmKbdwddx0ia&_nc_ohc=DuoYi0mfAoIAX_XEQDG&_nc_ht=scontent.fhdy1-1.fna&oh=14c7e678eab454a650705b31341ed423&oe=602020AB" width="350">
    </td>
  </tr>
  </table>

การเชื่อมต่อบนบอร์ด
1. TFT 9431 2.8" มีขาเชื่อมต่อดังนี้   
  <library>
  lv_arduino
  #include <lvgl.h>
  #include <TFT_eSPI.h>
 ----------------------------
  <connection>
  #define TFT_CS   15  // Chip select control pin
  #define TFT_DC    0  // Data Command control pin
  #define TFT_RST   2  // Reset pin (could connect to RST pin)
  #define TOUCH_CS 5     // Chip select pin (T_CS) of touch screen
  ---------------------------
2. RFID rc522 ขาเชื่อมต่อดังนี้  
  <library>
  #include <SPI.h>
  #include <MFRC522.h>
  ---------------------------
  <connection>
  #define SS_PIN 26
  #define RST_PIN 27
  ---------------------------
