/**
 * @file
 * This file conteins the necessary javascript for TOA search block.
 */

(function($jqnc) {
  var funcionCallback = function(data) {
    $jqnc('#searcher').whiteSearcher(data);
  };
  var loadSearcher = function() {
    var url = Drupal.settings.toa_b2c.toa_b2c_url;
    var params = {
      callback: function(data) {
        funcionCallback(data);
      },
      callbackParamName: "searcherCallback",
      params: {}
    };
    $jqnc.jsonp.call(url, params);
  };
  Drupal.behaviors.toa_b2c = {
    attach: function()
    {
      loadSearcher();
    }
  };
})(jQuery.noConflict());
