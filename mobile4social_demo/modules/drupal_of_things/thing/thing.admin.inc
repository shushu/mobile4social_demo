<?php

/**
 * @file
 * Thing editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class ThingUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Thing',
      'description' => 'Add edit and update thing.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of thing.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a thing',
      'description' => 'Add a new thing',
      'page callback'  => 'thing_add_page',
      'access callback'  => 'thing_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'thing.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (thing_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'thing_form_wrapper',
        'page arguments' => array(thing_create(array('type' => $type->type))),
        'access callback' => 'thing_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'thing.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing thing entities
    $items[$this->path . '/thing/' . $wildcard] = array(
      'page callback' => 'thing_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'thing_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'thing.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/thing/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/thing/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'thing_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'thing_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'thing.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing thing
    $items['thing/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'thing_page_title',
      'title arguments' => array(1),
      'page callback' => 'thing_page_view',
      'page arguments' => array(1),
      'access callback' => 'thing_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add Thing Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('thing_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a thing.
 *
 * @param $thing
 *   The thing object being edited by this form.
 *
 * @see thing_edit_form()
 */
function thing_form_wrapper($thing) {
  // Add the breadcrumb for the form's location.
  thing_set_breadcrumb();
  return drupal_get_form('thing_edit_form', $thing);
}


/**
 * Form callback wrapper: delete a thing.
 *
 * @param $thing
 *   The thing object being edited by this form.
 *
 * @see thing_edit_form()
 */
function thing_delete_form_wrapper($thing) {
  // Add the breadcrumb for the form's location.
  //thing_set_breadcrumb();
  return drupal_get_form('thing_delete_form', $thing);
}


/**
 * Form callback: create or edit a thing.
 *
 * @param $thing
 *   The thing object to edit or for a create form an empty thing object
 *     with only a thing type defined.
 */
function thing_edit_form($form, &$form_state, $thing) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Thing Name'),
    '#default_value' => isset($thing->name) ? $thing->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  
  // Add the field related form elements.
  $form_state['thing'] = $thing;
  field_attach_form('thing', $thing, $form, $form_state);

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
    '#value' => t('Save thing'),
    '#submit' => $submit + array('thing_edit_form_submit'),
  );
  
  if (!empty($thing->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete thing'),
      '#suffix' => l(t('Cancel'), 'admin/drupal-of-things/thing'),
      '#submit' => $submit + array('thing_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'thing_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the thing form
 */
function thing_edit_form_validate(&$form, &$form_state) {
  $thing = $form_state['thing'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('thing', $thing, $form, $form_state);
}


/**
 * Form API submit callback for the thing form.
 * 
 * @todo remove hard-coded link
 */
function thing_edit_form_submit(&$form, &$form_state) {
  
  $thing = entity_ui_controller('thing')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the thing and go back to the list of thing
  
  // Add in created and changed times.
  if ($thing->is_new = isset($thing->is_new) ? $thing->is_new : 0){
    $thing->created = time();
  }

  $thing->changed = time();
  
  $thing->save();
  $form_state['redirect'] = 'admin/drupal-of-things/thing';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function thing_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/drupal-of-things/' . $form_state['thing']->thing_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a thing.
 *
 * @param $thing
 *   The thing to delete
 *
 * @see confirm_form()
 */
function thing_delete_form($form, &$form_state, $thing) {
  $form_state['thing'] = $thing;

  $form['#submit'][] = 'thing_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete thing %name?', array('%name' => $thing->name)),
    'admin/drupal-of-things/thing',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for thing_delete_form
 */
function thing_delete_form_submit($form, &$form_state) {
  $thing = $form_state['thing'];

  thing_delete($thing);

  drupal_set_message(t('The thing %name has been deleted.', array('%name' => $thing->name)));
  watchdog('thing', 'Deleted thing %name.', array('%name' => $thing->name));

  $form_state['redirect'] = 'admin/drupal-of-things/thing';
}



/**
 * Page to add Thing Entities.
 *
 * @todo Pass this through a proper theme function
 */
function thing_add_page() {
  $controller = entity_ui_controller('thing');
  return $controller->addPage();
}


/**
 * Displays the list of available thing types for thing creation.
 *
 * @ingroup themeable
 */
function theme_thing_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="thing-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer thing types')) {
      $output = '<p>' . t('Thing Entities cannot be added because you have not created any thing types yet. Go to the <a href="@create-thing-type">thing type creation page</a> to add a new thing type.', array('@create-thing-type' => url('admin/drupal-of-things/configuration/thing-types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No thing types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative thing pages.
 */
function thing_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Thing'), 'admin/drupal-of-things/thing'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



