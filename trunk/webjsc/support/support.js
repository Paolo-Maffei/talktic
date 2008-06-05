Number.prototype.zsHex = function(len) {
	if(len == undefined) {
		len = 0;
	}
	var h = this.toString(16).toUpperCase();
	var zs = '';
	for(var i=0; i<len - h.length; i++) {
		zs += '0'
	}
	return zs + h;
}

String.prototype.intelHex = function() {
	var h = "";
	for(var i=0; i<this.length && i < 0xFFFF; i+= 16) {
		var s = 0;
		var l = Math.min(this.length - i, 16);
		h += ':' + l.zsHex(2) + i.zsHex(4) + '00';
		s += l;
		s += ((i >> 8) & 0xFF);
		s += i & 0xFF;
		for(var j=0; j<l; j++) {
			var code = this.charCodeAt(i+j);
			h += code.zsHex(2);
			s += code;
		}
		var cs = (0x100 - (s & 0xFF)) & 0xFF;
//		h += (cs+s).zsHex(2);
		h += cs.zsHex(2) + "\n";
	}
	h += ':00000001FF';
	return h;
}
String.prototype.append = function(a) {
	if(typeof a == 'string') {
		return this + a;
	} else if(typeof a == 'number') {
		return this + String.fromCharCode(a);
	}
}
String.pack = function(s) {
	var r = "";
	var j = 1;
	for(var i=0; i<s.length; i++) {
		switch(s.charAt(i)) {
		case 'C':
			r += String.fromCharCode(arguments[j++] & 0xff);
			break;
		case 'N':
			var v = arguments[j++];
			r += String.fromCharCode(v >> 24 & 0xff);
			r += String.fromCharCode(v >> 16 & 0xff);
			r += String.fromCharCode(v >> 8 & 0xff);
			r += String.fromCharCode(v & 0xff);
			break;
		case 'n':
			var v = arguments[j++];
			r += String.fromCharCode(v >> 8 & 0xff);
			r += String.fromCharCode(v & 0xff);
			break;
		case 'd':
			var bp = new BinaryParser(false, false);
			r += bp.fromFloat(arguments[j++]);
			break;
		}
	}
	return r;
}

function isInt(a) {
	return a == Math.floor(a);
}
function isFloat(a) {
	return a != Math.floor(a);
}
