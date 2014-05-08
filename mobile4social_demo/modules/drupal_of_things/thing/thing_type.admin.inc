<?php

/**
 * @file
 * Thing type editing UI.
 */

/**
 * UI controller.
 */
class ThingTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage thing entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the thing type editing form.
 */
function thing_type_form($form, &$form_state, $thing_type, $op = 'edit') {

  if ($op == 'clone') {
    $thing_type->label .= ' (cloned)';
    $thing_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $thing_type->label,
    '#description' => t('The human-readable name of this thing type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($thing_type->type) ? $thing_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'thing_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this thing type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save thing type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function thing_type_form_submit(&$form, &$form_state) {
  $thing_type = entity_ui_form_submit_build_entity($form, $form_state);
  $thing_type->save();
  $form_state['redirect'] = 'admin/drupal-of-things/configuration/thing-types';
}

/**
 * Form API submit callback for the delete button.
 */
function thing_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/drupal-of-things/configuration/thing-types/manage/' . $form_state['thing_type']->type . '/delete';
}
