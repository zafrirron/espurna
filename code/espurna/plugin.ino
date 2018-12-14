
#ifdef _PLUGIN_H
/*

Plugin Module description
Plugin Copyright

*/
//* This is espurna plugin template file integrated thru existing espurna integration
//* model of including custom.h header by USE_CUSTOM_H flag
//* running 3rd party code by USE_EXTRA flag
//* the file include commnted code lines for calling espurna's services
//* The bare template includes:
//* 1. A loop counter in the lpugin main Loop
//*     controled by PLUGIN_REPORT_EVERY parmeters in plugin header (0-disbles counter)
//*     the counter is printed on debug windows (web, telnet, serial)
//* 2. API registration /plugin were value=0 stops exceiotion and value=1 starts
//*    (see the counter start stops on debug)
//* 3. COMMAND registration on espurna commander from web/telnet/serial command "plugin"
//*    shows status, "plugin 0" stops execution and "plugin 1" starts.
//* 4. Setting of plugin state is saved thru reboots
//*

//*
//*for better readability and usage of this template file the writing style is:
//* (//*) for comments
//* (//) for commented code (just delete the // to activate)
//*
//* This plugin templat does not include web interface provisioning of the frontend
//* HTML, JS, CSS needs to be coded into the original core (on current espurna design)

//*---------------------------------------------------------------------------
//* Plugin includes
//*---------------------------------------------------------------------------
#include <EEPROM.h>
#include <Ticker.h>
#include <ArduinoJson.h>
#include <vector>
#include <functional>
#include <ESPAsyncTCP.h>
#include <SyncClient.h>
//#include <otherPluginIncludeFiles>

//*----------------------------------------------------------------------------
//* Private
//*----------------------------------------------------------------------------
//*----------------------------------------------------------------------------
//* Plugin globals
//*----------------------------------------------------------------------------
bool _plugin_enabled = false;;
unsigned long _pluginReportInterval = 1000 * PLUGIN_REPORT_EVERY;
unsigned long _pluginLastUpdate = 0;
unsigned long _pluginCounter = PLUGIN_PARAMETER_1;
const char GET_REQUEST_TEMPLATE[] PROGMEM =
    "GET %s HTTP/1.1\r\n"
    "Host: %s\r\n\r\n";
    //"User-Agent: ESPurna\r\n"
    //"Connection: close\r\n"
    //"Content-Type: application/x-www-form-urlencoded\r\n"
    //"Content-Length: 0\r\n\r\n\r\n";
const char POST_REQUEST_TEMPLATE[] PROGMEM =
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        //"User-Agent: ESPurna\r\n"
        "Connection: close\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: %d\r\n\r\n"
        "%s\r\n";
const String LoggerHost = "10.0.0.155";  //Logger Server IP
const uint16_t LoggerPort = 8000;  //Logger service port
const String LogUri = "/Door-Bell/log";  //Simple logger service definition
const String SonosHost = "10.0.0.155";  //Sonos Server IP
const uint16_t SonosPort = 5005;  //Sonos service port
const String SonosClip = "/kitchen/clip/church-3.mp3"; //Sonos Clip

