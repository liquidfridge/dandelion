<?php

/**
 * @file
 * DandelionBoost
 *
 * @author Hein Bekker <hein@netbek.co.za>
 * @copyright (c) 2015 Hein Bekker
 * @license http://www.gnu.org/licenses/gpl-2.0.txt GPLv2
 */
class DandelionBoost {

  /**
   *
   * @param array $urls
   */
  public static function expire($urls) {
    // Make URLs absolute.
    foreach ($urls as $index => $url) {
      $urls[$index] = url($url, array(
        'absolute' => TRUE,
        'alias' => TRUE,
      ));
    }

    boost_expire_cache($urls);
  }

  /**
   *
   */
  public static function expireAll() {
    $_boost = boost_transform_url();

    if (isset($_boost['base_dir'])) {
      $count = _boost_rmdir($_boost['base_dir'], TRUE);
    }
  }

  /**
   * Return urls for a front page.
   */
  public static function getFrontPageUrls() {
    $urls = array(
      'front' => '',
      'front-path' => variable_get('site_frontpage', 'node'),
    );
    return $urls;
  }

  /**
   *
   * @param array $link
   */
  public static function expireMenuLink($link) {
    if ($link['menu_name'] == 'main-menu') {
      self::expireAll();
    }
  }

  /**
   *
   * @param stdClass $node
   */
  public static function expireNode($node) {
    if (empty($node->nid) || empty($node->type)) {
      return;
    }

    $urls = array();

    if ($node->type == 'book') {
      $nids = db_select('node', 'n')
          ->fields('n', array('nid'))
          ->fields('n', array('type'))
          ->condition('n.type', 'book')
          ->execute()
          ->fetchCol();
      foreach ($nids as $nid) {
        $url = 'node/' . $nid;
        $urls[] = $url;
        $urls[] = drupal_get_path_alias($url);
      }
    }
    elseif ($node->type == 'page') {
      // Front page.
      $path = 'node/' . $node->nid;
      $alias = drupal_get_path_alias($path);

      if ($alias == 'front') {
        $urls = self::getFrontPageUrls();
      }
    }

    self::expire($urls);
  }

}
