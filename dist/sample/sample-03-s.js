/**********************************************************
�����ʐM

 - �ʓr�Asample-03-r.js���������܂ꂽ�{�[�h��p�ӂ��邱��
**********************************************************/

// �ϐ��̏���
var previousState = false;
var isPressed = false;

// ����������
pinMode(0, true);				// PORT0�ɂ�LED��ڑ��iLOW�o�͂œ_���j
pinMode(1, false);				// PORT1�ɂ̓X�C�b�`��ڑ��i������LOW��ԁj
radioInit(0xDEAD, 1, 11, 31);

// ���C���ƂȂ郋�[�v
while(true) {

	// �X�C�b�`��������Ă�����A���M�o�͂�ύX���ăf�[�^�𑗐M����
	// ����������΁ALED��_������B
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