//*----------------------------------------------------------------------------
//* Plugin helper functions
//*----------------------------------------------------------------------------
void HttpRequest(char *ServerHost ,uint16_t ServerPort,char *ReqUri,char *PostData) {
    SyncClient client;
    bool httpget = (PostData == "");
    if(!client.connect(ServerHost, ServerPort)){
        DEBUG_MSG_P(PSTR("[PLUGIN] HTTP connect failed %s:%u\n"),ServerHost,ServerPort);
        return;
    }
    DEBUG_MSG_P(PSTR("[PLUGIN] HTTP connected %s:%u\n"),ServerHost,ServerPort);
    client.setTimeout(3);
    if (httpget) {
        char buffer[strlen_P(GET_REQUEST_TEMPLATE) + strlen(ReqUri) + strlen(ServerHost)];
        snprintf_P(buffer, sizeof(buffer),
            GET_REQUEST_TEMPLATE,
            ReqUri,
            ServerHost
        );
        //if(client.printf("GET %s HTTP/1.1\r\nHost: %s\r\n\r\n",ReqUri,ServerHost) == 0){
        if(client.printf(buffer) == 0){
                DEBUG_MSG_P(PSTR("[PLUGIN] HTTP GET reuest failed %s\n"),ReqUri);
        } else {
                DEBUG_MSG_P(PSTR("[PLUGIN] HTTP GET Ok %s\n"),ReqUri);
        }
    } else {
        char buffer[strlen_P(POST_REQUEST_TEMPLATE) + strlen(ReqUri) + strlen(ServerHost) + strlen(PostData)];
        snprintf_P(buffer, sizeof(buffer),
            POST_REQUEST_TEMPLATE,
            ReqUri,
            ServerHost,
            strlen(PostData),
            PostData
        );
        if(client.printf(buffer) == 0){
              DEBUG_MSG_P(PSTR("[PLUGIN] HTTP POST reuest failed %s\n"),ReqUri);
        } else {
              DEBUG_MSG_P(PSTR("[PLUGIN] HTTP Post Ok %s:%s\n"),ReqUri,PostData);
        }
    }
    client.stop();
}
void logit(String message) {
    String logStr = ntpDateTime() +" - " + message + "\r\n";
    HttpRequest(strdup(LoggerHost.c_str()),LoggerPort, strdup(LogUri.c_str()),strdup(logStr.c_str()));
}
//* Plugin loop helper function(s)
//*------------------------------
void _pluginFunction1() {
    //* This is were the plugin magic happens...
    //* plugin functions called from _pluginLoop()
    //* _pluginLoop() is regitered to
    //* plugin loop helper function code goes here

    //* to get a sensor value for the plugin
    //*-------------------------------------
//    #if SENSOR_SUPPORTED
//        unsigned char _sensorID;
//        double _sensorValue;
//        _sensorValue = _getSensorValue(_sensorID, "current");
//        _sensorValue = _getSensorValue(_sensorID, "filtered");
//        _sensorValue = _getSensorValue(_sensorID, "reported");
//    #endif

    //* changing relay based on plugin logic
    //*-------------------------------------
//    unsigned char _relayID;
    //* set to true, false ot toggle status
//    _setRaleyStatus(_relayID, "ON");
//    _setRaleyStatus(_relayID, "OFF");
//    _setRaleyStatus(_relayID, "TOGGLE");

    //* In case of factory reset need
    //*------------------------------
//    resetSettings();
//    deferredReset(100, CUSTOM_RESET_FACTORY);

    //* In case of AP  need
    //*--------------------
//     createAP();

    //* In case of system reset need
    //*-----------------------------
//     deferredReset(100, CUSTOM_RESET_HARDWARE);

    //* In case of params setter/getter need
    //*-------------------------------------
//    setSetting(key, value);
//    getSetting(key, value, defaultValue);

    //* Broker publish
    //*-------------
//    #if BROKER_SUPPORT
//        brokerPublish(MQTT_TOPIC_PLUGIN, [id], message);
//    #endif

    //* MQTT publish
    //*-------------
//    #if MQTT_SUPPORT
//        mqttSend(MQTT_TOPIC_PLUGIN, [id], message);
//    #endif

    //* DOMOTICZ publish
    //*-----------------
//    #if DOMOTICZ_SUPPORT
//        domoticzSend(DOMOTICZ_TOPIC_PLUGIN, payload);
//    #endif

    //* INFLUXDB publish
    //*-----------------
//    #if INFLUXDB_SUPPORT
//        idbSend(INFLUXDB_TOPIC_PLUGIN,payload);
//    #endif

    //* THINGSPEAK publish
    //*-----------------
//    #if THINGSPEAK_SUPPORT
//        _tspkEnqueue(field_id, field_payload);
//        tspkFlush();
//    #endif

    //* Debug messages (anywere in your code)
    //*--------------------------------------
    #if PLUGIN_REPORT_EVERY != 0
      //DEBUG_MSG_P(PSTR("[PLUGIN] Plugin debug message c format: {%.}\n"), {.});
        if (millis() - _pluginLastUpdate > _pluginReportInterval) {
            _pluginLastUpdate = millis();
            DEBUG_MSG_P(PSTR("[PLUGIN] Counter (%d s' tick): %d\n"),PLUGIN_REPORT_EVERY,_pluginCounter);
            _pluginCounter++;
        }
    #endif

    if (_bell_pressed) {
        DEBUG_MSG_P(PSTR("[PLUGIN] Button-1 pressed\n"));
        //HttpRequest(strdup(SonosHost.c_str()),SonosPort,strdup(SonosClip.c_str()),"");
        logit("Door Bell");
        _bell_pressed = false;
    }
    if (_gate_open) {
        DEBUG_MSG_P(PSTR("[PLUGIN] Gate Open requested\n"));
        logit("Gate Open");
        _gate_open = false;
    }
}
//* If frontend support needed
//* Websocket support helper functions
//*-----------------------------------
//#if WEB_SUPPORT
     //* parse ws values
//      unsigned char pluginParsePayload(const char * payload) {
//          char * p = ltrim((char *)payload);
//            if (strcmp(p, "query") == 0) {
//                return 0;
//           }
//      }
//      void _pluginWebSocketUpdate(JsonObject& root) {
//          JsonArray& plugin = root.createNestedArray("pluginStatus");
//          plugin.add("OK");
//      }
//      void _pluginWebSocketOnAction(uint32_t client_id, const char * action, JsonObject& data) {
		      //* on action register event action code here
