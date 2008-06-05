/*!
  @file
  @brief �h���C�o�֌W�̐ݒ�}�N��

  MOXA���C�u�����ł́AMCU�Ɠ��ʂȌ����Őڑ����Ă���f�o�C�X�̏������K�肵���\�t�g�E�F�A��
  ���Ƃ��h���C�o�ƌĂ�ł��܂��B
  �ʏ�̃f�o�C�X�̓f�o�C�X�|�[�g�ƌĂԒ��ۃ|�[�g�ɑ΂��Đڑ�����܂����A�h���C�o�͓��ʂ�
  ����ɂ��ڑ���MCU��I/O�|�[�g�P�ʂŎw�肷��K�v������܂��B
  ���̎w���{�t�@�C���ōs�Ȃ��Ă��������B
  �e�h���C�o���Ƃɐڑ�I/O�|�[�g�̐ݒ���L�q���Ă��������B
  �܂��A�V�����f�o�C�X���쐬�����Ƃ��A������h���C�o�Ƃ��Ē�`����ꍇ�͖{�t�@�C���ɐݒ��
  �ǉ����Ă��������B
  
  @author Shinji Yamachika
  @date   2005/12/16
  @version 0.1
 */
#ifndef __MOXA_DRIVER_H__
#define __MOXA_DRIVER_H__

/**************************************************************************************
  SHT11 (humidity and temperature sensor) settings
***************************************************************************************/

// SHT11 I/O settings
#define	CHIP_SHT11_CLK_OUT_BIT      __IN(PORTE,4)       //!< �N���b�N�r�b�g�ԍ��̎w��
#define	CHIP_SHT11_CLK_DIR_BIT      __IN(DDRE,4)        //!< �N���b�N�����̎w��
#define	CHIP_SHT11_DATA_OUT_BIT     __IN(PORTE,5)       //!< �o�̓r�b�g�ԍ��̎w��
#define	CHIP_SHT11_DATA_IN_BIT      __IN(PINE,5)        //!< ���̓r�b�g�ԍ��̎w��
#define	CHIP_SHT11_DATA_DIR_BIT     __IN(DDRE,5)        //!< �f�[�^�����̎w��

#define	CHIP_SHT11_CLK_OUT_BIT_(s)      __OUT(PORTE,4,s)       //!< �N���b�N�r�b�g�ԍ��̎w��
#define	CHIP_SHT11_CLK_DIR_BIT_(s)      __OUT(DDRE,4,s)        //!< �N���b�N�����̎w��
#define	CHIP_SHT11_DATA_OUT_BIT_(s)     __OUT(PORTE,5,s)       //!< �o�̓r�b�g�ԍ��̎w��
#define	CHIP_SHT11_DATA_IN_BIT_(s)      __OUT(PINE,5,s)        //!< ���̓r�b�g�ԍ��̎w��
#define	CHIP_SHT11_DATA_DIR_BIT_(s)     __OUT(DDRE,5,s)        //!< �f�[�^�����̎w��

#undef CHIP_SHT11_USE_DEW_POINT   //!< ���I���x�����߂�֐����g�p����}�N��

#endif // __MOXA_DRIVER_H__
