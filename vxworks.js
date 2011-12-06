var net = require('net');

net.Server(function(socket) {
  socket.on('data',function(data){
    console.log(data+'');
  });

  setInterval(function() {
    var buf = new Buffer(10);
    socket.write();
  }, 5000);

}).listen(1337);// 5001 | 3737 

