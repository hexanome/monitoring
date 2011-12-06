/* server.js: Run this with node to start your server.
 * Copyright © Hexanome H4101 INSA IF.
 */


// Sending messages.

function readmessage(buffer) {
  var type = buffer.readUInt8(0).toString(),
      size = +buffer.readUInt32BE(1, true),
      message = buffer.slice((8+32)/8, size).toString();
  return {type:type, size:size, message:message};
}

// Reading messages.

function cca(c) {
  return c.charCodeAt(0);
}

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

// Commands must be a list of objects of the form
//
//     numCommand:Number
//     part_type:String (of one char)
//     part_number:Number
//
// `send` :: function (buffer) { do something with it }
function craftcommand(commands, send) {
  var len = commands.length;
  for (var i = 0; len > i; i++) {
    var buf = new Buffer((8+32+8+32+16)/8);
    buf[0] = cca('c');
    buf.writeUInt32BE(commands[i].numCommand, 1);
    buf[(8+32)/8] = cca(commands[i].part_type);
    buf.writeUInt32BE(commands[i].part_number, (8+32+8)/8);
    buf.writeUInt16BE(len, (8+32+8+32)/8);
    send(buf);
  }
}


// Exports are here.
//

exports.readmessage = readmessage;
exports.craftinit = craftinit;
exports.craftanswer = craftanswer;
exports.craftcommand = craftcommand;

