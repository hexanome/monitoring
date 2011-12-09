/* server.js: Run this with node to start your server.
 * Copyright © Hexanome H4101 INSA IF.
 */


// Sending messages.

function readmessage(buffer) {
  try {
    var type = buffer.readUInt8(0).toString(),
        size = +buffer.readUInt32BE(1, true),
        message = buffer.slice((8+32)/8, size).toString();
  } catch (e) {
    console.log('PROTOCOL: ERROR: buffer not read properly',
        'while reading message ' + buffer.inspect());
  }
  return {type:type, size:size, message:message};
}

// Reading messages.

function cca(c) { return c.charCodeAt(0); }

// `nbparts` is the number of part types.
function craftinit(nbparts) {
  var buf = new Buffer(1 + (32*nbparts.length / 8));
  buf[0] = cca('i');
  for (var i = 0; i < nbparts.length; i++) {
    buf.writeUInt32BE(nbparts[i], 1 + (32*i / 8));
  }
  return buf;
}

// Parameter `choice` must be either `"c"` (to continue) or `"s"` (to stop).
function craftanswer(choice) {
  var buf = new Buffer(2);
  buf[0] = cca('a');
  buf[1] = cca(choice);
  return buf;
}

// A command has the following parameters, per the spec:
//
//     numCommand:Number
//     nbPalette1:Number
//     nbPalette2:Number
function craftcommand(numcomm, nbpal1, nbpal2) {
  var buf = new Buffer((8+32+32+32)/8);
  buf[0] = cca('c');
  buf.writeUInt32BE(numcomm, 1);
  buf.writeUInt32BE(nbpal1, (8+32)/8);
  buf.writeUInt32BE(nbpal2, (8+32+32)/8);
  return buf;
}


// Exports are here.
//

exports.readmessage = readmessage;
exports.craftinit = craftinit;
exports.craftanswer = craftanswer;
exports.craftcommand = craftcommand;

