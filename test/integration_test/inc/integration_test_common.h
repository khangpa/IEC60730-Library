/***************************************************************************/ /**
 * @file  integration_test_common.h
 * @brief Integration test init header
 *******************************************************************************
 * # License
 * <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: LicenseRef-MSLA
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/
#ifndef INTEGRATION_TEST_COMMON_H
#define INTEGRATION_TEST_COMMON_H

#include "stdio.h"
#include "em_core.h"
#include "em_rmu.h"
#include "em_wdog.h"
#include "em_gpcrc.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_letimer.h"
#include "sl_iec60730_internal.h"

/* Test Timer instance */
#if (_SILICON_LABS_32B_SERIES == 2)
#if ((defined SL_IEC60730_NON_SECURE_ENABLE) && (!defined(SL_TRUSTZONE_SECURE)))
#define TIMER_10MS  TIMER0_NS
#define TIMER_100MS LETIMER0_NS
#else
#define TIMER_10MS  TIMER0
#define TIMER_100MS LETIMER0
#endif
#else // Series 1 devices
#define TIMER_10MS  TIMER0
#define TIMER_100MS LETIMER0
#endif // (_SILICON_LABS_32B_SERIES == 2)

/* Init structure for timers */
#if defined(_TIMER_CTRL_MODE_MASK)
#if defined(TIMER_CTRL_X2CNT) \
  && (defined(TIMER_CTRL_ATI) || defined(TIMER_CFG_ATI))
#define TIMER_INIT_TEST_10MS                                                \
  { false,                /* Enable timer when initialization completes. */ \
    false,                /* Stop counter during debug halt. */             \
    timerPrescale4,       /* DIV 16. */                                     \
    timerClkSelHFPerClk,  /* Select HFPER / HFPERB clock. */                \
    false,                /* Not 2x count mode. */                          \
    false,                /* No ATI. */                                     \
    timerInputActionNone, /* No action on falling input edge. */            \
    timerInputActionNone, /* No action on rising input edge. */             \
    _TIMER_CTRL_MODE_UP,  /* Up-counting. */                                \
    false, /* Do not clear DMA requests when DMA channel is active. */      \
    false, /* Select X2 quadrature decode mode (if used). */                \
    false, /* Disable one shot. */                                          \
    false, /* Not started/stopped/reloaded by other timers. */              \
    true }
#else
#define TIMER_INIT_TEST_10MS                                                  \
  {                                                                           \
    false,                  /* Enable timer when initialization completes. */ \
    false,                  /* Stop counter during debug halt. */             \
    timerPrescale4,         /* DIV 16. */                                     \
    timerClkSelHFPerClk,    /* Select HFPER / HFPERB clock. */                \
    timerInputActionNone,   /* No action on falling input edge. */            \
    timerInputActionNone,   /* No action on rising input edge. */             \
    _TIMER_CTRL_MODE_UP,    /* Up-counting. */                                \
    false,   /* Do not clear DMA requests when DMA channel is active. */      \
    false,   /* Select X2 quadrature decode mode (if used). */                \
    false,   /* Disable one shot. */                                          \
    false    /* Not started/stopped/reloaded by other timers. */              \
  }
#endif
#endif

#if defined(_TIMER_CFG_MODE_MASK)
#if defined(TIMER_CTRL_X2CNT) \
  && (defined(TIMER_CTRL_ATI) || defined(TIMER_CFG_ATI))
#if (defined(TIMER_CTRL_DISSYNCOUT) || defined(TIMER_CFG_DISSYNCOUT))
#define TIMER_INIT_TEST_10MS                                                          \
  {                                                                                   \
    true,                 /* Enable timer when initialization completes. */           \
    false,                /* Stop counter during debug halt. */                       \
    timerPrescale4,       /* DIV 16. */                                               \
    timerClkSelHFPerClk,  /* Select HFPER / HFPERB clock. */                          \
    false,                /* Not 2x count mode. */                                    \
    false,                /* No ATI. */                                               \
    false,                /* No RSSCOIST. */                                          \
    timerInputActionNone, /* No action on falling input edge. */                      \
    timerInputActionNone, /* No action on rising input edge. */                       \
    timerModeUp,          /* Up-counting. */                                          \
    false,                /* Do not clear DMA requests when DMA channel is active. */ \
    false,                /* Select X2 quadrature decode mode (if used). */           \
    false,                /* Disable one shot. */                                     \
    false,                /* Not started/stopped/reloaded by other timers. */         \
    false                 /* Disable ability to start/stop/reload other timers. */    \
  };
