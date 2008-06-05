/*********************************************************
�V���A�����o��
**********************************************************/

// �ϐ��̏���
var receivedValue = NaN;

// ����������
pinMode(0, true);			// PORT0�ɂ�LED��ڑ��iLOW�o�͂œ_���j
pinMode(1, false);			// PORT1�ɂ̓X�C�b�`��ڑ��i������LOW��ԁj
serialInit(9600);			// PROTO1�{�[�h��COM0��PC�֐ڑ����邱��
serialSend("Input a decimal number from 0 to 1.\r\n");

// �V���A����M�C�x���g�n���h���̐ݒ�
function onSerialReceive(success) {
	// ���͒l���������͈͂ł���΁A�l��LED�̋P�x�ɔ��f����
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

// ���C���ƂȂ郋�[�v
while(true) {}