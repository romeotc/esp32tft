static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        const char * txt = lv_btnmatrix_get_active_btn_text(obj);

        printf("%s was pressed\n ", txt);
        Serial.println(passw);
        passw += txt;
     if(txt == "Pay")
    {
      
      if(passw == "1234Action2")
      {
        Serial.println("*************************");
        Serial.println("corect ");
        Serial.println(passw);
         Serial.println("*************************");
      }else{
         Serial.println("*************************");
         Serial.println("incorect ");
         Serial.println(passw);
          Serial.println("*************************");
      }
      passw = "";
    }
    }
   
}
void slider_event_cb(lv_obj_t * slider, lv_event_t event)
{

  printEvent("Slider", event);

  if(event == LV_EVENT_VALUE_CHANGED) {
      static char buf[4];                                 /* max 3 bytes  for number plus 1 null terminating byte */
      snprintf(buf, 4, "%u", lv_slider_get_value(slider));
      lv_label_set_text(slider_label, buf);               /*Refresh the text*/
  }
}

void printEvent(String Event, lv_event_t event)
{
  
  Serial.print(Event);
  printf(" ");

  switch(event) {
      case LV_EVENT_PRESSED:
          printf("Pressed\n");
          break;

      case LV_EVENT_SHORT_CLICKED:
          printf("Short clicked\n");
          break;

      case LV_EVENT_CLICKED:
          printf("Clicked\n");
          break;

      case LV_EVENT_LONG_PRESSED:
          printf("Long press\n");
          break;

      case LV_EVENT_LONG_PRESSED_REPEAT:
          printf("Long press repeat\n");
          break;

      case LV_EVENT_RELEASED:
          printf("Released\n");
          break;
  }
}