#else
#define TIMER_INIT_TEST_10MS                                                \
  { false,                /* Enable timer when initialization completes. */ \
    false,                /* Stop counter during debug halt. */             \
    timerPrescale4,       /* DIV 16. */                                     \
    timerClkSelHFPerClk,  /* Select HFPER / HFPERB clock. */                \
    false,                /* Not 2x count mode. */                          \
    false,                /* No ATI. */                                     \
    timerInputActionNone, /* No action on falling input edge. */            \
    timerInputActionNone, /* No action on rising input edge. */             \
    timerModeUp,   /* Up-counting. */                                       \
    false, /* Do not clear DMA requests when DMA channel is active. */      \
    false, /* Select X2 quadrature decode mode (if used). */                \
    false, /* Disable one shot. */                                          \
    false, /* Not started/stopped/reloaded by other timers. */              \
    true }
#endif
#else
#define TIMER_INIT_TEST_10MS                                                \
  {                                                                         \
    false,                /* Enable timer when initialization completes. */ \
    false,                /* Stop counter during debug halt. */             \
    timerPrescale4,       /* DIV 16. */                                     \
    timerClkSelHFPerClk,  /* Select HFPER / HFPERB clock. */                \
    timerInputActionNone, /* No action on falling input edge. */            \
    timerInputActionNone, /* No action on rising input edge. */             \
    timerModeUp,   /* Up-counting. */                                       \
    false, /* Do not clear DMA requests when DMA channel is active. */      \
    false, /* Select X2 quadrature decode mode (if used). */                \
    false, /* Disable one shot. */                                          \
    false  /* Not started/stopped/reloaded by other timers. */              \
  }
#endif
#endif

#if defined(LETIMER_CTRL_RTCC0TEN)
#define TIMER_INIT_TEST_100MS                                                \
  {                                                                          \
    false,           /* Enable timer when initialization completes. */       \
    false,           /* Stop counter during debug halt. */                   \
    false,           /* Do not start counting on RTC COMP0 match. */         \
    false,           /* Do not start counting on RTC COMP1 match. */         \
    true,            /* Load COMP0 into CNT on underflow. */                 \
    false,           /* Do not load COMP1 into COMP0 when REP0 reaches 0. */ \
    0,               /* Idle value 0 for output 0. */                        \
    0,               /* Idle value 0 for output 1. */                        \
    letimerUFOANone, /* No action on underflow on output 0. */               \
    letimerUFOANone, /* No action on underflow on output 1. */               \
    letimerRepeatFree, /* Count until stopped by SW. */                      \
    0                  /* Use default top Value. */                          \
  }
#else
#define TIMER_INIT_TEST_100MS                                                \
  {                                                                          \
    false,           /* Enable timer when initialization completes. */       \
    false,           /* Stop counter during debug halt. */                   \
    true,            /* Load COMP0 into CNT on underflow. */                 \
    false,           /* Do not load COMP1 into COMP0 when REP0 reaches 0. */ \
    0,               /* Idle value 0 for output 0. */                        \
    0,               /* Idle value 0 for output 1. */                        \
    letimerUFOANone, /* No action on underflow on output 0. */               \
    letimerUFOANone, /* No action on underflow on output 1. */               \
    letimerRepeatFree, /* Count until stopped by SW. */                      \
    0                  /* Use default top Value. */                          \
  }
#endif

/* Value of the timer counter */
#define TEST_TIMER_RESET_VAL  0
#define TEST_TIMER_PRESET_VAL 3276

/* Timers is clocked by FSRCO 20Mhz */
/* Timer prescaler is 2 so counter clock is 5Mhz () */
/* Counter value for 10ms timing */
#define TEST_TIMER_10MS_VAL   50000
/* Counter value for 100ms timing */
#define TEST_TIMER_100MS_VAL  3276

#if defined(SL_IEC60730_NON_SECURE_ENABLE)
#define T_NVIC_SetPriorityGrouping TZ_NVIC_SetPriorityGrouping_NS
#define T_NVIC_SetPriority         TZ_NVIC_SetPriority_NS
#define T_NVIC_EnableIRQ           TZ_NVIC_EnableIRQ_NS
#else
#define T_NVIC_SetPriorityGrouping NVIC_SetPriorityGrouping
#define T_NVIC_SetPriority         NVIC_SetPriority
#define T_NVIC_EnableIRQ           NVIC_EnableIRQ
#endif

/* Function Prototype */
/* SMU configuration */
void smu_config(void);
/* NVIC configuration */
void nvic_init(void);
/* SCB non-secure configuration */
void system_init_ns(void);
/* Integration test config support */
void integration_test_clock_config(void);
/* Init timer test */
void integration_test_timers_init(void);
/* Enable timer to test interrupt */
void integration_test_timers_enable(void);
/* Disable timer to test interrupt */
void integration_test_timers_disable(void);
/* Setup irq before run test */
void integration_test_init(void);
/* Disable irq after run test */
void integration_test_deinit(void);
/* Run test */
void integration_test_run_init(void);
void integration_test_run_process_action(void);

#endif // INTEGRATION_TEST_COMMON_H
