
HTTPClient http;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
        printf("Clicked\n");
        
        
      scanWIFI();
        
        printf("end Clicked\n");
        
    }
    else if(event == LV_EVENT_VALUE_CHANGED) {
        printf("Toggled\n");
    }
}

static void dd_event_handler(lv_obj_t * obj, lv_event_t event){
  printf("list\n");
  if(event == LV_EVENT_VALUE_CHANGED) {
    
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        ssidName = String(buf);
        
        for (int i = 0; i < ssidName.length()-1; i++) {
          if (ssidName.substring(i, i+2) == " (") {
              ssidName = ssidName.substring(0, i);
            break;
          }
        }
        delay(1000);
       
        popupPWMsgBox();
    }
}

static void popupPWMsgBox(){
  if(ssidName == NULL || ssidName.length() == 0){
    return;
  }

    lv_textarea_set_text(ta_password, ""); 
    lv_msgbox_set_text(mbox_connect, ssidName.c_str());
    lv_obj_move_foreground(mbox_connect);
    
    lv_obj_move_foreground(kb);
    lv_keyboard_set_textarea(kb, ta_password);
}
JSONVar myObject;
void getData()
{
  
   if((WiFi.status() == WL_CONNECTED)) {

        lv_label_set_text(label, "Connecting.." );

        Serial.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
        String serv = json_serv + inStringHex;
        http.begin(serv); //HTTP

        Serial.println("[HTTP] GET...\n");
        Serial.print(serv);
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
               


                
               
                  
           
                   static char buf[32];
                    snprintf(buf, 32, "Success..." );

                  /**********************************************/
                 lv_label_set_text(label, buf );
                 lv_label_set_text(label_pay , LV_SYMBOL_OK " Success Attendance.");

                 
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
             lv_label_set_text(label, "[HTTP] GET... failed" );
             lv_label_set_text(label_pay, LV_SYMBOL_CLOSE " Error try Again!!!..");
        }

        http.end();
    }else{
      lv_label_set_text(label, "Not Connect..try" );
      lv_label_set_text(label_pay, LV_SYMBOL_CLOSE " Check Internet...");
       Serial.print("Not Connect..\n");
    }
}
