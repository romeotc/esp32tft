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
    lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "Tab 2");
    lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "Tab 3");

  /* Create simple label */
  label = lv_label_create(tab1, NULL);
  lv_label_set_text(label, "Please Tag Card..");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT , 10, 10);

  label_pay = lv_label_create(tab1, NULL);
  lv_label_set_text(label_pay, "Pay 0 B");
  lv_obj_align(label_pay, NULL, LV_ALIGN_IN_TOP_RIGHT , -25, 10);



  /* Create a label below the slider */
  slider_label = lv_label_create(tab2, NULL);
  lv_label_set_text(slider_label, "Please Tag Card..");
  
  lv_obj_align(slider_label, NULL, LV_ALIGN_CENTER, -5, -5);

  static const char * btnm_map[] = { "25", "30", "35", "\n",
                                 
                                  "Pay", ""};

    lv_obj_t * btnm1 = lv_btnmatrix_create(tab1, NULL);
    lv_btnmatrix_set_map(btnm1, btnm_map);
   // lv_btnmatrix_set_btn_width(btnm1, 0, 1);        /*Make "Action1" twice as wide as "Action2"*/
   // lv_btnmatrix_set_btn_width(btnm1, 1, 1);        /*Make "Action1" twice as wide as "Action2"*/
   // lv_btnmatrix_set_btn_width(btnm1, 2, 1);        /*Make "Action1" twice as wide as "Action2"*/
  //  lv_btnmatrix_set_btn_width(btnm1, 3, 1);        /*Make "Action1" twice as wide as "Action2"*/
    
    lv_btnmatrix_set_btn_ctrl(btnm1, 3, LV_BTNMATRIX_CTRL_CHECK_STATE);
    lv_obj_align(btnm1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -10);
    lv_obj_set_event_cb(btnm1, event_handler);

    
  
 }
