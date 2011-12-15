var net = require('net');

// Contains information about palette numbers.
var nbpal1 = 20,
    nbpal2 = 20,
    msgfreq = 5000;  // interval of messages in millisecs.

net.Server(function(socket) {
  socket.on('data', function(buf){
    // Read the first letter, behave accordingly.
    var action = buf[0];
    if (action === cca('i')) {
      // Init: set the number of palette of each type.
      console.log(buf);
      nbpal1 = buf.readUInt32BE(1);
      nbpal2 = buf.readUInt32BE((8+32)/8);
      console.log('INIT:', nbpal1, nbpal2);
    } else if (action === cca('a')) {
      // Answer
      var command = buf[1];
      if (command === cca('c') && !msgon) {
        // Continue
        msgon = true;
        sendmessages();
      } else if (command === cca('s') && msgon) {
        // Stop
        msgon = false;
      }
    } else if (action === cca('c')) {
      // Command
      var pal1 = buf.readUInt32BE(1),
          pal2 = buf.readUInt32BE((8+32)/8);
      console.log('COMMAND:', pal1, pal2);
      socket.write(craftcommack(pal1, pal2));
    }
  });

  // Every 5 secs, we send a message.
  var msgon = true;
  function sendmessages() {
    setTimeout(function() {
      if (msgon) {
        socket.write(craftmessage());
        sendmessages();
      }
    }, msgfreq);
  }
  sendmessages();

}).listen(1337);


console.log('SIM started on port 1337');


// Protocol primitives.
//
// We don't put these in protocol.js because this simulator should really be
// code-independant from the real thing.

function cca(c) { return c.charCodeAt(0); }

// craftmessage creates the buffer for the message the simulator sends through
// the socket.
function craftmessage() {
  // We show the data about the number of palette 1 and 2 for
  // debugging purposes (both of init and of message transmission).
  var pal1 = '' + nbpal1,
      pal2 = '' + nbpal2,
      intro1 = 'Number of palette of type 1: ',
      intro2 = '. Number of palette of type 2: ',
      msgsize = intro1.length + pal1.length + intro2.length + pal2.length,
      buf = new Buffer((8+32+8*(msgsize)) / 8);
  buf.writeUInt8(cca('i'), 0);      // First, the character 'i'.
  buf.writeUInt32BE(msgsize, 1);    // The size of the message.
  buf.write(intro1 + pal1 + intro2 + pal2, (8+32)/8);  // The message.
  return buf;
}

function craftcommack(pal1, pal2) {
  var pal1 = '' + pal1,
      pal2 = '' + pal2,
      intro1 = 'Command with ',
      intro2 = ' palettes of type 1 and ',
      intro3 = ' palettes of type 2',
      msgsize = intro1.length + pal1.length +
        intro2.length + pal2.length + intro3.length,
      buf = new Buffer((8+32+8*(msgsize)) / 8);
  buf.writeUInt8(cca('i'), 0);      // First, the character 'i'.
  buf.writeUInt32BE(msgsize, 1);    // The size of the message.
  buf.write(intro1 + pal1 + intro2 + pal2 + intro3, (8+32)/8);  // The message.
  return buf;
}

