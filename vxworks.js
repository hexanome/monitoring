var net = require('net');

net.Server(function(socket) {
  socket.on('data',function(data){
    console.log(data+'');
  });

  setInterval(function() {
    var buf = new Buffer(10);
    buf.writeUInt8('i'.charCodeAt(0),0);
    buf.writeUInt32BE(5,1);
    buf.write('FFUUU',5,5);
    console.log(buf);
    socket.write(buf);
  }, 5000);

}).listen(1337);

