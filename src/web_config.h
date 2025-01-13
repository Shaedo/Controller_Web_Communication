  #define CONFIG_CONTROLLER_ID 1

//Period (milli seconds) timer waits for unresponsive peripherals
  #define DEFAULT_TIMER_PERIOD 3
  #define DEFAULT_CYCLE_DURATION 10000
  #define MIN_CYCLE_DURATION 1000
/*************************************/

// min value for global var currentCycle. 
  // values < MIN_CURRENT_CYCLE are reserved for communications outside of usual cycle 
  # define MIN_CURRENT_CYCLE 5 

/*** WIFI ***/


//#define CONFIG_SSID "PFSB-12-2.4GHz"

//#define CONFIG_SSID "Embernet24"
//#define CONFIG_PASS "mandQLaQHJYj1ePBe07ywTFKJ9J3THx60X2FJccK5UopMK62"

//#define CONFIG_SSID "WiFi-987A"
//#define CONFIG_PASS "57318622"

//  #define CONFIG_SSID "AndroidAP0535"
//  #define CONFIG_PASS "ARMJNR8DLC"

/**Note ESP32/Arduino/etc only use 2.4ghz (which is longer range, more stable, and maximises their bandwidth)*/
  #define CONFIG_SSID "NotWorking2"
  #define CONFIG_PASS "ARMJNR8DLC"

// API Server to take requests from EmberAngel
  #define CONFIG_SERVER_PORT 80
  #define CONFIG_CONTROLLER_VERIFICATION "asdfqwer" 
  #define VERIFICATION_LENGTH 8

//  Web Server to send reports to
  #define CONFIG_WEB_SERVER_UNIT "https://emberangel.com/test/report.php"
  #define CONFIG_WEB_SERVER_PORT 443
  #define CONFIG_REPORTING_ID "JymxTPGeGW"


