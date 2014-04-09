<?php

/**
 * @file
 * Pages provided by the module.
 */

/**
 * Page callback for the my rules overview page of the current user.
 */
function my_rules_overview_page_current_user() {
  global $user;
  if ($user->uid) {
    // Adjust my-rules/page/X pages to my-rules/CURRENT_UID/page/X.
    $arg = arg(1);
    if ($arg) {
      $path = str_replace("my-rules/$arg", "my-rules/$user->uid/$arg", current_path());
      menu_set_active_item($path);
    }
    else {
      $path = str_replace("my-rules", "my-rules/$user->uid", current_path());
      menu_set_active_item($path);
    }
    return menu_execute_active_handler(NULL, FALSE);
  }
  else {
    return MENU_ACCESS_DENIED;
  }
}

/**
 * Form builder for the my rules overview page.
 */
function my_rules_overview_page($form, &$form_state, $base_path, $account) {
  RulesPluginUI::$basePath = $base_path;
  RulesPluginUI::formDefaults($form, $form_state);

  $conditions = array(
    'plugin' => 'reaction rule',
    'uid' => $account->uid,
    'owner' => 'my_rules',
  );
  $collapsed = TRUE;
  if (empty($_GET['tag'])) {
    $tag = 0;
  }
  else {
    $tag = $_GET['tag'];
    $conditions['tags'] = array($tag);
    $collapsed = FALSE;
  }
  if (empty($_GET['event'])) {
    $event = 0;
  }
  else {
    $event = $_GET['event'];
    // Filter using a wildcard suffix so configured event names with suffixes
    // are found also.
    $conditions['event'] = $event . '%';
    $collapsed = FALSE;
  }
  $form['sidebar']['#prefix'] = '<div class="l-my-rules-overview--sidebar">';
  $form['sidebar']['#suffix'] = '</div>';

  $form['sidebar']['filter'] = array(
    '#prefix' => '<div class="my-rules-overview--filter"><h2>' . t('Filter rules') . '</h2><div class="content">',
    '#suffix' => '</div></div>'
  );
  $form['sidebar']['filter']['#id'] = 'rules-filter-form';
  $form['sidebar']['filter']['#attached']['css'][] = drupal_get_path('module', 'rules') . '/ui/rules.ui.css';
  $form['sidebar']['filter']['event'] = array(
    '#type' => 'select',
    '#title' => t('Filter by event'),
    '#options' => array(0 => t('<All>')) + RulesPluginUI::getOptions('event'),
    '#default_value' => $event,
  );
  $form['sidebar']['filter']['tag'] = array(
    '#type' => 'select',
    '#title' => t('Filter by tag'),
    '#options' => array(0 => t('<All>')) + RulesPluginUI::getTags(),
    '#default_value' => $tag,
  );
  $form['sidebar']['filter']['#empty'] = 'test';
  $form['sidebar']['filter']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#name' => '', // prevent from showing up in $_GET.
  );

  $form['sidebar']['help'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="my-rules-overview--help"><h2>' . t('Help') . '</h2><div class="content">',
    '#suffix' => '</div></div>',
    '#markup' => t('Rules react on selected <em>events</em> (When) and may fire any number of <em>actions</em> (Then).'),
  );

  $options = array('show plugin' => FALSE, 'base path' => $base_path);
  $form['main']['#prefix'] = '<div class="l-my-rules-overview--main">';
  $form['main']['#suffix'] = '</div>';

  $form['main']['#markup'] = my_rules_ui()->overviewTable($conditions, $options);
  //TODO: Use views and entity templates instead

  $form['#empty'] = t('There are no rules. ;)<br /><br /><a href="!url">Add a new rule</a>.', array('!url' => url($base_path . '/add')));

  $form['main']['filter']['#collapsed'] = $collapsed;
  $form['#submit'][] = 'rules_form_submit_rebuild';
  $form['#method'] = 'get';

  return $form;
}

/**
 * Add reaction rule form.
 */
function my_rules_add_reaction_rule($form, &$form_state, $base_path, $account) {
  RulesPluginUI::$basePath = $base_path;
  RulesPluginUI::formDefaults($form, $form_state);

  $rules_config = isset($form_state['rules_config']) ? $form_state['rules_config'] : rules_reaction_rule();
  $rules_config->uid = $account->uid;
  $rules_config->owner = 'my_rules';
  $rules_config->module = 'my_rules';
  $rules_config->form($form, $form_state, array('show settings' => TRUE, 'button' => TRUE));

  $form['settings']['#collapsible'] = FALSE;
  $form['settings']['#type'] = 'container';
  $form['settings']['label']['#default_value'] = '';

  // Hide the rule elements stuff for now.
  foreach (array('elements', 'conditions', 'add', 'events') as $key) {
    $form[$key]['#access'] = FALSE;
  }
  foreach (array('active', 'weight') as $key) {
    $form['settings'][$key]['#access'] = FALSE;
  }
  // Incorporate the form to add the first event.
  $form['settings'] += rules_ui_add_event(array(), $form_state, $rules_config, $base_path);
  $form['settings']['event']['#tree'] = FALSE;
  $form['settings']['event_settings']['#tree'] = FALSE;
  unset($form['settings']['help']);

  unset($form['settings']['submit']);
  $form['submit']['#value'] = t('Save');

  $form_state += array('rules_config' => $rules_config);
  $form['#validate'][] = 'my_rules_add_reaction_rule_validate';
  $form['#validate'][] = 'rules_ui_edit_element_validate';
  $form['#submit'][] = 'my_rules_add_reaction_rule_submit';
  return $form;
}

/**
 * Form validation callback.
 */
function my_rules_add_reaction_rule_validate(&$form, &$form_state) {
  rules_ui_add_event_validate($form['settings'], $form_state);
}

/**
 * Form submit callback.
 */
function my_rules_add_reaction_rule_submit(&$form, &$form_state) {
  rules_ui_add_event_apply($form['settings'], $form_state);
  rules_ui_edit_element_submit($form, $form_state);
}

/**
 * Import form for rule configurations.
 */
function my_rules_ui_import_form($form, &$form_state, $base_path, $account) {
  RulesPluginUI::$basePath = $base_path;
  RulesPluginUI::formDefaults($form, $form_state);

  $form = rules_ui_import_form($form, $form_state, $base_path);
  $form_state['uid'] = $account->uid;
  $form['#validate'][]  = 'rules_ui_import_form_validate';
  $form['#validate'][]  = 'my_rules_ui_import_form_validate';
  $form['#submit'][]  = 'my_rules_ui_import_form_submit';
  $form['#submit'][]  = 'rules_ui_import_form_submit';
  return $form;
}

/**
 * Validation callback for the import form.
 */
function my_rules_ui_import_form_validate($form, &$form_state) {
  if (isset($form_state['rules_config']) && $form_state['values']['overwrite']) {
    // Store the successfully imported entity in $form_state.
    $existing_config = rules_config_load($form_state['rules_config']->name);

    if ($existing_config && ($existing_config->uid != $form_state['uid'] || $existing_config->owner != 'my_rules')) {
      $vars = array('@entity' => t('Rules configuration'), '%label' => $form_state['rules_config']->label());
      form_set_error('import', t('Import of @entity %label failed, a @entity with the same machine name already exists but cannot be overwritten.', $vars));
    }
  }
}

/**
 * Form submit callback.
 */
function my_rules_ui_import_form_submit($form, &$form_state) {
  $rules_config = $form_state['rules_config'];
  $rules_config->uid = $form_state['uid'];
  $rules_config->owner = 'my_rules';
  $rules_config->module = 'my_rules';
}

