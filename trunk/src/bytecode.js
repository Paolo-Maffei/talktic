pinMode(0, true);
pinMode(1, false);

while(true) {
	var s = digitalRead(1);
	print(s);
	digitalWrite(0, s);
	var f = analogRead(0);
	print(f);
	analogWrite(0, f);
}
