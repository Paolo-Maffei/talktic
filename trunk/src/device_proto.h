/*!
  @file
  @brief �Z���T�[�̏o�͒l�Ɋւ���f�[�^��`
  @author Shinji Yamachika
  @date   2005/11/21
  @version 0.1
*/

#ifndef __DEVICE_PROTO_H__
#define __DEVICE_PROTO_H__

#include <include.h>

/*!
  �f�o�C�X�̎�ނ�\���񋓌^�ł��B
  �f�o�C�X�̓Z���T�[�ƃA�N�`���G�[�^�ō\������Ă���A�Z���T�[��MCU�ɑ΂��ăf�[�^����͂��܂��B
  �A�N�`���G�[�^��MCU�̎w���ɑ΂��ĉ�������̓�����s�Ȃ��܂��B
  �܂��ADEVICE_TYPE_NULL�̓f�o�C�X�����ڑ��ł��邱�Ƃ�\���܂��B
*/
typedef enum {
    DEVICE_TYPE_NULL,                    //!< �f�o�C�X��ڑ����Ă��Ȃ��Ƃ��w�肵�Ă�������
    SENSOR_TYPE_COLOR,                   //!< ���Z���T�[
    SENSOR_TYPE_INFRARED,                //!< �ԊO���Z���T�[
    SENSOR_TYPE_SGAS,                    //!< �K�X�Z���T�[ (���������o)
    SENSOR_TYPE_HUMIDITY,                //!< ���x�Z���T�[
    SENSOR_TYPE_TEMPERATURE,             //!< ���x�Z���T�[
    SENSOR_TYPE_MIC,                     //!< �}�C�N
    SENSOR_TYPE_AIRPRESSURE,             //!< �C���Z���T�[
    SENSOR_TYPE_PRESSURE,                //!< ���̓Z���T�[
    SENSOR_TYPE_ACCE,                    //!< �����x�Z���T�[
    SENSOR_TYPE_GYRO,                    //!< �p���x�Z���T�[
    SENSOR_TYPE_BEND,                    //!< �Ȃ��Z���T�[
    SENSOR_TYPE_TOUCH,                   //!< �^�b�`�Z���T�[
    SENSOR_TYPE_PUSH,                    //!< �v�b�V���{�^��
    SENSOR_TYPE_SLIDER,                  //!< �X���C�_�[
    SENSOR_TYPE_ROTATION,                //!< ���[�^���[
    ACTUATOR_TYPE_LED,                   //!< LED (Sink�^�C�v)
    ACTUATOR_TYPE_LED2,                  //!< LED (Source�^�C�v)
    DEVICE_TYPE_SIZEOF                   //!< �f�o�C�X�̎�ނ�\���񋓌`�̐�
} DEVICE_Type;

//--------------------------------------------------------------------
// �Z���T�[�̏o�͌^
//--------------------------------------------------------------------

/*!
  ���Z���T�[�̏o�͌^
*/
typedef struct {
    BYTE red;       //!< red
    BYTE green;     //!< green
    BYTE blue;      //!< blue
} SENSOR_Color;

/*!
  �ԊO���Z���T�[�̏o�͌^
*/
typedef UINT16 SENSOR_Infrared;

/*!
  �K�X�i���������o�j�Z���T�[�̏o�͌^
*/
typedef UINT16 SENSOR_SGas;

/*!
  ���x�Z���T�[�̏o�͌^
*/
typedef float SENSOR_Humidity;

/*!
  ���x�Z���T�[�̏o�͌^
*/
typedef float SENSOR_Temperature;

/*!
  �}�C�N�̏o�͌^
*/
typedef INT16 SENSOR_Mic;

/*!
  �C���Z���T�[�̏o�͌^
*/
typedef UINT16 SENSOR_AirPressure;

/*!
  ���̓Z���T�[�̏o�͌^
*/
typedef UINT16 SENSOR_Pressure;

/*!
  �����x�Z���T�[�̏o�͌^
*/
typedef struct {
    INT16 x;     //!< x axis
    INT16 y;     //!< y axis
    INT16 z;     //!< z axis
} SENSOR_Acce;

/*!
  �p���x�Z���T�[�̏o�͌^
*/
typedef struct {
    INT16 x;
    INT16 y;
} SENSOR_Gyro;

/*!
  �Ȃ��Z���T�[�̏o�͌^
*/
typedef INT8 SENSOR_Bend;

/*!
  �^�b�`�Z���T�[�̏o�͌^
*/
typedef UINT16 SENSOR_Touch;

/*!
  �v�b�V���{�^���̏o�͌^
*/
typedef BOOL SENSOR_Push;

/*!
  �X���C�_�[�̏o�͌^
*/
typedef UINT16 SENSOR_Slider;

/*!
  ���[�^���[�X�C�b�`�̏o�͌^
*/
typedef UINT16 SENSOR_Rotary;

/*!
  LED�̏�Ԍ^
*/
typedef BOOL ACTUATOR_Led;

/*!
  �f�o�C�X�̋��ʏo�͌^�ł��B
  ���p�̂Ȃ̂łǂ̌^�Ƃ��Ă������܂����A���ʏo�͌^�̃T�C�Y���ł��T�C�Y�̑傫���^
  (SENSOR_Acce:6Byte)�ɍ��킹����̂ŁA
  �������̈��ߖ񂵂����ꍇ�͒��ڃZ���T�[�^���g�p���Ă��������B
*/
typedef union {
    SENSOR_Color        color;           //!< ���Z���T�[�̃f�[�^��\��
    SENSOR_Infrared     infrared;        //!< �ԊO���Z���T�[�̃f�[�^��\��
    SENSOR_SGas         sgas;            //!< �K�X�Z���T�[�̃f�[�^��\��
    SENSOR_Humidity     humidity;        //!< ���x�Z���T�[�̃f�[�^��\��
    SENSOR_Temperature  temperature;     //!< ���x�Z���T�[�̃f�[�^��\��
    SENSOR_Mic          mic;             //!< �}�C�N�̃f�[�^��\��
    SENSOR_AirPressure  airpressure;     //!< �C���Z���T�[�̃f�[�^��\��
    SENSOR_Pressure     pressure;        //!< ���̓Z���T�[�̃f�[�^��\��
    SENSOR_Acce         acce;            //!< �����x�Z���T�[�̃f�[�^��\��
    SENSOR_Gyro         gyro;            //!< �p���x�Z���T�[�̃f�[�^��\��
    SENSOR_Bend         bend;            //!< �Ȃ��Z���T�[�̏�Ԃ�\��
    SENSOR_Touch        touch;           //!< �^�b�`�Z���T�[�̏�Ԃ�\��
    SENSOR_Push         push;            //!< �v�b�V���{�^���̏�Ԃ�\��
    SENSOR_Slider       slider;          //!< �X���C�_�[�̏�Ԃ�\��
    SENSOR_Rotary       rotary;          //!< ���[�^���[�X�C�b�`�̏�Ԃ�\��
    ACTUATOR_Led        led;             //!< LED�̏�Ԃ�\��
} DEVICE_Value;

#endif // __DEVICE_PROTO_H__
