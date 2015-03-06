/**
 * @file
 * Base widget code for the Co Pay Cards module.
 */

(function() {

  var $baseJQuery = false
    , clientID = '#clientID'
    , baseHost = '//#baseHost'
    , jsLibrariesPack = baseHost + '/co-pay-cards/libraries/js'
    , cssLibrariesPack = baseHost + '/co-pay-cards/libraries/css'
    , popupDialogID = 'co-pay-card-dialog'
    , $popupDialog = false
    , iframeURL = '//blinkreaction.com'
    , iframeWidth = 400
    , iframeHeight = 400;


  // Check, that client site is using own jQuery version.
  if (typeof jQuery !== 'undefined') {
    $baseJQuery = jQuery.noConflict();
  }

  // Get needed CSS libraries.
  loadFile(cssLibrariesPack, 'css');

  // Get needed JS libraries.
  loadFile(jsLibrariesPack, 'js', function() {
    initialize();
  });

  /**
   * Initialize widget dialog.
   */
  function initialize() {
    $popupDialog = $('<div id="' + popupDialogID + '" style="display:none;"></div>');
    $('body').append($popupDialog);
    $('#' + popupDialogID).append('<iframe src="' + iframeURL + '" width="' + iframeWidth + '" height="' + iframeHeight + '"></iframe>');
    $("#" + popupDialogID).dialog();
    console.log('Widget jQuery version' + $.fn.jquery);
  }

  /**
   * Load external JS or CSS library.
   *
   * @param string url
   *   Url to the library.
   * @param string type
   *   Library type (js/css).
   * @param function success
   *   Callback function.
   */
  function loadFile(url, type, success) {
    var head = document.getElementsByTagName('head')[0]
      , done = false
      , success = success || function() {};

    switch (type) {
      case 'js':
        var js = document.createElement('script');
        js.src = url;
        // Attach handlers for all browsers
        js.onload = js.onreadystatechange = function() {
          if (!done && (!this.readyState || this.readyState == 'loaded' || this.readyState == 'complete')) {
            done = true;
            // callback function provided as param
            success();
            js.onload = js.onreadystatechange = null;
            head.removeChild(js);
          }
        };
        head.appendChild(js);
        break;

      case 'css':
        var css = document.createElement("link");
        css.setAttribute("rel", "stylesheet");
        css.setAttribute("type", "text/css");
        css.setAttribute("href", url);
        head.appendChild(css);
        break;
    }
  };

  // Restore base jQuery alias.
  if ($baseJQuery !== false) {
    $ = jQuery = $baseJQuery;
  }
})();



