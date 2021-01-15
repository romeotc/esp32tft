void guiTask(void *pvParameters) {
    
    lv_init();

  tft.begin(); /* TFT init */
  tft.setRotation(3);

  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };
  tft.setTouch(calData);


    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10);
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/
  
    lv_main();

  
    while (1) {
         lv_task_handler();
    }
}

static void lv_main(){
    
    //LV_THEME_MATERIAL_FLAG_LIGHT
    //LV_THEME_MATERIAL_FLAG_DARK
    
    lv_theme_t * th = lv_theme_material_init(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY, LV_THEME_MATERIAL_FLAG_LIGHT, LV_THEME_DEFAULT_FONT_SMALL , LV_THEME_DEFAULT_FONT_NORMAL, LV_THEME_DEFAULT_FONT_SUBTITLE, LV_THEME_DEFAULT_FONT_TITLE);     
    lv_theme_set_act(th);

    lv_obj_t * scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

     lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, LV_SYMBOL_HOME);
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview,LV_SYMBOL_SETTINGS);


  /* Create simple label */
  label = lv_label_create(tab1, NULL);
  lv_label_set_text(label, "Please Tag Card..");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT , 10, 10);

  label_pay = lv_label_create(tab1, NULL);
  lv_label_set_text(label_pay, "Tag a Card..");
  lv_obj_align(label_pay, NULL, LV_ALIGN_CENTER , -45, 10);


   lv_obj_t * btn1 = lv_btn_create(tab2, NULL);
   lv_obj_set_event_cb(btn1, event_handler);
   lv_obj_align(btn1, NULL, LV_ALIGN_IN_TOP_RIGHT, -30, 8);

   label_btn1 = lv_label_create(btn1, NULL);
   lv_label_set_text(label_btn1, LV_SYMBOL_REFRESH " Scan");

    ddlist = lv_dropdown_create(tab2, NULL);
    //lv_dropdown_set_show_selected(ddlist, false);
    lv_dropdown_set_text(ddlist, "WIFI");
    //lv_dropdown_set_options(ddlist, "...Searching...");
    lv_obj_align(ddlist, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 8);
    lv_obj_set_event_cb(ddlist, dd_event_handler);


    // make label ip
     my_label_ip = lv_label_create(tab2, NULL);
     lv_label_set_text(my_label_ip, "IP ADD");
     lv_obj_align(my_label_ip, NULL, LV_ALIGN_CENTER, -20, 0);

        
    /* icon wifi */
    my_label_wifi_icon = lv_label_create(tab2, NULL);
    lv_label_set_text(my_label_wifi_icon, LV_SYMBOL_WIFI );
    lv_obj_align(my_label_wifi_icon, NULL, LV_ALIGN_CENTER, -80, 0);
    /* icon wifi */

    /* label SSID */
    my_label_ssid = lv_label_create(tab2, NULL);
    lv_label_set_text(my_label_ssid, "SSID" );
    lv_obj_align(my_label_ssid, NULL, LV_ALIGN_CENTER, -80, -30);
   
   
    makeKeyboard();
    makePWMsgBox();
    scanWIFI();
  
 }
 
static void makeKeyboard(){
  kb = lv_keyboard_create(lv_scr_act(), NULL);
  lv_obj_set_size(kb,  LV_HOR_RES, LV_VER_RES / 2);
  lv_keyboard_set_cursor_manage(kb, true);
  
  lv_keyboard_set_textarea(kb, ta_password);
  lv_obj_set_event_cb(kb, keyboard_event_cb);
  lv_obj_move_background(kb);
}

static void keyboard_event_cb(lv_obj_t * kb, lv_event_t event){
  lv_keyboard_def_event_cb(kb, event);

  if(event == LV_EVENT_APPLY){
    lv_obj_move_background(kb);
    
  }else if(event == LV_EVENT_CANCEL){
    lv_obj_move_background(kb);
  }
}
 static void makePWMsgBox(){
  mbox_connect = lv_msgbox_create(lv_scr_act(), NULL);
  static const char * btns[] ={"Connect", "Cancel", ""};
  
  ta_password = lv_textarea_create(mbox_connect, NULL);
  lv_obj_set_size(ta_password, 200, 40);
  lv_textarea_set_text(ta_password, "");


  lv_msgbox_add_btns(mbox_connect, btns);
  lv_obj_set_width(mbox_connect, 200);
  lv_obj_set_event_cb(mbox_connect, mbox_event_handler);
  lv_obj_align(mbox_connect, NULL, LV_ALIGN_CENTER, 0, -90);
  lv_obj_move_background(mbox_connect);
}
static void mbox_event_handler(lv_obj_t * obj, lv_event_t event){
    if(event == LV_EVENT_VALUE_CHANGED) {
      lv_obj_move_background(kb);
      lv_obj_move_background(mbox_connect);
      
          if(strcmp(lv_msgbox_get_active_btn_text(obj), "Connect")==0){
            password = lv_textarea_get_text(ta_password);
            password.trim();
            connectWIFI();
          }
    
    }
}
void connectWIFI(void)
{
   WiFi.begin(ssidName.c_str(), password.c_str());
   long Starttime = millis();
   Serial.println(ssidName.c_str());
   Serial.println(password.c_str());
  while (WiFi.status() != WL_CONNECTED && ((millis()- Starttime) < 10000) )
  {
    delay(250);
    Serial.print(".");
    Serial.print(String(millis()- Starttime));
  }

   if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Please check your wifi password and try again.");
    delay(2500);
    
  }
  if(WiFi.status() == WL_CONNECTED) {
     Serial.println("Connected");
     saveWifi();
  }
  
}
  void scanWIFI(void)
  {
       Serial.println("scan start");
       int n = WiFi.scanNetworks();
        if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        lv_dropdown_clear_options(ddlist);  
        String network = String(n) + "Found";
       
        delay(10);
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
             String item = WiFi.SSID(i) + " (" + WiFi.RSSI(i) +") " + ((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
             lv_dropdown_add_option(ddlist,item.c_str(),LV_DROPDOWN_POS_LAST);
            
             delay(10);
           
        }
    }
  }

void saveWifi()
{
   Serial.println("Save WIFI");
}
