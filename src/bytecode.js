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
/*
var h = 0;

function onr(seq,src,pan,pay,rss) {
	debug(pay);
	debug(h++);
}

if(dpi(2,false)) {
	debug("init port0 as out");
}
if(dpi(3,true)) {
	debug("init port1 as in");
}
var v = 0;
var i = 1;
var hz = 0;

while(true) {
	if(dpg(3)) {
		h++;
		hz += 10;
		snd(1, hz);
		debug("hz="+hz+"\r\n");
	}

	pwm(0, v);
	v += i;
	if(v>255 || v<0) {
		i = i * -1;
		v += i;
	}

	dps(2, (h % 2) == 0);
	if(srd) {
		srd(0xFFFF, "muchmorebigpacket");
	}
}
*/
var f = 3.1415926535897932384;
var i = 4;
f = f * i;
debug("f="+f+"\r\n");
while(1) {
}
