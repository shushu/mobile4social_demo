<?php

/**
 * @file
 *
 * Plugin to provide a thing context
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Thing"),
  'description' => t('A single thing object.'),
  'context' => 'ctools_context_create_thing',
  'edit form' => 'ctools_context_thing_settings_form',
  'defaults' => array('thing_id' => ''),
  'keyword' => 'thing',
  'context name' => 'thing',
  'convert list' => 'ctools_context_thing_convert_list',
  'convert' => 'ctools_context_thing_convert',
  'convert default' => 'name',

  // This context is deprecated and should not be usable in the UI.
  'no ui' => TRUE,
  'no required context ui' => TRUE,
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function ctools_context_create_thing($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context(array('entity:thing', 'entity', 'thing'));
  $context->plugin = 'thing';

  if ($empty) {
    return $context;
  }

  if ($conf) {
    global $thing;
    if ($thing) {
      $data = thing_load($thing->thing_id);
    }
  }
  // Load entity if the data provided is a numeric value. This kind of data is
  // passed by some relationships.
  if (is_numeric($data)) {
    $data = thing_load($data);
  }

  if (!empty($data)) {
    $context->data     = $data;
    $context->title    = isset($data->name) ? $data->name : t('A thing');
    if (isset($data->thing_id)) {
      $context->argument = $data->thing_id;
    }
    return $context;
  }
}

function ctools_context_thing_settings_form($form, &$form_state) {

  return $form;
}

/**
 * Validate a user.
 */
function ctools_context_thing_settings_form_validate($form, &$form_state) {

}

function ctools_context_thing_settings_form_submit($form, &$form_state) {

}

/**
 * Provide a list of replacements.
 */
function ctools_context_thing_convert_list() {
  $tokens = token_info();
  foreach ($tokens['tokens']['thing'] as $id => $info) {
    if (!isset($list[$id])) {
      $list[$id] = $info['name'];
    }
  }

  return $list;
}

/**
 * Convert a context into a string.
 */
function ctools_context_thing_convert($context, $type) {
  $tokens = token_info();
  if (isset($tokens['tokens']['thing'][$type])) {
    $values = token_generate('thing', array($type => $type), array('thing' => $context->data));
    if (isset($values[$type])) {
      return $values[$type];
    }
  }
}
