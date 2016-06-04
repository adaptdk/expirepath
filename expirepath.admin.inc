<?php

/**
 * Admin form for issuing purge requests.
 */
function expirepath_admin_form() {
  $form['expirepath_path_to_expire'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to expire'),
    '#description' => t('Write an internal path. For purging front page type: "FRONT".'),
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
  $path = filter_xss(trim($form_state['values']['expirepath_path_to_expire']));
  $url = parse_url($path);
  $path = implode("/", array_filter(explode("/", $url['path'])));

  // Expire url.
  $internal_paths = array();
  if ($path === 'FRONT') {
    $internal_paths += ExpireAPI::getFrontPageUrls();
    drupal_set_message(t('The front page has been purged.'));
  }
  else {
    $internal_paths[] = $path;
    drupal_set_message(t('Internal path: "%path" has been purged.', array('%path' => $path)));
  }

  // Expire internal paths.
  ExpireAPI::executeExpiration($internal_paths);
}
