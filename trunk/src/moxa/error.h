/*!
  @file
  @brief MOXA関数の戻り値定義

  基本的にMOXAライブラリ関数の戻り値はMRESULTを返します。
  MRESULTの値の範囲は-128～127です。
  MRESULTの値が正のとき処理は成功していることを意味します。
  MRESULTの値が負のとき処理は失敗していることを意味します。
  関数の処理が成功したときは、MOXA_SUCCESS(0)を返します。
  関数の処理に失敗したときは、MOXA_E_FAIL(-1)を返します。
  関数に渡す引数が不正だったときは、MOXA_E_PARAM(-2)を返します。

  @author Shinji Yamachika, Vistarica Designs Co.Ltd.
  @date   2005/12/7
  @version 0.1
*/
#ifndef __ERROR_H__
#define __ERROR_H__

#define MRESULT         signed char   //!< 関数戻り値型

#define MOXA_SUCCESS    0             //!< 関数の処理が成功したときの戻り値
#define MOXA_E_FAIL    -1             //!< 関数の処理が失敗したときの戻り値
#define MOXA_E_PARAM   -2             //!< 関数に渡す引数が不正なときの戻り値

#define MOXA_SUCCEEDED(x)  ((x) >= 0)     //!< MRESULT型が処理の成功を意味するとき真の値を返す
#define MOXA_FAILED(x)     ((x) < 0)      //!< MRESULT型が処理の失敗を意味するとき真の値を返す

#endif // __ERROR_H__
