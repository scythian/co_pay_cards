<?php

/**
 * @file
 * Code for the Co Pay Cards module.
 */


/**
 * Parse Widget Body.
 *
 * @param string $file_name
 *   JS file name, containing integer Client ID.
 *   For example clientID.js
 *
 * @return string
 *   JavaScript Source.
 */
function co_pay_cards_widget($file_name = '') {
  header('content-type: application/javascript');

  // Client ID.
  $clinent_id = NULL;
  // Error messages.
  $error_message = NULL;
  // Output JavaScript body.
  $js_source = '';

  // Check for correct JS filename, containing integer Client ID and grab it.
  if (preg_match('/(^[0-9]+)\.js$/u', $file_name, $matches)) {
    $clinent_id = $matches[1];

    // Check that Client ID exist in DB.
    if (!co_pay_cards_check_client_id($clinent_id)) {
      $error_message = t('Unknown Client ID.');
    }
  }
  else {
    $error_message = t('Wrong request');
  }

  // If errors was found,
  if (!empty($error_message)) {
    // Here can be some custom initial errors code.
    $base_js_file = 'co_pay_cards_error.js';
  }
  else {
    // Base widget code.
    $base_js_file = 'co_pay_cards.js';
  }

  $js_source .= file_get_contents(drupal_get_path('module', 'co_pay_cards') . '/misc/' . $base_js_file);
  $search = array(
    '#clientID',
    '#errorMessage',
    '#baseHost',
  );
  $replace = array(
    $clinent_id,
    $error_message,
    $_SERVER['HTTP_HOST'],
  );
  $js_source = str_replace($search, $replace, $js_source);

  echo $js_source;
  exit();
}

/**
 * Return required libraries pack.
 *
 * @param string $type
 *   Libraries type (js/css).
 *
 * @return string
 *   JavaScript Source.
 */
function co_pay_cards_libraries($type) {
  switch ($type) {
    case 'js':
      header('content-type: application/javascript');
      $js_source = '';

      $libraries_cache = cache_get('co_pay_cards:js_libraries');
      // If cache does not exist, load needed libraries.
      if (!isset($libraries_cache->data)) {
        $libraries_list = array(
          '/misc/jquery.js',
          '/misc/ui/jquery.ui.core.min.js',
          '/misc/ui/jquery.ui.widget.min.js',
          '/misc/ui/jquery.ui.button.min.js',
          '/misc/ui/jquery.ui.mouse.min.js',
          '/misc/ui/jquery.ui.position.min.js',
          '/misc/ui/jquery.ui.resizable.min.js',
          '/misc/ui/jquery.ui.dialog.min.js',
        );

        foreach ($libraries_list as $key => $file) {
          $js_source .= file_get_contents(DRUPAL_ROOT . $file);
        }

        // Set js libraries pack to cache.
        cache_set('co_pay_cards:js_libraries',
          $js_source,
          'cache',
          variable_get('co_pay_cards_data_ttl', 604800)
        );
      }
      else {
        // Read libraries pack from cache.
        $js_source = $libraries_cache->data;
      }

      echo $js_source;
      break;

    case 'css':
      header('Content-type: text/css');
      $css_source = '';

      $libraries_cache = cache_get('co_pay_cards:css_libraries');
      // If cache does not exist, load needed libraries.
      if (!isset($libraries_cache->data)) {
        $libraries_list = array(
          '/misc/ui/jquery.ui.core.css',
          '/misc/ui/jquery.ui.dialog.css',
        );

        foreach ($libraries_list as $key => $file) {
          $css_source .= file_get_contents(DRUPAL_ROOT . $file);
        }

        // Set css libraries pack to cache.
        cache_set('co_pay_cards:css_libraries',
          $css_source,
          'cache',
          variable_get('co_pay_cards_data_ttl', 604800)
        );
      }
      else {
        // Read libraries pack from cache.
        $css_source = $libraries_cache->data;
      }

      echo $css_source;
      break;
  }

  exit();
}

/**
 * Check, that Client ID exist in database.
 *
 * @param int $client_id
 *   Client ID.
 *
 * @return bool
 *   FALSE, if does not exist.
 */
function co_pay_cards_check_client_id($client_id) {
  // Here must be some query to the database.

  return TRUE;
}
