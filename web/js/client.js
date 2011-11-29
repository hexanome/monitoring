/* client.js: Include this in your index.html
 * Copyright © Hexanome H4101 INSA IF.
 */

function makeexec(action) {
  Scout('#' + action).on(action, function(query) {
    query.action = action;
    query.resp = function(resp) {
      console.log(action + '-ed');
    };
    query.error = function(err) {
      console.error(err.message);
    };
  });
}

addEventListener('load', function() {
  makeexec('stop');
  makeexec('go');
  makeexec('order');
}, false);

