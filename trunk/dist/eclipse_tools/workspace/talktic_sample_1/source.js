/**********************************************************
ディジタル、アナログ入出力
**********************************************************/

// 変数の準備
var brightness = 0;			// LEDの明るさ
var isLighted = true;		// LEDを点灯するかどうか
var isPressed = false; 		// スイッチが押されているか？
var previousState = false;	// 前回確認した時のスイッチの状態

// 初期化処理
pinMode(0, true);			// PORT0にはLEDを接続（LOW出力で点灯）
pinMode(1, false);			// PORT1にはスイッチを接続（押下でLOW状態）
isPressed = !digitalRead(1);
previousState = isPressed;

// メインとなるループ
while(true) {
	// スイッチが押されたらLEDの点灯状態をトグルする
	isPressed = !digitalRead(1);
	if (isPressed == true && previousState == false){
		isLighted = !isLighted;
	}
	previousState = isPressed;

	// LEDを点灯するならPORT2のアナログ値に応じた明るさで点灯する
	if (isLighted){
		brightness = analogRead(2);
	}else{
		brightness = 0;
	}
	analogWrite(0, brightness);
}
