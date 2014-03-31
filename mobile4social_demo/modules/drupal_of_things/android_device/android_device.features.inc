<?php
/**
 * @file
 * android_device.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function android_device_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function android_device_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_things_ids_type().
 */
function android_device_default_things_ids_type() {
  $items = array();
  $items['field_device_id'] = entity_import('things_ids_type', '{
    "type" : "field_device_id",
    "label" : "Android device id",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  $items['field_gcm_id'] = entity_import('things_ids_type', '{
    "type" : "field_gcm_id",
    "label" : "GCM Identifier",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_things_type().
 */
function android_device_default_things_type() {
  $items = array();
  $items['android_device'] = entity_import('things_type', '{
    "type" : "android_device",
    "label" : "Android device",
    "weight" : "0",
    "data" : "",
    "rdf_mapping" : []
  }');
  return $items;
}