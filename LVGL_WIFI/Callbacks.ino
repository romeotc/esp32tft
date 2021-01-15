
HTTPClient http;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        
        
        
       
        if(txt == "Pay")
        {
          
          Serial.println("GET...");
          
          delay(1000);
          putData(money);
        }else{
          money = atoi(txt);
           static char buf[32];                                 /* max 3 bytes  for number plus 1 null terminating byte */
            snprintf(buf, 32, "Pay %s B", txt);
           lv_label_set_text(label_pay, buf);
        }
    
    }
    
   
}

void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{

  //printEvent("Slider", event);

  if(event == LV_EVENT_VALUE_CHANGED) {
      static char buf[4];                                 /* max 3 bytes  for number plus 1 null terminating byte */
      snprintf(buf, 4, "%u", lv_slider_get_value(slider));
      lv_label_set_text(slider_label, buf);               /*Refresh the text*/
  }
}
JSONVar myObject;
void getData()
{
  
   if((wifiMulti.run() == WL_CONNECTED)) {

        lv_label_set_text(label, "Connecting.." );

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        String serv = json_serv + inStringHex;
        http.begin(serv); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
                /*****************************************/
                JSONVar myArray = JSON.parse(payload);
               


                
                  jsonString = JSON.stringify(myArray[0]);
                  JSONVar myObject = JSON.parse(jsonString);

                  Serial.print("JSON.stringify(myObject) = ");
                  Serial.println(jsonString);
                
                  Serial.println();

                  Serial.print("myObject.length() = ");
                  Serial.println(myObject.length());
                  Serial.println();

                   Serial.print("myObject = ");
                    Serial.println(myObject);
                    Serial.println();
                  
              if (myObject.hasOwnProperty("name")) {
                  Serial.print("myObject[\"mane\"] = ");
                    json_name = JSON.stringify(myObject["name"]);
                  Serial.println( myObject["name"]);
                }
                if (myObject.hasOwnProperty("money")) {
                  Serial.print("myObject[\"money\"] = ");
                    json_money = JSON.stringify(myObject["money"]);
                  Serial.println( myObject["money"]);
                }
                   static char buf[32];
                    snprintf(buf, 32, "Name %s = %s ฿", json_name , json_money  );

                  /**********************************************/
                 lv_label_set_text(label, buf );

                 
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }else{
      lv_label_set_text(label, "Not Connect..try" );
       Serial.print("Not Connect..\n");
    }
}

void putData(uint8_t money)
{
  
   if((wifiMulti.run() == WL_CONNECTED)) {

        lv_label_set_text(label, "Connecting.." );
       
        Serial.print("jsonString = ");
         Serial.println(jsonString);
         

          Serial.print("money = ");
         Serial.println(money);
        

         JSONVar myObject = JSON.parse(jsonString);
         Serial.print("name = ");
           json_name = JSON.stringify(myObject["name"]);
           Serial.println( myObject["name"]);

            String old = JSON.stringify(myObject["money"]);
            int old_money = old.toInt();

            int balance = old_money - money;
            
           Serial.print("balance = ");
           Serial.println(balance);
           
          static char buf[32];
         

          String data = "money=" + String(balance);

          String jsonString_2 = JSON.stringify(myObject);

           Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        String serv = json_serv + inStringHex;
        http.begin(serv); //HTTP
         http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        
         

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        
        int httpCode = http.PATCH(data);
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
               if(httpCode == HTTP_CODE_OK) {
                      String payload = http.getString();
                      Serial.println(payload);
                       inStringHex = "";
                      json_money = balance;
                      money = 0 ;
               }
         }else{
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
         }
                          
                         snprintf(buf, 32, "Name %s = %s ฿", json_name , json_money  );
                          lv_label_set_text(label, buf );
                                                   /* max 3 bytes  for number plus 1 null terminating byte */
                         snprintf(buf, 32, "Tag Card..");
                        lv_label_set_text(label_pay, buf);

   }
}
