#include "main.h"

void isr_button_pressed(void *args)
{
  buttonIsPressed = gpio_get_level(BUTTON_GPIO);
}

void task_button(void *pvParameter)
{
  //Configure button
  gpio_config_t btn_config;
  btn_config.intr_type = GPIO_INTR_ANYEDGE;    //Enable interrupt on both rising and falling edges
  btn_config.mode = GPIO_MODE_INPUT;           //Set as Input
  btn_config.pin_bit_mask = (1 << BUTTON_GPIO); //Bitmask
  btn_config.pull_up_en = GPIO_PULLUP_DISABLE;    //Disable pullup
  btn_config.pull_down_en = GPIO_PULLDOWN_ENABLE; //Enable pulldown
  gpio_config(&btn_config);
  printf("Button configured\n");

  //Configure interrupt and add handler
  gpio_install_isr_service(0);                  //Start Interrupt Service Routine service
  gpio_isr_handler_add(BUTTON_GPIO, isr_button_pressed, NULL); //Add handler of interrupt
  printf("Interrupt configured\n");
  
  //Wait
  while (1)
  {
	  	// button pressed
	  	if(buttonIsPressed == 1){
			buttonIsPressedCounter++;
			// ~3 seconds pressed...
			if( buttonIsPressedCounter >= 30){
	  			printf("Alarm triggered, counter: %d\n",buttonIsPressedCounter);
				// sound not enabled
				if(!soundhandler->getState()){
				    // enable sound
				    soundhandler->enable();
				}
		  	}	
	  	} else{
			buttonIsPressedCounter = 0;
			// sound enabled
			if(soundhandler->getState()){
			    // mute sound
			    soundhandler->mute();
			}
	 	}
		// 100ms
		vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

extern "C" void app_main()
{
  xTaskCreate(&task_button, "button", 2048, NULL, 5, NULL);
}