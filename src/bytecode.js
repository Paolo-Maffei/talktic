// class methods
function put() {
	debug(this.val+"\r\n");
}

// class definition
function PrintString(val) {
  this.val = val;
  this.put = put;
}

// extend PrintString
function PrintHoge() {
  this.val = "hoge";
}
PrintHoge.prototype = new PrintString;

var a = new PrintHoge();
var arr = new Array();
for(var i=0; i<20; i++) {
	a.put();
	arr.push(20-i);
}
for(var i=0; i<arr.length; i++) {
    debug(arr[i]);
}

var f = 3.1415
debug(f);
debug(f*10);

for(var i=0; i<100; i++) {
var x = new Hello("Hello World!");
debug(x.msg);
x.show();
}
