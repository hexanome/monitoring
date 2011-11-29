/* client.js: Include this in your index.html
 * Copyright © Hexanome H4101 INSA IF.
 */

function makeop(action) {
  Scout('#' + action).on('click', function(query) {
    query.action = action;
    query.resp = function(resp) { console.log(action + '-ed'); };
    query.error = function(err) { console.error(err); };
  });
}

addEventListener('load', function createactions() {
  ['stop', 'go', 'init'].forEach(function(act) {makeop(act);});
}, false);

