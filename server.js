/* server.js: Run this with node to start your server.
 * Copyright (c) Hexanome H4101 INSA IF.
 */

// Import modules
var net = require ('net'),
    camp = require ('./camp/camp');


// Connect to remote monitoring system
var socket = new net.Socket();

// What to do when connected
socket.on('connect', function() {

  // Listen to incoming data
  socket.on('data', function(data) {
    // TODO notify the client
    console.log('received ' + data);
  });

  camp.add('init', function(data) {
    var msg = 'init message'; // TODO
    socket.write(msg);
  });

  camp.add('stop', function(data) {
    var msg = 'stop message'; // TODO
    socket.write(msg);
  });

  camp.add('continue', function(data) {
    var msg = 'continue message'; // TODO
    socket.write(msg);
  });

});

// Connect to remote system
socket.connect(1337); // TODO

// Web server options
var options = {
  port: 80,
  secure: 'no',
  debug: 10
}

// Start web server
camp.start(options);
