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

  // Exported permission: 'administer things_ids'.
  $permissions['administer things_ids'] = array(
    'name' => 'administer things_ids',
    'roles' => array(),
    'module' => 'things_ids',
  );

  // Exported permission: 'create things services'.
  $permissions['create things services'] = array(
    'name' => 'create things services',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_services',
  );

  // Exported permission: 'delete things services'.
  $permissions['delete things services'] = array(
    'name' => 'delete things services',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_services',
  );

  // Exported permission: 'edit any android_device things'.
  $permissions['edit any android_device things'] = array(
    'name' => 'edit any android_device things',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things',
  );

  // Exported permission: 'edit any field_device_id things_ids'.
  $permissions['edit any field_device_id things_ids'] = array(
    'name' => 'edit any field_device_id things_ids',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_ids',
  );

  // Exported permission: 'edit any field_gcm_id things_ids'.
  $permissions['edit any field_gcm_id things_ids'] = array(
    'name' => 'edit any field_gcm_id things_ids',
    'roles' => array(),
    'module' => 'things_ids',
  );

  // Exported permission: 'get a system variable'.
  $permissions['get a system variable'] = array(
    'name' => 'get a system variable',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'services',
  );

  // Exported permission: 'retrieve things services'.
  $permissions['retrieve things services'] = array(
    'name' => 'retrieve things services',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_services',
  );

  // Exported permission: 'update things services'.
  $permissions['update things services'] = array(
    'name' => 'update things services',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_services',
  );

  // Exported permission: 'view any android_device things'.
  $permissions['view any android_device things'] = array(
    'name' => 'view any android_device things',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things',
  );

  // Exported permission: 'view any field_device_id things_ids'.
  $permissions['view any field_device_id things_ids'] = array(
    'name' => 'view any field_device_id things_ids',
    'roles' => array(
      'mobile4social' => 'mobile4social',
    ),
    'module' => 'things_ids',
  );

  // Exported permission: 'view any field_gcm_id things_ids'.
  $permissions['view any field_gcm_id things_ids'] = array(
    'name' => 'view any field_gcm_id things_ids',
    'roles' => array(),
    'module' => 'things_ids',
  );

  return $permissions;
}
