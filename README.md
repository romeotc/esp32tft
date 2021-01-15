# esp32tft

esp32tft เป็นบอร์ดสำหรับการเรียนรู้การเขียนโปรแกรมเพื่อควบคุม Board esp32 กับจอ tft9341 ทัชสกรีน โดยมีโมดูล RC522 สำหรับติดต่อ RFID 
<hr>
<table>
  <tr>
    <td>
      บทที่
    </td>
    <td>
      เรื่อง
    </td>
    <td>
     แหล่งข้อมูล
    </td>
      
  </tr>
  <tr>
    <td>
      1
    </td>
     <td>
      LVGL DEMO
    </td>
    <td>
      < a href="https://www.youtube.com/watch?v=7v4SGbpQaqw">Video</a>/
      <a href="https://github.com/romeotc/esp32tft/tree/main/01.ESP32_TFT_eSPI_Slider">Source</a>
    </td>
  </tr>
  
</table>
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

<p>การเชื่อมต่อบนบอร์ด</p>
<ol>
<li>TFT 9431 2.8" มีขาเชื่อมต่อดังนี้</li>
</ol>
<p>&nbsp; &lt;library&gt;</p>
<p>&nbsp; lv_arduino</p>
<p>&nbsp; #include &lt;lvgl.h&gt;</p>
<p>&nbsp; #include &lt;TFT_eSPI.h&gt;</p>
<p>&nbsp;----------------------------</p>
<p>&nbsp; &lt;connection&gt;</p>
<p>&nbsp; #define TFT_CS&nbsp;&nbsp; 15&nbsp; // Chip select control pin</p>
<p>&nbsp; #define TFT_DC&nbsp;&nbsp;&nbsp; 0&nbsp; // Data Command control pin</p>
<p>&nbsp; #define TFT_RST&nbsp;&nbsp; 2&nbsp; // Reset pin (could connect to RST pin)</p>
<p>&nbsp; #define TOUCH_CS 5&nbsp;&nbsp;&nbsp;&nbsp; // Chip select pin (T_CS) of touch screen</p>
<p>&nbsp; ---------------------------</p>
<ol start="2">
<li>RFID rc522 ขาเชื่อมต่อดังนี้</li>
</ol>
<p>&nbsp; &lt;library&gt;</p>
<p>&nbsp; #include &lt;SPI.h&gt;</p>
<p>&nbsp; #include &lt;MFRC522.h&gt;</p>
<p>&nbsp; ---------------------------</p>
<p>&nbsp; &lt;connection&gt;</p>
<p>&nbsp; #define SS_PIN 26</p>
<p>&nbsp; #define RST_PIN 27</p>
