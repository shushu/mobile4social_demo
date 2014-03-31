<?php
/**
 * @file
 * android_device.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function android_device_default_rules_configuration() {
  $items = array();
  $items['rules_when_thing_with_gcm_identifier_is_saved'] = entity_import('rules_config', '{ "rules_when_thing_with_gcm_identifier_is_saved" : {
      "LABEL" : "When thing with GCM identifier is saved",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Mobile4Social Privatemsg" ],
      "REQUIRES" : [ "rules", "privatemsg_rules", "gcm", "things" ],
      "ON" : { "things_update" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "things" ], "field" : "field_gcm_id" } },
        { "entity_has_field" : { "entity" : [ "things" ], "field" : "field_owner" } },
        { "NOT data_is_empty" : { "data" : [ "things:field-gcm-id" ] } },
        { "NOT data_is_empty" : { "data" : [ "things-unchanged:things-id" ] } },
        { "data_is_empty" : { "data" : [ "things-unchanged:field-gcm-id:things-ids-id" ] } }
      ],
      "DO" : [
        { "entity_fetch" : {
            "USING" : { "type" : "user", "id" : [ "things:field-owner:uid" ] },
            "PROVIDE" : { "entity_fetched" : { "thing_owner" : "Thing owner" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "user", "id" : "1" },
            "PROVIDE" : { "entity_fetched" : { "admin" : "Site admin" } }
          }
        },
        { "privatemsg_rules_new" : {
            "USING" : {
              "recipient" : [ "thing-owner" ],
              "author" : [ "admin" ],
              "subject" : "Welcome to [site:name]",
              "body" : "Welcome to [site:name], and thanks for using Mobile4Social Privatemsg Android application.\\r\\nPlease feel free to use it to interact with mobile4Social users and any other user of the site, and to ask anything related to the site and its concept.\\r\\nRegards,\\r\\nMobile4Social.com"
            },
            "PROVIDE" : { "thread_id" : { "thread_id" : "ID of new thread" } }
          }
        },
        { "entity_fetch" : {
            "USING" : { "type" : "things_ids", "id" : [ "things:field-gcm-id:things-ids-id" ] },
            "PROVIDE" : { "entity_fetched" : { "gcm_id" : "GCM identifier" } }
          }
        },
        { "gcm_action_send_message" : {
            "tokens" : "[gcm-id:token]",
            "keyValue" : "type=user,action=index",
            "delay_while_idle" : 0,
            "time_to_live" : "3600",
            "collapse_key" : "user_index"
          }
        }
      ]
    }
  }');
  return $items;
}
