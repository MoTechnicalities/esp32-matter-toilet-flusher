#include "Matter.h"
#include <app/server/OnboardingCodesUtil.h>
#include <credentials/examples/DeviceAttestationCredsExample.h>
#include <ESP32Servo.h>
using namespace chip;
using namespace chip::app::Clusters;
using namespace esp_matter;
using namespace esp_matter::endpoint;

/**
 * This program presents the ESP32 as a Matter plugin unit (switch) device with one endpoints 
 * with OnOff clusters by controlling a servo and LED via Matter and/or momentary contact buttons.
 * The project was developed to automate toilet flushing.
 *
 * You can toggle the plugin unit by both:
 *  - Matter (via CHIPTool or other Matter controller) or
 *  - toggle button (with debouncing)
 * When activated, the plugin unit will set the servo angle to a designated position for a designated time, then return
 * the servo angle and set the Matter device state to off again. Lower and Upper angle, and servo
 * pull time can be designated below.
 */

// Please configure your Servo, LED and Button PINs, Servo Pull Time delay in milliseconds, and Upper and Lower servo angles.
Servo myServo;
int servoPin = 13;
const int SERVO_PULL_TIME = 2000;
const int LED_PIN_1 = 23;
const int TOGGLE_BUTTON_PIN_1 = 22;
const int LOWER_ANGLE = 0;
const int UPPER_ANGLE = 179;

// Debounce for toggle button
const int DEBOUNCE_DELAY = 500;
int last_toggle;

// Cluster and attribute ID used by Matter plugin unit device
const uint32_t CLUSTER_ID = OnOff::Id;
const uint32_t ATTRIBUTE_ID = OnOff::Attributes::OnOff::Id;

// Endpoint and attribute ref that will be assigned to Matter device
uint16_t plugin_unit_endpoint_id_1 = 0;
attribute_t *attribute_ref_1;

// There is possibility to listen for various device events, related for example
// to setup process. Leaft empty for simplicity.
static void on_device_event(const ChipDeviceEvent *event, intptr_t arg) {}
static esp_err_t on_identification(identification::callback_type_t type,
                                   uint16_t endpoint_id, uint8_t effect_id,
                                   uint8_t effect_variant, void *priv_data) {
  return ESP_OK;
}

// Listener on attribute update requests.
// In this example, when update is requested, path (endpoint, cluster and
// attribute) is checked if it matches plugin unit attribute. If yes, LED changes
// state to new one.
static esp_err_t on_attribute_update(attribute::callback_type_t type,
                                     uint16_t endpoint_id, uint32_t cluster_id,
                                     uint32_t attribute_id,
                                     esp_matter_attr_val_t *val,
                                     void *priv_data) {
  if (type == attribute::PRE_UPDATE && cluster_id == CLUSTER_ID && attribute_id == ATTRIBUTE_ID) {
    // We got a plugin unit on/off attribute update!
    bool new_state = val->val.b;
    if (new_state) {
      // Lift the toilet tank's drain plug
      digitalWrite(LED_PIN_1, new_state);
      myServo.write(UPPER_ANGLE);
    }
    if (!new_state) {
      // Lower the toilet tank's drain plug
      myServo.write(LOWER_ANGLE);
      digitalWrite(LED_PIN_1, new_state);
    }
  }
  return ESP_OK;
}

void setup() {
  myServo.attach(servoPin);
  Serial.begin(115200);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(TOGGLE_BUTTON_PIN_1, INPUT_PULLUP);
  esp_log_level_set("*", ESP_LOG_DEBUG);

  // Setup Matter node
  node::config_t node_config;
  node_t *node = node::create(&node_config, on_attribute_update, on_identification);

  // Setup Plugin unit endpoint / cluster / attributes with default values
  on_off_plugin_unit::config_t plugin_unit_config;
  plugin_unit_config.on_off.on_off = false;
  plugin_unit_config.on_off.lighting.start_up_on_off = false;
  endpoint_t *endpoint_1 = on_off_plugin_unit::create(node, &plugin_unit_config,
                                                      ENDPOINT_FLAG_NONE, NULL);
  
  // Save on/off attribute reference. It will be used to read attribute value later.
  attribute_ref_1 =
    attribute::get(cluster::get(endpoint_1, CLUSTER_ID), ATTRIBUTE_ID);

  // Save generated endpoint id
  plugin_unit_endpoint_id_1 = endpoint::get_id(endpoint_1);

  // Setup DAC (this is good place to also set custom commission data, passcodes etc.)
  esp_matter::set_custom_dac_provider(chip::Credentials::Examples::GetExampleDACProvider());

  // Start Matter device
  esp_matter::start(on_device_event);

  // Print codes needed to setup Matter device
  PrintOnboardingCodes(
    chip::RendezvousInformationFlags(chip::RendezvousInformationFlag::kBLE));
}

// Reads plugin unit on/off attribute value
esp_matter_attr_val_t get_onoff_attribute_value(esp_matter::attribute_t *attribute_ref) {
  esp_matter_attr_val_t onoff_value = esp_matter_invalid(NULL);
  attribute::get_val(attribute_ref, &onoff_value);
 return onoff_value;
}

// Sets plugin unit on/off attribute value
void set_onoff_attribute_value(esp_matter_attr_val_t *onoff_value, uint16_t plugin_unit_endpoint_id) {
  attribute::update(plugin_unit_endpoint_id, CLUSTER_ID, ATTRIBUTE_ID, onoff_value);
  }

// When toggle plugin unit button is pressed (with debouncing),
// plugin unit attribute value is changed
//loop for button--------------------------------------------
void loop() {
  esp_matter_attr_val_t onoff_value = get_onoff_attribute_value(attribute_ref_1);
  if(onoff_value.val.b){
    set_onoff_attribute_value(&onoff_value, plugin_unit_endpoint_id_1);
    delay(SERVO_PULL_TIME);
    onoff_value.val.b = !onoff_value.val.b;
    set_onoff_attribute_value(&onoff_value, plugin_unit_endpoint_id_1);
  }
  if ((millis() - last_toggle) > DEBOUNCE_DELAY) {
    if (!digitalRead(TOGGLE_BUTTON_PIN_1)) {
      last_toggle = millis();
      // Read actual on/off value, invert it and set
      esp_matter_attr_val_t onoff_value = get_onoff_attribute_value(attribute_ref_1);
      onoff_value.val.b = !onoff_value.val.b;
      set_onoff_attribute_value(&onoff_value, plugin_unit_endpoint_id_1);
    }
  }
}