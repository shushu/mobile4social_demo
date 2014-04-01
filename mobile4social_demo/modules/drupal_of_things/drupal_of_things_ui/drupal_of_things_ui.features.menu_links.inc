<?php
/**
 * @file
 * drupal_of_things_ui.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function drupal_of_things_ui_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_drupal-of-things:node
  $menu_links['management_drupal-of-things:node'] = array(
    'menu_name' => 'management',
    'link_path' => 'node',
    'router_path' => 'node',
    'link_title' => 'Drupal of Things',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'management_drupal-of-things:node',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -20,
    'customized' => 1,
    'parent_identifier' => 'management_administration:admin',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Drupal of Things');


  return $menu_links;
}
