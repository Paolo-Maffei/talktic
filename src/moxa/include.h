/*!
  @file
  @brief MOXA���ʌ^�̒�`
  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __INCLUDE_H__
#define __INCLUDE_H__

// �f�[�^����`�^
// MCU��ύX�����Ƃ��͂����̒�`����x�������Ă�������
#if defined _CHIP_ATMEGA128_ | defined _CHIP_ATMEGA128L_
typedef unsigned char		BOOL;     //!< ��l�𖾎�����Ƃ��g�p���Ă�������

typedef unsigned char		BYTE;     //!< �����Ȃ�1Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef unsigned short		WORD;     //!< �����Ȃ�2Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef unsigned long		DWORD;    //!< �����Ȃ�4Byte�^�𖾎�����Ƃ��g�p���Ă�������

typedef unsigned char		UINT8;    //!< �����Ȃ�1Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef unsigned short		UINT16;   //!< �����Ȃ�2Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef unsigned long		UINT32;   //!< �����Ȃ�4Byte�^�𖾎�����Ƃ��g�p���Ă�������

typedef signed char			INT8;     //!< ��������1Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef signed short		INT16;    //!< ��������2Byte�^�𖾎�����Ƃ��g�p���Ă�������
typedef signed long			INT32;    //!< ��������4Byte�^�𖾎�����Ƃ��g�p���Ă�������
#endif

// ���ʒl
#ifndef FALSE
#define FALSE 0    //!< BOOL�^�ɑ΂��ċU�̒l�𖾎�����Ƃ��g�p���Ă�������
#endif

#ifndef TRUE
#define TRUE 1     //!< BOOL�^�ɑ΂��Đ^�̒l�𖾎�����Ƃ��g�p���Ă�������
#endif

#ifndef NULL
#define NULL 0     //!< ANSI�ŋK�肳��Ă���NULL�^�ł��istdio.h���g�p���Ȃ��Ƃ��̂��߂ɒ�`���Ă���܂��j
#endif

// �ėp�}�N��
#define BM(n)     (1 << (n))                 //!< n�Ɏw�肵���r�b�g���������Ă���l�𐶐����܂�
#define BF(x,b,s) (((x) & (b)) >> (s))       //!< x��b�̘_���ς�s�r�b�g�E�V�t�g�����l�𐶐����܂�
#define MIN(n,m)  (((n) < (m)) ? (n) : (m))  //!< n��m�̂������������̒l��Ԃ��܂�
#define MAX(n,m)  (((n) < (m)) ? (m) : (n))  //!< n��m�̂����傫�����̒l��Ԃ��܂�
#define ABS(n)    (((n) < 0) ? (-(n)) : (n)) //!< n�̐�Βl��Ԃ��܂�

// �֐��|�C���^�^
typedef void (*VFPTR)(void);   //!< VFPTR���A�߂�lvoid�E����void�̊֐��|�C���^�^��\���܂�

#endif // __INCLUDE_H__
