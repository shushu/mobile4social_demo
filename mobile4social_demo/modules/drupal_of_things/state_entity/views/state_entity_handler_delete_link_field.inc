<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class state_entity_handler_delete_link_field extends state_entity_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy state_entity to check access against
    $dummy_state_entity = (object) array('type' => $type);
    if (!state_entity_access('edit', $dummy_state_entity)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $state_entity_id = $values->{$this->aliases['state_entity_id']};
    
    return l($text, 'admin/drupal-of-things/state-entity/state-entity/' . $state_entity_id . '/delete');
  }
}
