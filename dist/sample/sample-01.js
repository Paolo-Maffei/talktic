/**********************************************************
�f�B�W�^���A�A�i���O���o��
**********************************************************/

// �ϐ��̏���
var brightness = 0;			// LED�̖��邳
var isLighted = true;		// LED��_�����邩�ǂ���
var isPressed = false; 		// �X�C�b�`��������Ă��邩�H
var previousState = false;	// �O��m�F�������̃X�C�b�`�̏��

// ����������
pinMode(0, true);			// PORT0�ɂ�LED��ڑ��iLOW�o�͂œ_���j
pinMode(1, false);			// PORT1�ɂ̓X�C�b�`��ڑ��i������LOW��ԁj
isPressed = !digitalRead(1);
previousState = isPressed;

// ���C���ƂȂ郋�[�v
while(true) {
	// �X�C�b�`�������ꂽ��LED�̓_����Ԃ��g�O������
	isPressed = !digitalRead(1);
	if (isPressed == true && previousState == false){
		isLighted = !isLighted;
	}
	previousState = isPressed;

	// LED��_������Ȃ�PORT2�̃A�i���O�l�ɉ��������邳�œ_������
	if (isLighted){
		brightness = analogRead(2);
	}else{
		brightness = 0;
	}
	analogWrite(0, brightness);
}
