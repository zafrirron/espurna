#ifdef INCLUDE_PLUGIN
#ifndef _PLUGIN_H
#define _PLUGIN_H


//*---------------------------------------------------------------------------
//* Espurna overrides
//* -------------------------------------------------------------------------
//*  Put here espurna defines overrides
#define API_RESTFUL                 0
//---------------------------------------------------------------------------
//* Plugin defines
//----------------------------------------------------------------------------
//* Put here plpugin specific defines
//* plese refer to plugin.ino for more help and inline documentaion

//* Plugin enabled flag (enabling or disabling execution)
#define PLUGIN_ENABLE             1

//* plugin API endpoint
#define API_PLUGIN_ENDPOINT        "PLUGIN"
#define API_SERVO_ENDPOINT      "SERVO"

//* sample plugin MQTT topic
#define MQTT_TOPIC_PLUGIN          "PLUGIN"
#define MQTT_TOPIC_SERVO           "SERVO"

//* Sample plugin reporting interval (0 no reporting)
#define PLUGIN_REPORT_EVERY         0          //sec

//* Plugin running frequency
#define PLUGIN_RUN_EVERY            0         //msec

//* Sample plugin parameter values
#define PLUGIN_PARAMETER_1         0

// Servo Defines
#define SERVO_PIN                   15        //GPIO
#define SERVO_MAX_VALUE             180     //Angle Deg
#define SERVO_INC_VALUE             5       //Angle Deg


//------------------------------------------------------------
//* Plugin public interface
//------------------------------------------------------------
//* declare the plugin setup function (used by custom.h)
void pluginSetup();
//* get plugin enabled state
bool plugin1Enabled();
static auto _last_run = millis();
bool _bell_pressed = false;
bool _gate_open = false;

#endif
#endif
