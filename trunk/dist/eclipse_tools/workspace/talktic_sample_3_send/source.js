/**********************************************************
無線通信

 - 別途、sample-03-r.jsが書き込まれたボードを用意すること
**********************************************************/

// 変数の準備
var previousState = false;
var isPressed = false;

// 初期化処理
pinMode(0, true);				// PORT0にはLEDを接続（LOW出力で点灯）
pinMode(1, false);				// PORT1にはスイッチを接続（押下でLOW状態）
radioInit(0xDEAD, 1, 11, 31);

// メインとなるループ
while(true) {

	// スイッチが押されていたら、送信出力を変更してデータを送信する
	// 応答があれば、LEDを点灯する。
	isPressed = !digitalRead(1);
	if (isPressed){
		transmissionPower = Math.ceil(31 * analogRead(2));
		radioInit(0xDEAD, 1, 11, transmissionPower);
		var result = radioSend(0xFFFF, "test");
		digitalWrite(0, !result);
	}else{
		digitalWrite(0, true);
	}
}
