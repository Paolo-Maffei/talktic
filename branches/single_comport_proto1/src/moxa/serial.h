/*!
  @file
  @brief �f�o�b�O�p�V���A���ʐM�̏����֐���`

  �V���A���|�[�g�̓��o�͂��s�Ȃ��֐�����`���Ă���܂��B
  ���������ɂ́A�V���A���|�[�g�ԍ��ƃ{�[���[�g���w�肵�Ă��������B
  ��������ɃV���A�����o�͊֐����g�p����ۂɂ��V���A���|�[�g�ԍ����w�肵�Ă��������B
  �Ⴆ�΁A�V���A���|�[�g�O�Ԃ�9600bps�ŏ��������āA���͂���������啶���ɕϊ����ďo�͂���
  �v���O�����͈ȉ��̂悤�ȃR�[�h�ɂȂ�܂��B

  char ch;

  SERIAL_init(0, 9600);

  while (1) {
      ch = SERIAL_getchar(0);
      if (ch >= 'a' && ch <= 'z') {
          SERIAL_putchar(0, ch - 'a' + 'A');
      } else {
          SERIAL_putchar(0, ch);
      }
  }

  ���������Ƃ��āASERIAL_scanf�֐��͎g�p�ł��܂���B
  SERIAL_printf�֐���moxa_config.h�ɒ�`���Ă���SERIAL_VARARG_SIZE�̒����𒴂��āA
  ��x�ɏo�͂��邱�Ƃ͂ł��܂���B
  �܂��ASERIAL_sprintf, SERIAL_sscanf�֐��ɂ̓V���A���|�[�g���w�肷��K�v�͂���܂���B
  
  @author Shinji Yamachika
  @date   2005/11/28
  @version 0.1
*/

#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "moxa_config.h"
#include "mega128_macro.h"

#include <stdio.h>

//#pragma used+

/*!
  �f�o�b�O�p�̃V���A���|�[�g�����������܂��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @param nBaudrate    �{�[���[�g���w��
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �����Ƃ��Ďw�肵���|�[�g�ԍ��ɊԈႢ������
*/
MRESULT SERIAL_init(UINT8 nSerialPort, UINT32 nBaudrate);

/*
  stdio.h�ɒ�`���Ă���֐��̒u�������}�N���ł��B
  ���o�͐悪�|�C���^�̂��߁A�V���A���|�[�g�Ɋ֌W�Ȃ��g�p���邱�Ƃ��ł��܂��B
*/
#define SERIAL_sprintf  sprintf
#define SERIAL_sscanf   sscanf

/*!
  ��������V���A���o�͂��܂��B
  NULL�������݂���܂ł̕������V���A���o�͂���̂ŁApStr���w���z��͕K��NULL������
  �I�[���Ă���K�v������܂��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @param pStr         �\��������ւ̃|�C���^
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �������s��
*/
MRESULT SERIAL_puts(UINT8 nSerialPort, char flash *pStr);

/*!
  �V���A�����͂𕶎���Ƃ��Ď擾���܂��B
  ���s�R�[�h��������NULL�������󂯎��܂�pStr�Ɏw�肵���z��ɕ�������i�[���܂��B
  �܂��A(nLength-1)�����𒴂����ꍇ���擾�͏I�����܂��B
  ���s�R�[�h��NULL�����ɒu���������A������̍Ō�͕K��NULL�����ŏI���܂��B
  ���������āAnLength�ɂ͕K�v�ȕ�����+1�̒������w�肷��K�v������܂��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @param pStr         �擾������������i�[����z��ւ̃|�C���^
  @param nLength      �擾���镶����(NULL�������l������2�ȏ���w�肵�Ă�������)
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �������s��
*/
MRESULT SERIAL_gets(UINT8 nSerialPort, char *pStr, UINT8 nLength);

/*!
  ����ch�Ŏw�肵���������V���A���o�͂��܂��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @param ch           �o�͂���ASCII����
  @retval MOXA_SUCCESS  �������ɐ���
  @retval MOXA_E_PARAM  �����Ƃ��Ďw�肵���|�[�g�ԍ��ɊԈႢ������
*/
MRESULT SERIAL_putchar(UINT8 nSerialPort, char ch);

/*!
  �V���A�����͂����P�������擾���܂��B
  ���̊֐����ĂԂƁA���������͂����܂Ńu���b�L���O���܂��B
  �u���b�L���O���Ăق����Ȃ��ꍇ��SERIAL_getch���g�p���Ă��������B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @return �V���A���o�R�Ŏ擾����ASCII����
*/
int SERIAL_getchar(UINT8 nSerialPort);

/*!
  �V���A�����͂����P�������擾���܂��B
  SERIAL_getchar�֐��ƈقȂ�A���������͂����܂Ńu���b�L���O���܂���B
  �o�b�t�@�Ƀf�[�^�����݂��Ȃ��ꍇ��-1��Ԃ��ď������I�����܂��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @retval 0�`255  �V���A���o�R�Ŏ擾����ASCII����
  @retval -1      �o�b�t�@�Ƀf�[�^�����݂��Ȃ�����
*/
int SERIAL_getch(UINT8 nSerialPort);

/*!
  ��M�o�b�t�@����ꂽ���`�F�b�N���܂��B
  �{�֐����ĂԂ��Ƃő����̎�M�����݂ɂ���M�o�b�t�@����ꂽ���ǂ������ׂ邱�Ƃ��ł��܂��B
  �{�֐�����x�ĂԂƎ�M�o�b�t�@���̃t���O�̓N���A����܂��B
  ��M�o�b�t�@������v���Ƃ��āA�f�[�^�����͂���Ă���ɂ�������炸�K�x�ȕp�x�Ŏ擾�֐�
  ���Ă�ł��Ȃ��Ȃǂ��l�����܂��B�����̓s����A�p�ɂɎ擾�֐����ĂԂ��Ƃ��ł��Ȃ��Ȃǂ�
  �������ꍇ�́ASERIAL_RX_BUFSIZE(moxa_config.h�Œ�`)�̃T�C�Y��傫�����Ă݂邱�Ƃ���
  ���߂��܂��B
  �Ȃ��A���݂��Ȃ��|�[�g�ԍ����w�肵���Ƃ��̌��ʂ�FALSE�ł��B

  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @retval TRUE   ��M�o�b�t�@����ꂽ
  @retval FALSE  ��M�o�b�t�@�����Ă��Ȃ�
*/
BOOL SERIAL_checkRxOverflow(UINT8 nSerialPort);

/*!
  �����t�V���A���o�͊֐��ł��B
  �����t�H�[�}�b�g������̋L�q��printf�֐��ɏ������܂��B
  �������ACodeVision�̃v���W�F�N�g�ݒ� (s)printf Features�̒l�ɂ���Ă͎g�p�ł��Ȃ�
  �o�̓t�H�[�}�b�g�����݂��܂��B
  
  @param nSerialPort  �V���A���|�[�g�ԍ����w��(0, 1)
  @param pFmt         �o�̓t�H�[�}�b�g������ւ̃|�C���^
  @param MOXA_SUCCESS �o�͂ɐ���
  @param MOXA_E_PARAM �������s��
*/
MRESULT SERIAL_printf(UINT8 nSerialPort, char flash *pFmt, ...);

//#pragma used-

#endif // __SERIAL_H__
