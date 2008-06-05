/*!
  @file
  @brief ATMEGA128のの制御マクロ定義
  @author Takaaki Ishizawa, Vistarica Designs Co.Ltd.
  @date   2006/02/20
  @version 0.1
 */

#ifndef MEGA128_MACRO_H
#define MEGA128_MACRO_H

//#define ENABLE_GLOBAL_INT()        #asm("sei")  //!< 全ての割り込みを許可
//#define DISABLE_GLOBAL_INT()       #asm("cli")  //!< 全ての割り込みを禁止
//#define NOP()                      #asm("nop")  //!< No Operation
#define ENABLE_GLOBAL_INT()        __asm__ __volatile__ ("sei" ::)
#define DISABLE_GLOBAL_INT()       __asm__ __volatile__ ("cli" ::)
#define NOP()                      __asm__ __volatile__ ("nop" ::)

#endif
