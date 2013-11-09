<?php

/**
 * @file 
 * this file contains forms and all necessary code for module admin pages
 */

/**
 * Form Builder to configure the module.
 *
 * @return associative array, with the structure of the form
 */
function toa_b2c_settings() {

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('This page allows you to set the parameters required to use the search Travel Open Apps'),
  );

  $form['toa_b2c_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Add user'),
    '#default_value' => variable_get('toa_b2c_user'),
    '#description' => t('Enter the user name for TOA.'),
    '#size' => 30,
  );
  $form['toa_b2c_password'] = array(
    '#type' => 'password',
    '#title' => t('Add password'),
    '#description' => t('Enter password for TOA'),
    '#size' => 30,
  );
  $form['toa_b2c_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Add url'),
    '#default_value' => variable_get('toa_b2c_url'),
    '#description' => t('Enter the url Searcher, e.g.: http://reservas.emergya.es/searcher.htt'),
    '#size' => 50,
  );
  $form['toa_b2c_home_agencie'] = array(
    '#type' => 'textfield',
    '#title' => t('Home agencia'),
    '#default_value' => variable_get('toa_b2c_home_agencie'),
    '#description' => t('The agencies Home page. e.g.: white-emergya'),
    '#size' => 50,
  );
  $form['toa_b2c_domain_magnolia'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain Magnolia'),
    '#default_value' => variable_get('toa_b2c_domain_magnolia'),
    '#description' => t('Domain Magnolia your account, e.g.: http://cmsmagnolia.hotetec.com'),
    '#size' => 50,
  );
  $form['toa_b2c_jquery_version'] = array(
    '#type' => 'select',
    '#title' => t('jQuery version'),
    '#default_value' => variable_get('toa_b2c_jquery_version', '1.8.3'),
    '#options' => array(
      '1.8.3' => '1.8.3',
      '1.9.1' => '1.9.1',
      '1.10.1' => '1.10.1',
    ),
    '#description' => t('jQuery version using TOA, default is 1.8.3'),
  );
  $form['toa_b2c_jqueryui_version'] = array(
    '#type' => 'select',
    '#title' => t('jQuery ui version'),
    '#default_value' => variable_get('toa_b2c_jqueryui_version', '1.9.2'),
    '#options' => array(
      '1.9.2' => '1.9.2',
      '1.10.1' => '1.10.1',
    ),
    '#description' => t('jQuery ui version using TOA, default is 1.9.2'),
  );
  // Set a submit handler manually because the default submit handler
  // gets overridden by the system_settings_form() submit handler.
  $form['#submit'][] = 'toa_b2c_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for the custom form.
 */
function toa_b2c_settings_submit($form, &$form_state) {
  if ($form_state['values']['toa_b2c_password'] == '') {
    $form_state['values']['toa_b2c_password'] = variable_get('toa_b2c_password', 'ww');
  }
}

/**
 * Returns the HTML iframe with forms of administration.
 * @param associative array $variables, containing: 
 *  - "url" : string, Url to be carried by the iframe
 *  - "login" : bolean, 
 * @return string
 */
function theme_toa_b2c_admin_page($variables) {
  $path_module = drupal_get_path('module', 'toa_b2c');
  $login = '<iframe id="magnolialogin" src="' . $GLOBALS['base_url'] . '/?q=admin/toa_b2c/menu/iframe" width="100" height="100" style="display:none;"></iframe>';

  $magnoliaframe = '<iframe id="magnoliaframe" src="' . $variables['url'] . '&mgnlCK=' . time() . '" name="' . time() .
      '" width="1024" height="540" scrolling="auto" frameborder="1">'
      . '<p>' . t("Your browser does not support iframe.") . '</p></iframe>';

  drupal_add_js('
  (function($) {
        $(document).ready(function() {
         $("#magnoliaframe").load();
        })
      })(jQuery);', 'inline'
  );

  $admin_iframe = '<center style="background: url(' . $path_module . '/loader.gif) no-repeat fixed center">'
      . '<div>' . $magnoliaframe . '</div>'
      . '</center>';

  return ($variables['login']) ? $login . $admin_iframe : $admin_iframe;
}

/**
 * Callback function for the menu admin/toa_b2c/menu/...
 * @param string $arg
 * @return associative array
 */
function _menu_toa_b2c_page($arg = '') {
  $agencie = variable_get('toa_b2c_home_agencie');
  $magnolia = variable_get('toa_b2c_domain_magnolia', 'http://cmsmagnolia.hotetec.com');

  $url_forms = array(
    'my_data' => $magnolia . '/author/hTtSites-' . $agencie . '/.magnolia/trees/webdata.html?pathSelected=/webdata/'
    . $agencie . '&pathOpen=/webdata/' . $agencie . '&path=/webdata/' . $agencie,
    'my_pages' => $magnolia . '/author/hTtSites-' . $agencie . '/.magnolia/trees/website.html?parm=/',
    'booking_engine' => $magnolia . '/author/.magnolia/dialogs/pages/hTt/homeBookingEngineConfig.html?mgnlPath=/'
    . $agencie . '&mgnlParagraph=hTt-template-generic:pages/hTt/homeBookingEngineConfig&mgnlRepository=website&mgnlLocale=es&mgnlRichE=false&mgnlRichEPaste=',
    'booking_engine_hotel' => $magnolia . '/author/.magnolia/dialogs/pages/hTt/homeBookingEngineConfigHotel.html?mgnlPath=/'
    . $agencie . '&mgnlParagraph=hTt-template-generic:pages/hTt/homeBookingEngineConfigHotel&mgnlRepository=website&mgnlLocale=es&mgnlRichE=false&mgnlRichEPaste=',
    'properties' => $magnolia . '/author/.magnolia/dialogs/whiteHomeProperties.html?mgnlPath=/'
    . $agencie . '&mgnlParagraph=hTt-template-white:whiteHomeProperties&mgnlRepository=website&mgnlLocale=es&mgnlRichE=true&mgnlRichEPaste=textarea',
    'admincentral' => $magnolia . '/author/.magnolia/pages/adminCentral.html',
    'google_analytics' => $magnolia . '/author/.magnolia/dialogs/custom/hTtAnalyticsEdit.html?mgnlPath=/'
    . $agencie . '&mgnlParagraph=hTt-generic-controls:custom/hTtAnalyticsEdit&mgnlRepository=website&mgnlLocale=es&mgnlRichE=true&mgnlRichEPaste=textarea',
  );
  $login = ($arg == 'my_data') ? TRUE : FALSE;

  return theme('toa_b2c_admin_page', array('url' => $url_forms[$arg], 'login' => $login));
}

/**
 * Login in Magnolia.
 *
 * @return string
 */
function toa_b2c_login_magnolia() {
  $user = variable_get('toa_b2c_user');
  $password = variable_get('toa_b2c_password');
  $agencia = variable_get('toa_b2c_home_agencie');
  $magnolia = variable_get('toa_b2c_domain_magnolia');
  $login_magnolia = $magnolia . '/author/' . $agencia . '.html';

  $form = '<form id="loginForm" method="post" action="' . $login_magnolia . '">
        <input id="username" name="mgnlUserId" type="hidden" value="' . $password . '">
        <input id="mgnlUserPSWD" type="password" name="mgnlUserPSWD" type="hidden" value="' . $user . '">
        <input id="submitButton" class="button" type="submit" value="login">
        </form>';
  $form .= '<script type="text/javascript">document.getElementById(\'loginForm\').submit();</script>';

  echo $form;
}
