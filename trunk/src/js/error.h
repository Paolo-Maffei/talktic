/*!
  @file
  @brief MOXA�֐��̖߂�l��`

  ��{�I��MOXA���C�u�����֐��̖߂�l��MRESULT��Ԃ��܂��B
  MRESULT�̒l�͈̔͂�-128�`127�ł��B
  MRESULT�̒l�����̂Ƃ������͐������Ă��邱�Ƃ��Ӗ����܂��B
  MRESULT�̒l�����̂Ƃ������͎��s���Ă��邱�Ƃ��Ӗ����܂��B
  �֐��̏��������������Ƃ��́AMOXA_SUCCESS(0)��Ԃ��܂��B
  �֐��̏����Ɏ��s�����Ƃ��́AMOXA_E_FAIL(-1)��Ԃ��܂��B
  �֐��ɓn���������s���������Ƃ��́AMOXA_E_PARAM(-2)��Ԃ��܂��B

  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __ERROR_H__
#define __ERROR_H__

#define MRESULT         signed char   //!< �֐��߂�l�^

#define MOXA_SUCCESS    0             //!< �֐��̏��������������Ƃ��̖߂�l
#define MOXA_E_FAIL    -1             //!< �֐��̏��������s�����Ƃ��̖߂�l
#define MOXA_E_PARAM   -2             //!< �֐��ɓn���������s���ȂƂ��̖߂�l

#define MOXA_SUCCEEDED(x)  ((x) >= 0)     //!< MRESULT�^�������̐������Ӗ�����Ƃ��^�̒l��Ԃ�
#define MOXA_FAILED(x)     ((x) < 0)      //!< MRESULT�^�������̎��s���Ӗ�����Ƃ��^�̒l��Ԃ�

#endif // __ERROR_H__
