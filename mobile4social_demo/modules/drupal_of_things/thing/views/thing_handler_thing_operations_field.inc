<?php

/**
 * This field handler aggregates operations that can be done on a things
 * under a single field providing a more flexible way to present them in a view
 */
class things_handler_things_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['thing_id'] = 'thing_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('thing', 'admin/drupal-of-things/things', array($this->get_value($values, 'thing_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
