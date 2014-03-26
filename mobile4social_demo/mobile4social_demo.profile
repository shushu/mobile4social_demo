<?php

/**
 * Implements hook_install_tasks().
 */
function mobile4social_demo_install_tasks($install_state) {
  $tasks = array();

  $tasks['mobile4social_demo_variables_set'] = array(
    'display_name' => t('Setting variables'),
  );

  return $tasks;
}

/**
 * Implements hook_install_tasks_alter().
 */
function mobile4social_demo_install_tasks_alter(&$tasks, $install_state) {
  $tasks['install_finished']['function'] = 'mobile4social_demo_install_finished';
  $tasks['install_finished']['display_name'] = t('Finished');
  $tasks['install_finished']['type'] = 'normal';
}


/**
 * Step for setting up variables.
 */
function mobile4social_demo_variables_set() {
  $variables = array(
    'theme_default' => 'bootstrap',
    'admin_theme' => 'seven',
    'user_register' => USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL,
    'jquery_update_jquery_version' => 1.8,
    'jquery_update_jquery_admin_version' => 1.5,
    'site_frontpage' => 'front',
  );

  foreach ($variables as $name => $value) {
    variable_set($name, $value);
  }
}

/**
 * Running the function when the installation process is finished.
 */
function mobile4social_demo_install_finished(&$install_state) {
  drupal_set_title(st('mobile4social_demo installation complete'));
  $messages = drupal_get_messages();
  $output = '<p>' . st('Congratulations, you\'ve successfully installed mobile4social_demo!') . '</p>';
  if (isset($messages['error'])) {
    $output .= '<p>' . st('There are some problems. Please check them.') . '</p>';
  }
  else {
    $output .= '<p>' . st('Your site has installed fully.') . '</p>';
  }

  $output .= '<p>' . t('Please go ahead and visit your <a href="@url">Website</a>', array('@url' => url(''))) . '</p>';

  // Flush all caches to ensure that any full bootstraps during the installer
  // do not leave stale cached data, and that any content types or other items
  // registered by the install profile are registered correctly.
  drupal_flush_all_caches();

  // Remember the profile which was used.
  variable_set('install_profile', drupal_get_profile());

  // Install profiles are always loaded last
  db_update('system')
    ->fields(array('weight' => 1000))
    ->condition('type', 'module')
    ->condition('name', drupal_get_profile())
    ->execute();

  // Cache a fully-built schema.
  drupal_get_schema(NULL, TRUE);

  // Remove the variable we used during the installation.
  variable_del('dh_dummy_content');

  // Run cron to populate update status tables (if available) so that users
  // will be warned if they've installed an out of date Drupal version.
  // Will also trigger indexing of profile-supplied content or feeds.
  drupal_cron_run();

  return $output;
}
