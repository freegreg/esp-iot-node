#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"

// variable modified indirectly by interrupt handler
volatile int whatyouwant;

// gpio interrupt handler. See below
LOCAL void  gpio_intr_handler(int * dummy);


static const int Buttonpin = 0;
static const int Ledpin = 13;
static volatile os_timer_t some_timer;

void some_timerfunc(void *arg)
{
os_printf("Blinky...\n");
   	 uint32 gpio_Buttonpin = GPIO_REG_READ(GPIO_IN_ADDRESS) & (1 << Buttonpin);
	uint32 gpio_Ledpin = GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << Ledpin);
	os_printf("GPIO_BUTTON = %d\n", gpio_Buttonpin);
	os_printf("GPIO_LED = %d\n", gpio_Ledpin);

  //Do blinky stuff
  if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << Ledpin))
  {
    // set gpio low
    gpio_output_set(0, (1 << Ledpin), 0, 0);
  }
  else
  {
    // set gpio high
    gpio_output_set((1 << Ledpin), 0, 0, 0);
  }
}

void ICACHE_FLASH_ATTR user_init()
{
// Initialize the GPIO subsystem.
   gpio_init();

// =================================================
// Initialize GPIO13 and GPIO0 as GPIO
// =================================================
//
//
// PIN_FUNC_SELECT() defined in eagle_soc.h
// PERIPHS_IO_MUX_... for each pin defined in eagle_soc.h
// FUNC_... for each PERIPHS macros defined in eagle_soc.h
//
// From eagle_soc.h:
// GPIO0 only can be GPIO
// GPIO13 can be GPIO, ..
//

  // configure UART TXD to be GPIO1, set as output
  PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); 

    // set gpio low
 gpio_output_set(0, 0, (1 << Ledpin), (1 << Buttonpin));

// =================================================
// Activate gpio interrupt for gpio0
// =================================================

    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0);                //GPIO Alternate Function 
    GPIO_DIS_OUTPUT(GPIO_ID_PIN(0));                                  //Configure it in input mode.
    ETS_GPIO_INTR_DISABLE();                                           //Close the GPIO interrupt
    ETS_GPIO_INTR_ATTACH(gpio_intr_handler,NULL);                         //Register the interrupt function
    gpio_pin_intr_state_set(GPIO_ID_PIN(0),GPIO_PIN_INTR_ANYEDGE);    //Falling edge trigger
    ETS_GPIO_INTR_ENABLE() ;                                           //Enable the GPIO interrupt


  // setup timer (500ms, repeating)
  os_timer_setfn(&some_timer, (os_timer_func_t *)some_timerfunc, NULL);
  os_timer_arm(&some_timer, 2000, 1);
}

//-------------------------------------------------------------------------------------------------
// interrupt handler
// this function will be executed on any edge of GPIO0
LOCAL void  gpio_intr_handler(int * dummy)
{
// clear gpio status. Say ESP8266EX SDK Programming Guide in  5.1.6. GPIO interrupt handler
	os_printf("Interrupt...\n");
    uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

// if the interrupt was by GPIO0
    if (gpio_status & BIT(0))
    {
// disable interrupt for GPIO0
        gpio_pin_intr_state_set((1 << Buttonpin), GPIO_PIN_INTR_DISABLE);

// Do something, for example, increment whatyouwant indirectly
  //Do blinky stuff
  if (GPIO_REG_READ(GPIO_OUT_ADDRESS) & (1 << Ledpin))
  {
    // set gpio low
    gpio_output_set(0, (1 << Ledpin), 0, 0);
  }
  else
  {
    // set gpio high
    gpio_output_set((1 << Ledpin), 0, 0, 0);
  }

//clear interrupt status for GPIO0
        GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(0));

// Reactivate interrupts for GPIO0
        gpio_pin_intr_state_set((1 << Buttonpin), GPIO_PIN_INTR_ANYEDGE);
    }
}

