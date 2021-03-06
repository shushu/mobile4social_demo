<?php

/**
 * This field handler aggregates operations that can be done on a state_entity
 * under a single field providing a more flexible way to present them in a view
 */
class state_entity_handler_state_entity_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['state_entity_id'] = 'state_entity_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('state_entity', 'admin/drupal-of-things/state-entity/state-entity', array($this->get_value($values, 'state_entity_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
