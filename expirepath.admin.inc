<?php

/**
 * Admin form for issuing purge requests.
 */
function expirepath_admin_form() {
  $form['expirepath_path_to_expire'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to expire'),
    // Todo: Update description.
    '#description' => t('Something meaningful about what to do'),
    '#required' => TRUE,
    '#size' => 120,
  );
  $form['expirepath_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );

  return $form;
}

/**
 * Submit handler for expirepath_admin_form.
 */
function expirepath_admin_form_submit(&$form, &$form_state) {
  // Don't want possible nasty XSS things being sent to external proxy,
  // however unlikely it is to do anything too awful.
  $path = filter_xss($form_state['values']['expirepath_path_to_expire']);

  // Expire url.
  $internal_paths = array();
  if ($path === 'FRONT') {
    $internal_paths += ExpireAPI::getFrontPageUrls();
  }
  else {
    $internal_paths[] = $path;
  }

  // Expire internal paths.
  ExpireAPI::executeExpiration($internal_paths);
}
