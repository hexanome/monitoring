var net = require('net');

net.Server(function(socket) {
  socket.on('data',function(data){
    console.log(data+'');
  });

  setInterval(function() {
    var buf = new Buffer(10);
    buf[0] = 'i'; buf[1] = 0; buf[2] = 0; buf[3] = 0; buf[4] = 5;
    buf[5] = 'F'; buf[6] = 'F'; buf[7] = 'U'; buf[3] = 'U'; buf[4] = 'U';
    socket.write(buf);
  }, 5000);

}).listen(1337);

