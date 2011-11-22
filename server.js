/* server.js: run this with Node.js in the publish/ folder to start your server.
 * Copyright © 2011 Jan Keromnes, Thaddee Tyl. All rights reserved.
 * Code covered by the LGPL license. */


// Import the Camp
var camp = require ('./camp/camp.js');

// Options
var options = {
  port: +process.argv[2],
  secure: process.argv[3],
  debug: +process.argv[4]
}

// Let's rock'n'roll!
camp.start(options);
