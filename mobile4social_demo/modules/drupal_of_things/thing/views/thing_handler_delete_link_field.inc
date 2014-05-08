<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */


class thing_handler_delete_link_field extends thing_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }


  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy thing to check access against
    $dummy_thing = (object) array('type' => $type);
    if (!thing_access('edit', $dummy_thing)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $thing_id = $values->{$this->aliases['thing_id']};
    
    return l($text, 'admin/drupal-of-things/thing/' . $thing_id . '/delete');
  }
}
