/* server.js: Run this with node to start your server.
 * Copyright © Hexanome H4101 INSA IF.
 */


function readmessage(buffer) {
  return {
    type: buffer.readUInt8(0).toString(),
    size: +buffer.readInt32(1, true),
    message: buffer.slice((8+32)/8, size).toString()
  };
}


// Exports are here.

exports.readmessage = readmessage;

