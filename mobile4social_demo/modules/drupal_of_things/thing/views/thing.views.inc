<?php

/**
 * @file
 * Providing extra functionality for the Thing UI via views.
 */


/**
 * Implements hook_views_data()
 */
function thing_views_data_alter(&$data) {
  $data['thing']['link_thing'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the thing.'),
      'handler' => 'thing_handler_link_field',
    ),
  );
  $data['thing']['edit_thing'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the thing.'),
      'handler' => 'thing_handler_edit_link_field',
    ),
  );
  $data['thing']['delete_thing'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the thing.'),
      'handler' => 'thing_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows thing/thing/%thing_id/op
  $data['thing']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this thing.'),
      'handler' => 'thing_handler_thing_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function thing_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'thing';
  $view->description = 'A list of all thing';
  $view->tag = 'thing';
  $view->base_table = 'thing';
  $view->human_name = 'Thing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Thing';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any thing type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'thing_id' => 'thing_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'thing_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['content'] = 'No thing have been created yet';
  /* Field: Thing: Thing ID */
  $handler->display->display_options['fields']['thing_id']['id'] = 'thing_id';
  $handler->display->display_options['fields']['thing_id']['table'] = 'thing';
  $handler->display->display_options['fields']['thing_id']['field'] = 'thing_id';
  /* Field: Thing: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'thing';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Thing: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'thing';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Thing: Link */
  $handler->display->display_options['fields']['link_thing']['id'] = 'link_thing';
  $handler->display->display_options['fields']['link_thing']['table'] = 'thing';
  $handler->display->display_options['fields']['link_thing']['field'] = 'link_thing';
  $handler->display->display_options['fields']['link_thing']['label'] = 'View';
  /* Field: Thing: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'thing';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'thing_admin_page');
  $handler->display->display_options['path'] = 'admin/drupal-of-things/thing';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Thing';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Drupal of Things';
  $handler->display->display_options['tab_options']['description'] = 'Manage thing';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['thing'] = array(
    t('Master'),
    t('Thing'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty '),
    t('No thing have been created yet'),
    t('Thing ID'),
    t('.'),
    t(','),
    t('Type'),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views['thing_view'] = $view;
  return $views;

}
