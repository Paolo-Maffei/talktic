/*********************************************************
シリアル入出力
**********************************************************/

// 変数の準備
var receivedValue = NaN;

// 初期化処理
pinMode(0, true);			// PORT0にはLEDを接続（LOW出力で点灯）
pinMode(1, false);			// PORT1にはスイッチを接続（押下でLOW状態）
serialInit(9600);			// PROTO1ボードのCOM0をPCへ接続すること
serialSend("Input a decimal number from 0 to 1.\r\n");

// シリアル受信イベントハンドラの設定
function onSerialReceive(success) {
	// 入力値が正しい範囲であれば、値をLEDの輝度に反映する
	receivedValue = parseFloat(serialRead());
	if (isNaN(receivedValue)){
		serialSend("Error: Input value is Not a Number.\r\n");
	}else if(receivedValue < 0 || receivedValue > 1){
		serialSend("Error: Input value is out of range.\r\n");	
	}else{
		serialSend("OK: Brightness is set to " + receivedValue + "\r\n");
		analogWrite(0, receivedValue);
	}
}

// メインとなるループ
while(true) {}