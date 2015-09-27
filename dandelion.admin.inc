<?php

/**
 * @file
 * Admin pages
 *
 * @author Hein Bekker <hein@netbek.co.za>
 * @copyright (c) 2015 Hein Bekker
 * @license http://www.gnu.org/licenses/gpl-2.0.txt GPLv2
 */

/**
 * Settings form builder.
 */
function dandelion_admin_settings() {
  $form = array();

  /**
   * Front page.
   */
  $form['front_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Front page'),
  );

  $form['front_page']['dandelion_front_page_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => variable_get('dandelion_front_page_title'),
  );

  $body = variable_get('dandelion_front_page_body', array('value' => NULL));
  $form['front_page']['dandelion_front_page_body'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => $body['value'],
    '#format' => isset($body['format']) ? $body['format'] : NULL,
    '#required' => TRUE,
  );

  $footer = variable_get('dandelion_front_page_footer', array('value' => NULL));
  $form['front_page']['dandelion_front_page_footer'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Footer'),
    '#default_value' => $footer['value'],
    '#format' => isset($footer['format']) ? $footer['format'] : NULL,
  );

  $form['front_page']['dandelion_front_page_image'] = array(
    '#type' => 'media',
    '#tree' => TRUE,
    '#title' => t('Image'),
    '#description' => t('Allowed formats: JPG or PNG. Suggested size: @todo'),
    '#media_options' => array(
      'global' => array(
        'schemes' => array(
          'public' => 'public',
        ),
        'uri_scheme' => 'public',
        'file_extensions' => 'jpg jpeg png',
        'max_filesize' => '5 MB',
        'types' => array('image'),
        'enabledPlugins' => array(
          'upload',
          'media_default--media_browser_1',
        ),
      ),
    ),
    '#default_value' => variable_get('dandelion_front_page_image'),
  );

  return system_settings_form($form);
}
