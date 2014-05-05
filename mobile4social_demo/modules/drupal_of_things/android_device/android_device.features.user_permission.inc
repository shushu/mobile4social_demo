<?php
/**
 * @file
 * android_device.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function android_device_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer thing_ids'.
  $permissions['administer thing_ids'] = array(
    'name' => 'administer thing_ids',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'thing_ids',
  );

  // Exported permission: 'create thing services'.
  $permissions['create thing services'] = array(
    'name' => 'create thing services',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_services',
  );

  // Exported permission: 'delete thing services'.
  $permissions['delete thing services'] = array(
    'name' => 'delete thing services',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_services',
  );

  // Exported permission: 'edit any android_device thing'.
  $permissions['edit any android_device thing'] = array(
    'name' => 'edit any android_device thing',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing',
  );

  // Exported permission: 'edit any field_device_id thing_ids'.
  $permissions['edit any field_device_id thing_ids'] = array(
    'name' => 'edit any field_device_id thing_ids',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_ids',
  );

  // Exported permission: 'edit any field_gcm_id thing_ids'.
  $permissions['edit any field_gcm_id thing_ids'] = array(
    'name' => 'edit any field_gcm_id thing_ids',
    'roles' => array(),
    'module' => 'thing_ids',
  );

  // Exported permission: 'get a system variable'.
  $permissions['get a system variable'] = array(
    'name' => 'get a system variable',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'services',
  );

  // Exported permission: 'retrieve thing services'.
  $permissions['retrieve thing services'] = array(
    'name' => 'retrieve thing services',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_services',
  );

  // Exported permission: 'update thing services'.
  $permissions['update thing services'] = array(
    'name' => 'update thing services',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_services',
  );

  // Exported permission: 'view any android_device thing'.
  $permissions['view any android_device thing'] = array(
    'name' => 'view any android_device thing',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing',
  );

  // Exported permission: 'view any field_device_id thing_ids'.
  $permissions['view any field_device_id thing_ids'] = array(
    'name' => 'view any field_device_id thing_ids',
    'roles' => array(
      'administrator' => 'administrator',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'thing_ids',
  );

  // Exported permission: 'view any field_gcm_id thing_ids'.
  $permissions['view any field_gcm_id thing_ids'] = array(
    'name' => 'view any field_gcm_id thing_ids',
    'roles' => array(),
    'module' => 'thing_ids',
  );

  return $permissions;
}
