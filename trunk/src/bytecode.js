/*
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
var h = "global";

for(var i=0; i<1000; i++) {
	var x = new Hello("Hello World!\r\n");
	x.show();
}
*/
var h = 0;

while(true) {
	debug(".");
}
// interrupt?
function test() {
	var x = new Hello("interrupt!!\r\n");
	x.show();
	h++;
	debug(h);
	led();
}