//          if (strcmp(action, "plugin") != 0) return;
//          if (data.containsKey("status")) {
//              unsigned char value = pluginParsePayload(data["status"]);
//              if (value == 0) {
//                  wsSend(_pluginWebSocketUpdate);
//              }
//	        }
//      }
//      bool _pluginWebSocketOnReceive(const char * key, JsonVariant& value) {
	        //* on recieve event code here
//          return (strncmp(key, "plugin", 6) == 0);
//	    }
//        void _pluginWebSocketOnParse(JsonObject& root) {
	      //* socket parse event code here
//	    }
//      void _pluginWebSocketOnStart(JsonObject& root) {
	      //* socket start event code here
//        _relayWebSocketUpdate(root);

        //* Configuration params
//        JsonArray& config = root.createNestedArray("pluginConfig");
//        JsonObject& line = config.createNestedObject();
//        line["pluginParam1"] = "Param1";
//        line["pluginParam2"] = "Param2";
//        root["pluginRoot"]   = "pluginRoot";
//	    }
      //* set websocket handlers
//      void _pluginSetupWS() {
//          wsOnSendRegister(_pluginWebSocketOnStart);
//          wsOnReceiveRegister(_pluginWebSocketOnReceive);
//          wsOnActionRegister(_pluginWebSocketOnAction);
//          wsOnAfterParseRegister(_pluginWebSocketOnParse);
//	    }
//#endif

//* helper function to get sensor value
//*------------------------------------
//#if SENSOR_SUPPORT
//    double _getSensorValue(unsigned char id, const char * type ) {
//        char * p = ltrim((char *)type);
//        if (strcmp(p, "current") != 0) return _magnitudes[id].current;
//        else if (strcmp(p, "filtered") != 0) return _magnitudes[id].filtered;
//        else if (strcmp(p, "reported") != 0) return _magnitudes[id].reported;
//        return 0;
//    }
//#endif

//* helper function to set relay
//*-----------------------------
//void _setRaleyStatus(unsigned char id, const char * action ) {
//    char * p = ltrim((char *)action);
//    if (strcmp(p, "ON") != 0) {
//        relayStatus(id - 1, true);
//        return;
//    }
//    else if (strcmp(p, "OFF") != 0) {
//        relayStatus(id - 1, true);
//        return;
//    }
//    else if (strcmp(p, "TOGGLE") != 0) {
//        relayToggle(id - 1);
//        return;
//    }
//}

//* If API support needed
//* API register helper function
//*-----------------------------
#if API_SUPPORT
    //* register api functions
    //* apiRegister(key, _getFunction, _putFunction);
    //* this is API registraion to enable disable the plugin
    //* use this as template to create additional API calls for the plugin
    void _pluginSetupAPI() {
          char key[15];
          snprintf_P(key, sizeof(key), PSTR("%s"), API_PLUGIN_ENDPOINT);
          apiRegister(key, 
            [](char * buffer, size_t len) 
            {
               DEBUG_MSG_P(PSTR("[PLUGIN] received GET request at /%s \n"), API_PLUGIN_ENDPOINT);
               snprintf_P(buffer, len, PSTR("OK"));
            },
            [](const char * payload) { 
               int i = atoi(payload);
               DEBUG_MSG_P(PSTR("[PLUGIN] received GET request at /%s: (%s) \n"), API_PLUGIN_ENDPOINT,payload);
               
               if (i != 0 && i != 1) {
                   DEBUG_MSG_P(PSTR("[PLUGIN] Wrong payload (%s)\n"),i);
                   return;
               }
               _plugin_enabled = (i == 1);
               setSetting("PLG_EN", _plugin_enabled);
               DEBUG_MSG_P(PSTR("[PLUGIN] Set Plugin state: (%s)\n"), _plugin_enabled ? "ON" : "OFF");
            }
            //[](const char * payload) {
            //    DEBUG_MSG_P(PSTR("[PLUGIN] Wrong payload (%s)\n"), payload);
            //}
        );
	}
#endif

//* If MQTT support needed
//* MQTT callback handling helper functions
//*----------------------------------------
//#if MQTT_SUPPORT
//    void _pluginMQTTCallback(type, topic, payload) {
//        if (type == MQTT_CONNECT_EVENT) {
          //* Subscribe to own /set topic
//            mqttSubscribe(topic);
          //* Subscribe to group topics
//            mqttSubscribeRaw(group);
//       }
//       if (type == MQTT_MESSAGE_EVENT) {
            //* manage mtww palyload here
//         String t = mqttMagnitude((char *) topic);
            //* manage group topics code here
