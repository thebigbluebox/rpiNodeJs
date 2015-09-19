var gpio = require("pi-gpio");

 var intervalId;
 var durationId;
 var gpioPin = 16;


var express = require('express');
var app = express();
app.use('/', function(req, res) {
res.send('Hello World');
  gpio.open(gpioPin, "output", function(err) {
var on = 1;
console.log('GPIO pin '+gpioPin+' is open. toggling LED every 100 mS for 10s');

intervalId = setInterval( function(){
  gpio.write(gpioPin, on, function() { // toggle pin between high (1) and low (0)
    on = (on + 1) % 2;
    });
  }, 100);
});

durationId= setTimeout( function(){
  clearInterval(intervalId);
  clearTimeout(durationId);
  console.log('10 seconds blinking completed');
  gpio.write(gpioPin, 0, function() { // turn off pin 16
    gpio.close(gpioPin); // then Close pin 1
  });
},10000); // duration in mS

});
app.listen(3000);
console.log('Server running at http://localhost:3000/');
module.exports = app;




