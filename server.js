/* server.js: Run this with node to start your server.
 * Copyright © Hexanome H4101 INSA IF.
 */

// Import modules
var net = require ('net'),
    camp = require ('./camp/camp'),
    protocol = require ('./protocol');


// Connect to remote monitoring system
var socket = new net.Socket();

// What to do when connected
socket.on('connect', function() {

  console.log('socket connected');

  // Listen to incoming data
  socket.on('data', function(data) {
    var message = protocol.readmessage(data);
    console.log('DATA: %s%s',
      message.type === 'e'? '[error] ': '', message.message);
    camp.Server.emit('gotlog', message);
  });

  // All camp actions are defined here.

  camp.add('log', function() {}, function gotlog(log) {return log;});

  camp.add('init', function(data) {
    console.log('INIT nbpart1:' + data.nbpart1, 'nbpart2:' + data.nbpart2);
    var nbpart1 = data.nbpart1 || 20,
        nbpart2 = data.nbpart2 || 20;
    socket.write(protocol.craftinit([nbpart1, nbpart2]));
  });

  camp.add('stop', function(data) {
    console.log('STOP');
    socket.write(protocol.craftanswer('s'));
  });

  camp.add('go', function(data) {
    console.log('GO');
    socket.write(protocol.craftanswer('c'));
  });

  camp.add('comm', function(data) {
    console.log('COMM');
    socket.write(protocol.craftcommand(data.nbpart1, data.nbpart2));
  });
});

// Connect to remote system
socket.connect(1337);

// Web server options
var options = {
  port: +process.argv[2],
  secure: process.argv[3],
  debug: +process.argv[4]
}

// Start web server
camp.start(options);

