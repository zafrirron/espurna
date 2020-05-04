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

//* sample plugin MQTT topic
#define MQTT_TOPIC_PLUGIN          "PLUGIN"
#define MQTT_TOPIC_PLUGIN_NAME     "TEMPLATE"

//* Plugin local log flag
#define PLUGIN_LOCAL_LOG          1
#define PLUGIN_LOG_HOST           "10.0.0.155"
#define PLUGIN_LOG_PORT           8000
#define PLUGIN_LOG_URI            "/" + MQTT_TOPIC_PLUGIN_NAME + "/log"

//* Sample plugin reporting interval (0 no reporting)
#define PLUGIN_REPORT_EVERY         0          //sec

//* Plugin running frequency
#define PLUGIN_RUN_EVERY            0         //msec

//* Sample plugin parameter values
#define PLUGIN_PARAMETER_1         0

// Plugin specific Defines

//------------------------------------------------------------
//* Plugin public interface
//------------------------------------------------------------
//* declare the plugin setup function (used by custom.h)
void pluginSetup();
//* get plugin enabled state
bool pluginEnabled();
static auto _last_run = millis();

#endif
#endif