//         }
//          if (type == MQTT_DISCONNECT_EVENT) {
             //* MQTT disonnect code here
//          }
//      }

//      void _pluginSetupMQTT() {
//          _mqttRegister(_pluginMQTTCallback);
//      }
//#endif

//* If terminal Terminal commands needed
//* Plugin terminal commands helper function
//*-----------------------------------------
#if TERMINAL_SUPPORT
      void _pluginInitCommands() {
          //* Register Terminal commad to turn on/off the plugin
          //* use this as template to create additional plugin terminal commands
          terminalRegisterCommand(F("PLUGIN"), [](Embedis* e) {
                  if (e->argc == 1) {              //Got only /PLUGIN?apikey=xxxxxx query mode
                      DEBUG_MSG_P(PSTR("[PLUGIN] Status: %s\n"), _plugin_enabled ? "ON" : "OFF");
                      DEBUG_MSG_P(PSTR("Send 0/1 to enable/disable\n"));
                      DEBUG_MSG_P(PSTR("+OK\n"));
                      return;
                  }
                  if (e->argc > 1) {                //at least two params second param handled as value
                      _plugin_enabled = (String(e->argv[1]).toInt() == 1);
                      setSetting("PLG1_EN", _plugin_enabled);
                      DEBUG_MSG_P(PSTR("[PLUGIN] Set Status: %s\n"), _plugin_enabled ? "ON" : "OFF");
                      DEBUG_MSG_P(PSTR("+OK\n"));
                  }
              });

      }
#endif
#if BROKER_SUPPORT
void _pluginBroker(const String& topic, int id, unsigned int value) {
    //DEBUG_MSG_P(PSTR("[PLUGIN] Broker \n"));
    DEBUG_MSG_P(PSTR("[PLUGIN] Broker Event :%s id:%d value:%u\n"), topic.c_str(), id, value);
    if (topic.equals(MQTT_TOPIC_BUTTON)) {
        DEBUG_MSG_P(PSTR("[PLUGIN] Button #%d - %u\n"), id, value);
        if (id == 0 && value == 2) {
            logit("Door Bell");
        }
    } else if (topic.equals(MQTT_TOPIC_RELAY)) {
        DEBUG_MSG_P(PSTR("[PLUGIN] Relay #%d - %u\n"), id, value);
        if (value == 1) {
            logit("Gate On");
        } else if (value == 0) {
            logit("Gate Off");
        }
    }
}
#endif
//* end of helper functions
//*----------------------------------------------------------------------------

//*----------------------------------------------------------------------------
//* Plugin setup
//*----------------------------------------------------------------------------
void pluginSetup() {
    //*    plugin setup code
    //* myPluginSetup() is called by custom.h - espurna plugin entry point

    _plugin_enabled = getSetting("PLG_EN", 1 == PLUGIN_ENABLE);

    //* Register plugin loop to espurna main loop
    //*------------------------------------------
    espurnaRegisterLoop(_pluginLoop);

    #if BROKER_SUPPORT
    //* Register broker to get button pressed
    //*---------------------------------------
    StatusBroker::Register(_pluginBroker);
    #endif

    //* If API used set up Api
    //*-----------------------
    #if WEB_SUPPORT
        _pluginSetupAPI();
    #endif

    //* If Web Sockets set up WS
    //*-------------------------
//    #if WEB_SUPPORT
//        _pluginSetupWS();
//    #endif

    //* If MQTT used set up MQTT
    //*-------------------------
//    #if MQTT_SUPPORT
//        _pluginSetupMQTT();
//    #endif

    //* If trminal used set up terminal
    //*-------------------------------
	  #if TERMINAL_SUPPORT
	      _pluginInitCommands();
	  #endif
    DEBUG_MSG_P(PSTR("[PLUGIN] Plugin setup code finished \n"));
}
//* end of plugin setup
//*----------------------------------------------------------------------------

//*----------------------------------------------------------------------------
//* PLUGIN loop
//*----------------------------------------------------------------------------
void _pluginLoop() {
    //*   plugin loop code
    //* _pluginLoop regitered (espurnaRegisterLoop) by myPluginSetup()
    //* myPluginSetup() is called by custom.h - espurna plugin entry point

    //* if plugin disabled dont run the coded
    if (!_plugin_enabled) return;

    //* here call all plugin loop functions (copy sumple function as needed)
    _pluginFunction1();
}

//*----------------------------------------------------------------------------
//* Public - Plugin API
//*----------------------------------------------------------------------------
//* Here goes ublic plugin API definitions and coded
//* currently plugin enabled query implemented
//* use this as template to create additionl API calls
//* to Set/Get internal plugin data or use plugin functions
bool pluginEnabled() {
    return _plugin_enabled;
}
#endif  //#ifdef _PLUGIN_H
