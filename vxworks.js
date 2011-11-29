var net = require('net');

net.Server(function(socket) {
  socket.on('data',function(data){
    console.log(data+'');
  });
}).listen(1337);
