/* client.js: Include this in your index.html
 * Copyright © Hexanome H4101 INSA IF.
 */

(function () {


// This is something of a main function.

addEventListener('load', function createactions() {
  ['stop', 'go', 'init'].forEach(function(act) {makeop(act);});
  log = Scout('#log');
  logger();
}, false);


// You can send three actions:
//
// - stop
// - go
// - init

function makeop(action) {
  Scout('#' + action).on('click', function(q) {
    q.action = action;
    q.method = 'GET';
    q.resp = function(resp) { console.log(action + '-ed'); };
    q.error = function(err) { console.error(err); };
  });
}

// You receive logs the usual way.

var log;

function htmlescape(msg) {
  return msg.replace('&', '&amp;').replace('>', '&gt;').replace('<', '&lt;');
}

function writelog(msg, iserror) {
  log.innerHTML += '<p' + (iserror? ' class="red"':'') + '>'
    + htmlescape(msg) + '</p>';
}

var logger = Scout.send(function(q) {
  q.action = 'log';
  q.resp = function(resp) {
    writelog(resp.message, resp.type === 'e');
    logger();
  };
  q.error = function(err) { console.error(err); setTimeout(logger, 1000); };
});


})();

