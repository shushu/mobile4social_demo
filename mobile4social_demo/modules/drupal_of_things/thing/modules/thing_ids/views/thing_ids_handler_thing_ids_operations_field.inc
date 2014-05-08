<?php

/**
 * This field handler aggregates operations that can be done on a thing_ids
 * under a single field providing a more flexible way to present them in a view
 */
class thing_ids_handler_thing_ids_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['thing_ids_id'] = 'thing_ids_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('thing_ids', 'admin/drupal-of-things/identifiers/thing_ids', array($this->get_value($values, 'thing_ids_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
