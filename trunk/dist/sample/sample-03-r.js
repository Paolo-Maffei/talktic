/**********************************************************
無線通信

 - 別途、sample-03-s.jsが書き込まれたボードを用意すること
**********************************************************/

// 初期化処理
pinMode(0, true);				// PORT0にはLEDを接続（LOW出力で点灯）
radioInit(0xDEAD, 0, 11, 31);

// 無線受信イベントハンドラの設定
function onRadioReceive(seq,src,pan,data,rss) {
	// 受信したらLEDを点灯
	digitalWrite(0, false);
}

// メインとなるループ
while(true) {
	digitalWrite(0, true);
}
