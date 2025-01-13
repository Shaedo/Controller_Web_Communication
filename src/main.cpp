/******* SUMMARY *****
  *PIN-OUT*
    https://resource.heltec.cn/download/Wireless_Stick_Lite_V3/HTIT-WSL_V3.png
 */
/******* INCLUDES ***********/
  #include <Arduino.h>
  #include "web_config.h"

  #include <WiFi.h>
  #include <HTTPClient.h>

/******* GLOBAL VARS ***********/
  #define REPORTING_MODE 2 //0 = prod mode, 1 = include comments, 2 = dev (wipes EEPROM records)

  #define SERIAL_BAUD_RATE 115200

/******* FUNCTION PROTOTYPES ***********/
  void setup();
  void initWiFi();

  void loop();
  void listenWiFi();
  boolean validateID(char validateIncoming[VERIFICATION_LENGTH]);
  void sendExternalReport();

/******* WIFI ***********/
  WiFiServer server(CONFIG_SERVER_PORT);
  /* see web_config.h for:
    CONFIG_SSID
CONFIG_PASS

  */

/******* INIT - SETUP ***********/
  void setup(){
    #if REPORTING_MODE > 0
        Serial.begin(SERIAL_BAUD_RATE);
    #endif 

    initWiFi();

    #if REPORTING_MODE > 0
      Serial.println("Setup Complete.");
    #endif 

sendExternalReport();

  }

  void initWiFi(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(CONFIG_SSID, CONFIG_PASS);
    
    while (WiFi.status() != WL_CONNECTED) {
    #if REPORTING_MODE > 0
      Serial.print('.');
    #endif  
      delay(200);
    }
      server.begin();
    #if REPORTING_MODE > 0
      Serial.print("WiFi: ");
      Serial.println(WiFi.localIP());
    #endif  
  }

/******* LOOP ***********/
    void loop() {
      listenWiFi();
    }

    void listenWiFi() {
      // listen for incoming clients
      WiFiClient client = server.available();
      if (client) {
        //Verify IP address here??
        boolean currentLineIsBlank = true;

        char validateIncoming[VERIFICATION_LENGTH];
        //Serial.println("incoming WiFi....");
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
            if (c == '\n' && currentLineIsBlank) {
              byte dataPos = 0;
              while (client.available()) {
                char d = client.read();
                validateIncoming[dataPos] = d;
                dataPos++;
              }
              #if REPORTING_MODE > 0
                Serial.println("WiFi Request Recieved:" + String(validateIncoming));
              #endif
              /*Validate incoming data*/
              if (!validateID(validateIncoming)) {
                client.stop();
                return;
              } else {
                // send a standard HTTP response header
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println("Access-Control-Allow-Origin: emberangel.com");
                client.println("Connection: close");  // the connection will be closed after completion of the response
                client.println();
                byte randNumber = random(10, 99);
                client.print("Controller success ");
                client.println(randNumber);
              }
              break;  //!!!! DONT REMOVE ME (again!)
            }
            if (c == '\n') {  // you're starting a new line
              currentLineIsBlank = true;
            } else if (c != '\r') {  // you've gotten a character on the current line
              currentLineIsBlank = false;
            }
          }
        }
        delay(100);
        client.stop();
      }
    }

    boolean validateID(char validateIncoming[VERIFICATION_LENGTH]) {
      for (uint8_t i=0; i<VERIFICATION_LENGTH; i++) {
        if (validateIncoming[i] != CONFIG_CONTROLLER_VERIFICATION[i]) {
          return false;
        }
      }
      return true;
    }

    void sendExternalReport(){
      if(WiFi.status() == WL_CONNECTED){
        String report = "r=test-report";
        HTTPClient http;
        http.begin(CONFIG_WEB_SERVER_UNIT);  // Define the server URL
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        
        // Sending the POST request
        int httpResponseCode = http.POST(report);

        // Check the response code
        if (httpResponseCode > 0) {
          // Server responded with a code, print the code
          String serverResponse = http.getString();  // Get the response body as a string
          #if REPORTING_MODE > 0
            Serial.println("HTTP response code: " + String(httpResponseCode));
            Serial.println("Server response: " + serverResponse);  // Output the response body
          #endif
        } else {
          // If the request failed, print an error message
          #if REPORTING_MODE > 0
            Serial.println("Error sending POST request. HTTP code: " + String(httpResponseCode));
          #endif
        }

        http.end();  // Close the HTTP connection
      }
    }

/*END*/

