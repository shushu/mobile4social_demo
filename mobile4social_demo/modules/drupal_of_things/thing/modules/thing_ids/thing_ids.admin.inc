<?php

/**
 * @file
 * thing_ids editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class thing_idsUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Things Identifiers',
      'description' => 'Add edit and update Things Identifiers.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of Things Identifiers.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a Things Identifier',
      'description' => 'Add a new Things Identifier',
      'page callback'  => 'thing_ids_add_page',
      'access callback'  => 'thing_ids_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'thing_ids.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (thing_ids_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'thing_ids_form_wrapper',
        'page arguments' => array(thing_ids_create(array('type' => $type->type))),
        'access callback' => 'thing_ids_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'thing_ids.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing thing_ids entities
    $items[$this->path . '/thing_ids/' . $wildcard] = array(
      'page callback' => 'thing_ids_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'thing_ids_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'thing_ids.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/thing_ids/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/thing_ids/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'thing_ids_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'thing_ids_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'thing_ids.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing Things Identifiers
    $items['thing_ids/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'thing_ids_page_title',
      'title arguments' => array(1),
      'page callback' => 'thing_ids_page_view',
      'page arguments' => array(1),
      'access callback' => 'thing_ids_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add thing_ids Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('thing_ids_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a thing_ids.
 *
 * @param $thing_ids
 *   The thing_ids object being edited by this form.
 *
 * @see thing_ids_edit_form()
 */
function thing_ids_form_wrapper($thing_ids) {
  // Add the breadcrumb for the form's location.
  thing_ids_set_breadcrumb();
  return drupal_get_form('thing_ids_edit_form', $thing_ids);
}


/**
 * Form callback wrapper: delete a thing_ids.
 *
 * @param $thing_ids
 *   The thing_ids object being edited by this form.
 *
 * @see thing_ids_edit_form()
 */
function thing_ids_delete_form_wrapper($thing_ids) {
  // Add the breadcrumb for the form's location.
  //thing_ids_set_breadcrumb();
  return drupal_get_form('thing_ids_delete_form', $thing_ids);
}


/**
 * Form callback: create or edit a thing_ids.
 *
 * @param $thing_ids
 *   The thing_ids object to edit or for a create form an empty thing_ids object
 *     with only a Things Identifier type defined.
 */
function thing_ids_edit_form($form, &$form_state, $thing_ids) {
  // Add the default field elements.
  $form['token'] = array(
    '#type' => 'textfield',
    '#title' => t('Things Identifier Token'),
    '#default_value' => isset($thing_ids->token) ? $thing_ids->token : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  // Add the field related form elements.
  $form_state['thing_ids'] = $thing_ids;
  field_attach_form('thing_ids', $thing_ids, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save thing_ids'),
    '#submit' => $submit + array('thing_ids_edit_form_submit'),
  );
  
  if (!empty($thing_ids->token)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete thing_ids'),
      '#suffix' => l(t('Cancel'), 'admin/drupal-of-things/identifiers'),
      '#submit' => $submit + array('thing_ids_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'thing_ids_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the thing_ids form
 */
function thing_ids_edit_form_validate(&$form, &$form_state) {
  $thing_ids = $form_state['thing_ids'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('thing_ids', $thing_ids, $form, $form_state);
}


/**
 * Form API submit callback for the thing_ids form.
 * 
 * @todo remove hard-coded link
 */
function thing_ids_edit_form_submit(&$form, &$form_state) {
  
  $thing_ids = entity_ui_controller('thing_ids')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the thing_ids and go back to the list of Things Identifiers
  
  // Add in created and changed times.
  if ($thing_ids->is_new = isset($thing_ids->is_new) ? $thing_ids->is_new : 0){
    $thing_ids->created = time();
  }

  $thing_ids->changed = time();
  
  $thing_ids->save();
  $form_state['redirect'] = 'admin/drupal-of-things/identifiers';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function thing_ids_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/drupal-of-things/identifiers/thing_ids/' . $form_state['thing_ids']->thing_ids_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a thing_ids.
 *
 * @param $thing_ids
 *   The thing_ids to delete
 *
 * @see confirm_form()
 */
function thing_ids_delete_form($form, &$form_state, $thing_ids) {
  $form_state['thing_ids'] = $thing_ids;

  $form['#submit'][] = 'thing_ids_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete thing_ids %token?', array('%token' => $thing_ids->token)),
    'admin/drupal-of-things/identifiers/thing_ids',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for thing_ids_delete_form
 */
function thing_ids_delete_form_submit($form, &$form_state) {
  $thing_ids = $form_state['thing_ids'];

  thing_ids_delete($thing_ids);

  drupal_set_message(t('The thing_ids %token has been deleted.', array('%token' => $thing_ids->token)));
  watchdog('thing_ids', 'Deleted Things Identifier %token.', array('%token' => $thing_ids->token));

  $form_state['redirect'] = 'admin/drupal-of-things/identifiers';
}



/**
 * Page to add thing_ids Entities.
 *
 * @todo Pass this through a proper theme function
 */
function thing_ids_add_page() {
  $controller = entity_ui_controller('thing_ids');
  return $controller->addPage();
}


/**
 * Displays the list of available Things Identifier types for thing_ids creation.
 *
 * @ingroup themeable
 */
function theme_thing_ids_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="thing_ids-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer thing_ids types')) {
      $output = '<p>' . t('Things Identifiers Entities cannot be added because you have not created any Things Identifier types yet. Go to the <a href="@create-thing_ids-type">thing_ids type creation page</a> to add a new Things Identifier type.', array('@create-thing_ids-type' => url('admin/drupal-of-things/configuration/identifiers-types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No Things Identifier types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative thing_ids pages.
 */
function thing_ids_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Drupal of Things'), 'admin/drupal-of-things'),
    l(t('Identifiers'), 'admin/drupal-of-things/identifiers'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



