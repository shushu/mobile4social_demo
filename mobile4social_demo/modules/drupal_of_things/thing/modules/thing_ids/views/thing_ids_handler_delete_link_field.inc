<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class thing_ids_handler_delete_link_field extends thing_ids_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy thing_ids to check access against
    $dummy_thing_ids = (object) array('type' => $type);
    if (!thing_ids_access('edit', $dummy_thing_ids)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $thing_ids_id = $values->{$this->aliases['thing_ids_id']};
    
    return l($text, 'admin/drupal-of-things/identifiers/thing_ids/' . $thing_ids_id . '/delete');
  }
}
