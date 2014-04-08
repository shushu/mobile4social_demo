<?php

/**
 * @file
 * Providing extra functionality for the Things UI via views.
 */


/**
 * Implements hook_views_data()
 */
function things_views_data_alter(&$data) { 
  $data['things']['link_things'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the things.'),
      'handler' => 'things_handler_link_field',
    ),
  );
  $data['things']['edit_things'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the things.'),
      'handler' => 'things_handler_edit_link_field',
    ),
  );
  $data['things']['delete_things'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the things.'),
      'handler' => 'things_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows things/things/%things_id/op
  $data['things']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this things.'),
      'handler' => 'things_handler_things_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function things_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'things';
  $view->description = 'A list of all things';
  $view->tag = 'things';
  $view->base_table = 'things';
  $view->human_name = 'Things';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Things';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create any things type';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'things_id' => 'things_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'things_id' => array(
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
  $handler->display->display_options['empty']['area']['content'] = 'No things have been created yet';
  /* Field: Things: Things ID */
  $handler->display->display_options['fields']['things_id']['id'] = 'things_id';
  $handler->display->display_options['fields']['things_id']['table'] = 'things';
  $handler->display->display_options['fields']['things_id']['field'] = 'things_id';
  /* Field: Things: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'things';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Things: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'things';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  /* Field: Things: Link */
  $handler->display->display_options['fields']['link_things']['id'] = 'link_things';
  $handler->display->display_options['fields']['link_things']['table'] = 'things';
  $handler->display->display_options['fields']['link_things']['field'] = 'link_things';
  $handler->display->display_options['fields']['link_things']['label'] = 'View';
  /* Field: Things: Operations links */
  $handler->display->display_options['fields']['operations']['id'] = 'operations';
  $handler->display->display_options['fields']['operations']['table'] = 'things';
  $handler->display->display_options['fields']['operations']['field'] = 'operations';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'things_admin_page');
  $handler->display->display_options['path'] = 'admin/drupal-of-things/things';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Things';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Drupal of Things';
  $handler->display->display_options['tab_options']['description'] = 'Manage things';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['things'] = array(
    t('Master'),
    t('Things'),
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
    t('No things have been created yet'),
    t('Things ID'),
    t('.'),
    t(','),
    t('Type'),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views['things_view'] = $view;
  return $views;

}
