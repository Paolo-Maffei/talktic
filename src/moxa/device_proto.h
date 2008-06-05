/*!
  @file
  @brief センサーの出力値に関するデータ定義
  @author Shinji Yamachika
  @date   2005/11/21
  @version 0.1
*/

#ifndef __DEVICE_PROTO_H__
#define __DEVICE_PROTO_H__

#include <include.h>

/*!
  デバイスの種類を表す列挙型です。
  デバイスはセンサーとアクチュエータで構成されており、センサーはMCUに対してデータを入力します。
  アクチュエータはMCUの指示に対して何かしらの動作を行ないます。
  また、DEVICE_TYPE_NULLはデバイスが未接続であることを表します。
*/
typedef enum {
    DEVICE_TYPE_NULL,                    //!< デバイスを接続していないとき指定してください
    SENSOR_TYPE_COLOR,                   //!< 光センサー
    SENSOR_TYPE_INFRARED,                //!< 赤外線センサー
    SENSOR_TYPE_SGAS,                    //!< ガスセンサー (硫化物検出)
    SENSOR_TYPE_HUMIDITY,                //!< 湿度センサー
    SENSOR_TYPE_TEMPERATURE,             //!< 温度センサー
    SENSOR_TYPE_MIC,                     //!< マイク
    SENSOR_TYPE_AIRPRESSURE,             //!< 気圧センサー
    SENSOR_TYPE_PRESSURE,                //!< 圧力センサー
    SENSOR_TYPE_ACCE,                    //!< 加速度センサー
    SENSOR_TYPE_GYRO,                    //!< 角速度センサー
    SENSOR_TYPE_BEND,                    //!< 曲げセンサー
    SENSOR_TYPE_TOUCH,                   //!< タッチセンサー
    SENSOR_TYPE_PUSH,                    //!< プッシュボタン
    SENSOR_TYPE_SLIDER,                  //!< スライダー
    SENSOR_TYPE_ROTATION,                //!< ロータリー
    ACTUATOR_TYPE_LED,                   //!< LED (Sinkタイプ)
    ACTUATOR_TYPE_LED2,                  //!< LED (Sourceタイプ)
    DEVICE_TYPE_SIZEOF                   //!< デバイスの種類を表す列挙形の数
} DEVICE_Type;

//--------------------------------------------------------------------
// センサーの出力型
//--------------------------------------------------------------------

/*!
  光センサーの出力型
*/
typedef struct {
    BYTE red;       //!< red
    BYTE green;     //!< green
    BYTE blue;      //!< blue
} SENSOR_Color;

/*!
  赤外光センサーの出力型
*/
typedef UINT16 SENSOR_Infrared;

/*!
  ガス（硫化物検出）センサーの出力型
*/
typedef UINT16 SENSOR_SGas;

/*!
  湿度センサーの出力型
*/
typedef float SENSOR_Humidity;

/*!
  温度センサーの出力型
*/
typedef float SENSOR_Temperature;

/*!
  マイクの出力型
*/
typedef INT16 SENSOR_Mic;

/*!
  気圧センサーの出力型
*/
typedef UINT16 SENSOR_AirPressure;

/*!
  圧力センサーの出力型
*/
typedef UINT16 SENSOR_Pressure;

/*!
  加速度センサーの出力型
*/
typedef struct {
    INT16 x;     //!< x axis
    INT16 y;     //!< y axis
    INT16 z;     //!< z axis
} SENSOR_Acce;

/*!
  角速度センサーの出力型
*/
typedef struct {
    INT16 x;
    INT16 y;
} SENSOR_Gyro;

/*!
  曲げセンサーの出力型
*/
typedef INT8 SENSOR_Bend;

/*!
  タッチセンサーの出力型
*/
typedef UINT16 SENSOR_Touch;

/*!
  プッシュボタンの出力型
*/
typedef BOOL SENSOR_Push;

/*!
  スライダーの出力型
*/
typedef UINT16 SENSOR_Slider;

/*!
  ロータリースイッチの出力型
*/
typedef UINT16 SENSOR_Rotary;

/*!
  LEDの状態型
*/
typedef BOOL ACTUATOR_Led;

/*!
  デバイスの共通出力型です。
  共用体なのでどの型としても扱えますが、共通出力型のサイズが最もサイズの大きい型
  (SENSOR_Acce:6Byte)に合わせられるので、
  メモリ領域を節約したい場合は直接センサー型を使用してください。
*/
typedef union {
    SENSOR_Color        color;           //!< 光センサーのデータを表す
    SENSOR_Infrared     infrared;        //!< 赤外線センサーのデータを表す
    SENSOR_SGas         sgas;            //!< ガスセンサーのデータを表す
    SENSOR_Humidity     humidity;        //!< 湿度センサーのデータを表す
    SENSOR_Temperature  temperature;     //!< 温度センサーのデータを表す
    SENSOR_Mic          mic;             //!< マイクのデータを表す
    SENSOR_AirPressure  airpressure;     //!< 気圧センサーのデータを表す
    SENSOR_Pressure     pressure;        //!< 圧力センサーのデータを表す
    SENSOR_Acce         acce;            //!< 加速度センサーのデータを表す
    SENSOR_Gyro         gyro;            //!< 角速度センサーのデータを表す
    SENSOR_Bend         bend;            //!< 曲げセンサーの状態を表す
    SENSOR_Touch        touch;           //!< タッチセンサーの状態を表す
    SENSOR_Push         push;            //!< プッシュボタンの状態を表す
    SENSOR_Slider       slider;          //!< スライダーの状態を表す
    SENSOR_Rotary       rotary;          //!< ロータリースイッチの状態を表す
    ACTUATOR_Led        led;             //!< LEDの状態を表す
} DEVICE_Value;

#endif // __DEVICE_PROTO_H__
