<?php

/**
 * @file
 * Thing Identifier type editing UI.
 */

/**
 * UI controller.
 */
class thing_idsTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage thing_ids entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the Thing Identifier type editing form.
 */
function thing_ids_type_form($form, &$form_state, $thing_ids_type, $op = 'edit') {

  if ($op == 'clone') {
    $thing_ids_type->label .= ' (cloned)';
    $thing_ids_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $thing_ids_type->label,
    '#description' => t('The human-readable name of this Thing Identifier type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($thing_ids_type->type) ? $thing_ids_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'thing_ids_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Thing Identifier type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Thing Identifier type'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function thing_ids_type_form_submit(&$form, &$form_state) {
  $thing_ids_type = entity_ui_form_submit_build_entity($form, $form_state);
  $thing_ids_type->save();
  $form_state['redirect'] = 'admin/drupal-of-things/configuration/identifiers-types';
}

/**
 * Form API submit callback for the delete button.
 */
function thing_ids_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/drupal-of-things/configuration/identifiers-types/manage/' . $form_state['thing_ids_type']->type . '/delete';
}
