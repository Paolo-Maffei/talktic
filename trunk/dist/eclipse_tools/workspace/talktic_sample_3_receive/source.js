/**********************************************************
�����ʐM

 - �ʓr�Asample-03-s.js���������܂ꂽ�{�[�h��p�ӂ��邱��
**********************************************************/

// ����������
pinMode(0, true);				// PORT0�ɂ�LED��ڑ��iLOW�o�͂œ_���j
radioInit(0xDEAD, 0, 11, 31);

// ������M�C�x���g�n���h���̐ݒ�
function onRadioReceive(seq,src,pan,data,rss) {
	// ��M������LED��_��
	digitalWrite(0, false);
}

// ���C���ƂȂ郋�[�v
while(true) {
	digitalWrite(0, true);
}
