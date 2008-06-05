/*!
  @file
  @brief MOXA���C�u�����̐ݒ�}�N��

  �{�t�@�C���́AMOXA���C�u�����S�ʂɊ֌W����ݒ�}�N�����L�q����w�b�_�t�@�C���ł��B
  MOXA���C�u�����ɑ΂��Đݒ��ύX����ꍇ�͖{�t�@�C����ҏW���A���C�u�����{�̂̃t�@�C����
  �Ȃ�ׂ��ύX���Ȃ��ł��������B�܂��A�V��������J�������ꍇ�͐V�����{�[�h�^�C�v��ǉ���
  �A����Ɋ֌W����ݒ��V���ɒǉ����Ă��������B
  
  @author Shinji Yamachika
  @date   2005/12/16
  @version 0.1
 */
#ifndef __MOXA_CONFIG_H__
#define __MOXA_CONFIG_H__

#ifdef __AVR_ATmega128__
#define _CHIP_ATMEGA128_
#endif
#define flash

#define __OUT(pin,bit,state) pin = state ? (pin | (1 << bit)) : (pin & ~(1 << bit))
#define __IN(pin,bit)        ((pin & (1 << bit)) != 0)

/**************************************************************************************
  Target board settings
***************************************************************************************/

/*
  �{�[�h�^�C�v�̒l��`�i�J���҈ȊO�͕ύX���Ȃ��ł��������j
�܂��A�V��������J�������Ƃ��͏d�����Ȃ��l�Ń{�[�h�^�C�v��ǉ����Ă�������
*/
#define MOXA_BOARD_PROTO_1     1              //!< CREST prototype board 1
#define MOXA_BOARD_STK300      10             //!< Kanda STK300 Development Kit
#define MOXA_BOARD_CC2420DBK   11             //!< Chipcon CC2420DB 1.2

/*!
  �g�p����{�[�h�^�C�v���w�肵�Ă�������
  �������A�Ȃ�ׂ��v���W�F�N�g�̐ݒ�"Globally #define"�Ŏw�肷�邱�Ƃ������߂��܂��B
*/
#ifndef MOXA_BOARD_TYPE
#define MOXA_BOARD_TYPE  MOXA_BOARD_PROTO_1
#endif

/**************************************************************************************
  Include files
***************************************************************************************/

#include "include.h"
#include "error.h"
//#include "device_proto.h"

/**************************************************************************************
  Target board settings
***************************************************************************************/

/* Micro controller unit settings */

#ifdef _MCU_CLOCK_FREQUENCY_
#define MOXA_MCU_CLOCK  _MCU_CLOCK_FREQUENCY_   //!< MCU Clock (Hz)
/*
  _MCU_CLOCK_FREQUENCY_�}�N����CodeVision�̃v���W�F�N�g�ݒ�Ŏw�肵�܂��B
  �ʏ��_MCU_CLOCK_FREQUENCY_�̒l��MOXA_MCU_CLOCK�ɐݒ肵�Ďg�p���Ă��������B
  else�ȉ��̒l�̓v���W�F�N�g�ݒ�Ŋe�{�[�h�ɐݒ肷�ׂ��N���b�N������������x��
  �Ӗ��ŋL�q���Ă���܂��B�V�����{�[�h���J�������Ƃ��͓���N���b�N��ǉ����Ă��������B
*/
#elif defined F_CPU
#define MOXA_MCU_CLOCK  F_CPU
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define MOXA_MCU_CLOCK  8000000                 //!< PROTO1 Board MCU Clock (Hz)
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define MOXA_MCU_CLOCK  4000000                 //!< STK300 Board MCU Clock (Hz)
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define MOXA_MCU_CLOCK  8000000                 //!< CC2420DBK Board MCU Clock (Hz)
#endif // _MCU_CLOCK_FREQUENCY_

#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_
//#include <mega128.h>
#include <avr/io.h>
#include "mega128_macro.h"
//#include "mega128_reg.h"
#else
#error MCU type is not specified.
#endif

/**************************************************************************************
  Debug settings
***************************************************************************************/

/* Debug options */
#define MOXA_DEBUG_CHECK_INIT     //!< �����������̂Q�d�Ăяo�����`�F�b�N���܂�
//#define MOXA_DEBUG_CHECK_PARAM    //!< �֐��Ăяo�����Ɉ������`�F�b�N���܂�

/**************************************************************************************
   Radio communication settings
***************************************************************************************/

#define MOXA_USE_CHIP_CC2420     //!< �����`�b�v��CC2420���g�p���܂�

/**************************************************************************************
  Memory settings
***************************************************************************************/

/*
  �V��������쐬�����Ƃ���SRAM�T�C�Y��ݒ肵�Ă�������
  SRAM�T�C�Y�ɂ�0, 32, 64�̒l���w�肷�邱�Ƃ��ł��܂�
*/
#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define MEMORY_EXT_SRAM_SIZE  32                     //!< PROTO1��̊O��SRAM�T�C�Y
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define MEMORY_EXT_SRAM_SIZE  0                      //!< STK300��̊O��SRAM�T�C�Y
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define MEMORY_EXT_SRAM_SIZE  0                      //!< CC2420DBK��̊O��SRAM�T�C�Y
#endif

/**************************************************************************************
  Serial settings
***************************************************************************************/

/*!
  �ϒ����������̃o�b�t�@�T�C�Y�ł��BSERIAL_printf, SERIAL_scanf�̊֐��ň����������
  ������SERIAL_VARARG_SIZE�𒴂���Ƃ��A�������������邱�Ƃ��ł��܂���B
  ���̂Ƃ��͐��l��傫�Ȓl�ɕύX���Ă��������B
*/
#define SERIAL_VARARG_SIZE  64

/*!
  �V���A�����M��ʏ�̂Q�{�̑��x�ŏ������܂��B�i�񓯊����[�h�ł����g�p���܂���j
*/
#undef SERIAL_DOUBLE_SPEED

#if (MOXA_BOARD_TYPE == MOXA_BOARD_PROTO_1)
#define SERIAL_PORT_N  2                             //!< PROTO1��̃V���A���|�[�g��
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_STK300)
#define SERIAL_PORT_N  2                             //!< STK300��̃V���A���|�[�g��
#elif (MOXA_BOARD_TYPE == MOXA_BOARD_CC2420DBK)
#define SERIAL_PORT_N  2                             //!< CC2420DBK��̃V���A���|�[�g��
                                                     // ������0�ԃ|�[�g�͎g�p�ł��܂���
#endif

/*
  �o�b�t�@�I�[�o�[�t���[�����������Ƃ��A�T�C�Y��傫�����Ă݂Ă��������B
*/
#define SERIAL_TX_BUFSIZE  32                        //!< �V���A�����M�o�b�t�@�T�C�Y
#define SERIAL_RX_BUFSIZE  32                        //!< �V���A����M�o�b�t�@�T�C�Y

/**************************************************************************************
  Device settings
***************************************************************************************/

#define DEVICE_PORT_N   8    //!< �g�p�\�ȃf�o�C�X�|�[�g�̐�

/**************************************************************************************
  Temperature sensor settings
***************************************************************************************/

#define MOXA_TEMP_USE_LM61   //!< ���x�Z���T�[�Ƃ���LM61���g�p����Ƃ��L���ɂ��Ă�������

#endif // __MOXA_CONFIG_H__
