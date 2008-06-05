print((function(){
	return function(a) {
		return a;
	}
})()(1));
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

/*
var f = 3.1415926535897932384;
var i = 4;
f = f * i;
debug("f="+f+"\r\n");
while(1) {
}
*/

/*
var hogehoge = 1;
while(hogehoge < 2000) {
	hogehoge++;
	print(hogehoge);
}
// 1  2   3  4   5  6    7     8  9   10 11  12
// ド ド# レ レ# ミ ファ ファ# ソ ソ# ラ ラ# シ
var m = [0, 440, 466.2, 493.9, 523.3, 554.4, 587.3, 622.3, 659.3, 698.5, 740.0, 784.0, 830.6];
var k = [1,1,1,3,5,5,1,5,5,1,5,5,5,3,3,3,5,6,0,6,5,3,6,6,6];
var l = [];
for(var i=0; i<k.length; i++) {
	debug(m[k[i]]+"\r\n");
	snd(0, m[k[i]]);
	for(var j=0; j<300; j++){}
}
snd(0,0);
while(true) {
}
*/

/*
while(true) {
	var f = adc(0);
	snd(0, f * 1000);
	pwm(1, f);
	debug("f="+f+"\r\n");
}
*/

/*
for(var i=0; i<100; i++) {
	print(int(Math.random()*10000));
}
*/

/*
try {
	print("go...");
	try{
	exit(999);
		throw(123.4);
	} catch(e) {
		print("error2=", e);
	}
	print("rescue");
} catch(e) {
	print("error=", e);
}
print("rescue");
hogehoge();
print("norescue");
*/

/*
print((1073741823).toString(2));
print((2147483647).toString(2));
print((4294967295).toString(2));
print((-1).toString(2));
*/
