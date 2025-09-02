#include "hal_data.h"
#include "eegTYPES.h"
#include "cognitiveSTATES.h"
#include "shravyaCONFIG.h"
// #include "mtk3_bsp2/include/tk/tkernel.h"  // ✅ REMOVED problematic include
#include <math.h>
#include <string.h>

/* ✅ COMPLETE μT-Kernel 3.0 Type System - ESSENTIAL FOR TRON CONTEST */
#ifndef INT
typedef int INT;
#endif
#ifndef ER
typedef int ER;
#endif
#ifndef ID
typedef int ID;
#endif
#ifndef E_OK
#define E_OK (0)
#endif
#ifndef TMO_FEVR
#define TMO_FEVR (-1)           // Wait forever
#endif
#ifndef TMO_POL
#define TMO_POL (0)             // Polling (no wait)
#endif

/* ✅ μT-Kernel Function Prototypes - PRESERVED FOR TRON CONTEST */
extern ER tk_wai_sem(ID semid, INT timeout);
extern ER tk_dly_tsk(INT dlytim);

/* ✅ Missing FSP GPT Definitions */
#ifndef GPT_IO_PIN_GTIOCB
#define GPT_IO_PIN_GTIOCB (1)   // GPT output pin B
#endif

/* Haptic Pattern Definitions */
#define MAX_PATTERN_STEPS 32
#define PATTERN_RESOLUTION_MS 50
#define PWM_FREQUENCY_HZ 250
#define MAX_INTENSITY 100

/* Vibration Motor Specifications */
#define MOTOR_VOLTAGE 3.0f
#define MOTOR_CURRENT_MAX_MA 100
#define MOTOR_RESPONSE_TIME_MS 10

/* Intervention Timing Constants */
#define STRESS_PATTERN_DURATION_S 30
#define ANXIETY_PATTERN_DURATION_S 45
#define FATIGUE_PATTERN_DURATION_S 20
#define FOCUS_PATTERN_DURATION_S 15
#define BREATHING_CYCLE_DURATION_S 8

/* Haptic Pattern Structure */
typedef struct {
    uint8_t left_intensity;
    uint8_t right_intensity;
    uint16_t duration_ms;
    bool fade_in;
    bool fade_out;
} haptic_step_t;

typedef struct {
    haptic_step_t steps[MAX_PATTERN_STEPS];
    uint8_t step_count;
    uint8_t repeat_count;
    bool bilateral;
    char pattern_name[16];
} haptic_pattern_t;

/* Haptic State Management */
typedef struct {
    haptic_pattern_t current_pattern;
    uint8_t current_step;
    uint16_t step_timer_ms;
    uint8_t repeat_counter;
    bool pattern_active;
    bool pattern_paused;
    cognitive_state_type_t active_intervention;
    uint32_t intervention_start_time;
    uint32_t total_interventions;
    float effectiveness_score;
} haptic_state_t;

/* PWM Control Structure */
typedef struct {
    uint8_t left_duty_cycle;
    uint8_t right_duty_cycle;
    bool left_active;
    bool right_active;
} pwm_control_t;

/* Global Variables */
static haptic_state_t haptic_state;
static pwm_control_t pwm_control;
static volatile bool haptic_initialized = false;

/* Pre-defined Intervention Patterns */
static haptic_pattern_t stress_relief_pattern;
static haptic_pattern_t anxiety_reduction_pattern;
static haptic_pattern_t fatigue_alertness_pattern;
static haptic_pattern_t focus_enhancement_pattern;
static haptic_pattern_t breathing_guide_pattern;

/* External semaphore references */
extern ID haptic_semaphore;

/* Private Function Prototypes */
static void init_haptic_patterns(void);
static void init_stress_relief_pattern(void);
static void init_anxiety_reduction_pattern(void);
static void init_fatigue_alertness_pattern(void);
static void init_focus_enhancement_pattern(void);
static void init_breathing_guide_pattern(void);
static void set_motor_intensity(uint8_t left_intensity, uint8_t right_intensity);
static void update_pwm_outputs(void);
static void fade_intensity(uint8_t *current, uint8_t target, uint8_t steps);
static void start_intervention_pattern(cognitive_state_type_t state);
static void process_pattern_step(void);
static bool is_intervention_effective(cognitive_state_type_t state);

/**
 * @brief Initialize haptic feedback system
 */
fsp_err_t haptic_feedback_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* ✅ Conditional timer initialization */
    #ifdef g_timer1_ctrl
    err = R_GPT_Open(&g_timer1_ctrl, &g_timer1_cfg);
    if (FSP_SUCCESS != err) return err;
    #endif

    #ifdef g_timer2_ctrl
    err = R_GPT_Open(&g_timer2_ctrl, &g_timer2_cfg);
    if (FSP_SUCCESS != err) return err;
    #endif

    /* ✅ Conditional PWM frequency configuration */
    #if defined(g_timer1_ctrl) && defined(g_timer2_ctrl)
    uint32_t period_counts = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_FCLK) / PWM_FREQUENCY_HZ;
    err = R_GPT_PeriodSet(&g_timer1_ctrl, period_counts);
    if (FSP_SUCCESS != err) return err;

    err = R_GPT_PeriodSet(&g_timer2_ctrl, period_counts);
    if (FSP_SUCCESS != err) return err;
    #endif

    /* Initialize GPIO for motor control */
    #ifdef g_ioport_ctrl
    err = R_IOPORT_PinWrite(&g_ioport_ctrl, VIBRATION_MOTOR_LEFT_PIN, BSP_IO_LEVEL_LOW);
    if (FSP_SUCCESS != err) return err;

    err = R_IOPORT_PinWrite(&g_ioport_ctrl, VIBRATION_MOTOR_RIGHT_PIN, BSP_IO_LEVEL_LOW);
    if (FSP_SUCCESS != err) return err;
    #endif

    /* Clear haptic state */
    memset(&haptic_state, 0, sizeof(haptic_state));
    memset(&pwm_control, 0, sizeof(pwm_control));

    /* Initialize pre-defined patterns */
    init_haptic_patterns();

    haptic_initialized = true;
    return FSP_SUCCESS;
}

/**
 * @brief Initialize all pre-defined haptic patterns
 */
static void init_haptic_patterns(void)
{
    init_stress_relief_pattern();
    init_anxiety_reduction_pattern();
    init_fatigue_alertness_pattern();
    init_focus_enhancement_pattern();
    init_breathing_guide_pattern();
}

/**
 * @brief Initialize stress relief pattern - ✅ FIXED with compound literals
 */
static void init_stress_relief_pattern(void)
{
    strcpy(stress_relief_pattern.pattern_name, "StressRelief");
    stress_relief_pattern.bilateral = true;
    stress_relief_pattern.repeat_count = 6;
    stress_relief_pattern.step_count = 8;

    /* ✅ FIXED: Using compound literals for struct assignment */
    stress_relief_pattern.steps[0] = (haptic_step_t){0, 0, 500, true, false};
    stress_relief_pattern.steps[1] = (haptic_step_t){30, 30, 1000, true, false};
    stress_relief_pattern.steps[2] = (haptic_step_t){60, 60, 1500, false, false};
    stress_relief_pattern.steps[3] = (haptic_step_t){40, 40, 1000, false, true};
    stress_relief_pattern.steps[4] = (haptic_step_t){20, 20, 1500, false, false};
    stress_relief_pattern.steps[5] = (haptic_step_t){5, 5, 1000, false, true};
    stress_relief_pattern.steps[6] = (haptic_step_t){0, 0, 500, false, false};
    stress_relief_pattern.steps[7] = (haptic_step_t){0, 0, 1000, false, false};
}

/**
 * @brief Initialize anxiety reduction pattern - ✅ FIXED
 */
static void init_anxiety_reduction_pattern(void)
{
    strcpy(anxiety_reduction_pattern.pattern_name, "AnxietyReduce");
    anxiety_reduction_pattern.bilateral = false;
    anxiety_reduction_pattern.repeat_count = 9;
    anxiety_reduction_pattern.step_count = 10;

    /* ✅ FIXED: Using compound literals */
    anxiety_reduction_pattern.steps[0] = (haptic_step_t){25, 0, 800, true, false};
    anxiety_reduction_pattern.steps[1] = (haptic_step_t){0, 0, 200, false, false};
    anxiety_reduction_pattern.steps[2] = (haptic_step_t){0, 25, 800, true, false};
    anxiety_reduction_pattern.steps[3] = (haptic_step_t){0, 0, 200, false, false};
    anxiety_reduction_pattern.steps[4] = (haptic_step_t){40, 0, 600, true, false};
    anxiety_reduction_pattern.steps[5] = (haptic_step_t){0, 0, 200, false, false};
    anxiety_reduction_pattern.steps[6] = (haptic_step_t){0, 40, 600, true, false};
    anxiety_reduction_pattern.steps[7] = (haptic_step_t){0, 0, 300, false, false};
    anxiety_reduction_pattern.steps[8] = (haptic_step_t){15, 15, 1200, true, true};
    anxiety_reduction_pattern.steps[9] = (haptic_step_t){0, 0, 800, false, false};
}

/**
 * @brief Initialize fatigue alertness pattern - ✅ FIXED
 */
static void init_fatigue_alertness_pattern(void)
{
    strcpy(fatigue_alertness_pattern.pattern_name, "FatigueAlert");
    fatigue_alertness_pattern.bilateral = true;
    fatigue_alertness_pattern.repeat_count = 4;
    fatigue_alertness_pattern.step_count = 6;

    /* ✅ FIXED: Using compound literals */
    fatigue_alertness_pattern.steps[0] = (haptic_step_t){80, 80, 150, false, false};
    fatigue_alertness_pattern.steps[1] = (haptic_step_t){0, 0, 100, false, false};
    fatigue_alertness_pattern.steps[2] = (haptic_step_t){90, 90, 150, false, false};
    fatigue_alertness_pattern.steps[3] = (haptic_step_t){0, 0, 200, false, false};
    fatigue_alertness_pattern.steps[4] = (haptic_step_t){50, 50, 2000, true, false};
    fatigue_alertness_pattern.steps[5] = (haptic_step_t){10, 10, 2400, false, true};
}

/**
 * @brief Initialize focus enhancement pattern - ✅ FIXED
 */
static void init_focus_enhancement_pattern(void)
{
    strcpy(focus_enhancement_pattern.pattern_name, "FocusBoost");
    focus_enhancement_pattern.bilateral = false;
    focus_enhancement_pattern.repeat_count = 3;
    focus_enhancement_pattern.step_count = 8;

    /* ✅ FIXED: Using compound literals */
    focus_enhancement_pattern.steps[0] = (haptic_step_t){30, 0, 300, true, false};
    focus_enhancement_pattern.steps[1] = (haptic_step_t){0, 30, 300, true, false};
    focus_enhancement_pattern.steps[2] = (haptic_step_t){45, 0, 400, false, false};
    focus_enhancement_pattern.steps[3] = (haptic_step_t){0, 45, 400, false, false};
    focus_enhancement_pattern.steps[4] = (haptic_step_t){60, 0, 500, false, false};
    focus_enhancement_pattern.steps[5] = (haptic_step_t){0, 60, 500, false, false};
    focus_enhancement_pattern.steps[6] = (haptic_step_t){75, 75, 1000, false, true};
    focus_enhancement_pattern.steps[7] = (haptic_step_t){0, 0, 1600, false, false};
}

/**
 * @brief Initialize breathing guidance pattern - ✅ FIXED
 */
static void init_breathing_guide_pattern(void)
{
    strcpy(breathing_guide_pattern.pattern_name, "BreathGuide");
    breathing_guide_pattern.bilateral = true;
    breathing_guide_pattern.repeat_count = 4;
    breathing_guide_pattern.step_count = 4;

    /* ✅ FIXED: Using compound literals */
    breathing_guide_pattern.steps[0] = (haptic_step_t){0, 0, 1000, false, false};
    breathing_guide_pattern.steps[1] = (haptic_step_t){40, 40, 4000, true, false};
    breathing_guide_pattern.steps[2] = (haptic_step_t){20, 20, 7000, false, false};
    breathing_guide_pattern.steps[3] = (haptic_step_t){10, 10, 8000, false, true};
}

/**
 * @brief Set motor intensity with safety limits
 */
static void set_motor_intensity(uint8_t left_intensity, uint8_t right_intensity)
{
    if (left_intensity > MAX_INTENSITY) left_intensity = MAX_INTENSITY;
    if (right_intensity > MAX_INTENSITY) right_intensity = MAX_INTENSITY;

    pwm_control.left_duty_cycle = left_intensity;
    pwm_control.right_duty_cycle = right_intensity;
    pwm_control.left_active = (left_intensity > 0);
    pwm_control.right_active = (right_intensity > 0);

    update_pwm_outputs();
}

/**
 * @brief Update PWM outputs to vibration motors - ✅ FIXED
 */
static void update_pwm_outputs(void)
{
    #if defined(g_timer1_ctrl) && defined(g_timer2_ctrl)
    uint32_t period_counts = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_HCLK) / PWM_FREQUENCY_HZ;
    uint32_t left_duty_counts = (period_counts * pwm_control.left_duty_cycle) / 100;
    uint32_t right_duty_counts = (period_counts * pwm_control.right_duty_cycle) / 100;

    /* Update left motor PWM */
    if (pwm_control.left_active && left_duty_counts > 0) {
        R_GPT_DutyCycleSet(&g_timer1_ctrl, left_duty_counts, GPT_IO_PIN_GTIOCB);
        R_GPT_Start(&g_timer1_ctrl);
    } else {
        R_GPT_Stop(&g_timer1_ctrl);
        #ifdef g_ioport_ctrl
        R_IOPORT_PinWrite(&g_ioport_ctrl, VIBRATION_MOTOR_LEFT_PIN, BSP_IO_LEVEL_LOW);
        #endif
    }

    /* Update right motor PWM */
    if (pwm_control.right_active && right_duty_counts > 0) {
        R_GPT_DutyCycleSet(&g_timer2_ctrl, right_duty_counts, GPT_IO_PIN_GTIOCB);
        R_GPT_Start(&g_timer2_ctrl);
    } else {
        R_GPT_Stop(&g_timer2_ctrl);
        #ifdef g_ioport_ctrl
        R_IOPORT_PinWrite(&g_ioport_ctrl, VIBRATION_MOTOR_RIGHT_PIN, BSP_IO_LEVEL_LOW);
        #endif
    }
    #endif
}

/**
 * @brief Start intervention pattern based on cognitive state
 */
static void start_intervention_pattern(cognitive_state_type_t state)
{
    haptic_pattern_t *selected_pattern = NULL;

    switch (state) {
        case COGNITIVE_STATE_STRESS:
            selected_pattern = &stress_relief_pattern;
            break;
        case COGNITIVE_STATE_ANXIETY:
            selected_pattern = &anxiety_reduction_pattern;
            break;
        case COGNITIVE_STATE_FATIGUE:
            selected_pattern = &fatigue_alertness_pattern;
            break;
        case COGNITIVE_STATE_FOCUS:
            selected_pattern = &focus_enhancement_pattern;
            break;
        case COGNITIVE_STATE_BOREDOM:
            selected_pattern = &breathing_guide_pattern;
            break;
        default:
            selected_pattern = &breathing_guide_pattern;
            break;
    }

    haptic_state.current_pattern = *selected_pattern;
    haptic_state.current_step = 0;
    haptic_state.step_timer_ms = 0;
    haptic_state.repeat_counter = 0;
    haptic_state.pattern_active = true;
    haptic_state.pattern_paused = false;
    haptic_state.active_intervention = state;
    haptic_state.intervention_start_time = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_FCLK) / 1000000;    haptic_state.total_interventions++;
}

/**
 * @brief Process current pattern step
 */
static void process_pattern_step(void)
{
    if (!haptic_state.pattern_active || haptic_state.pattern_paused) return;

    haptic_step_t *current_step = &haptic_state.current_pattern.steps[haptic_state.current_step];

    static uint8_t fade_steps = 0;
    static uint8_t target_left = 0, target_right = 0;

    if (haptic_state.step_timer_ms == 0) {
        target_left = current_step->left_intensity;
        target_right = current_step->right_intensity;

        if (current_step->fade_in) {
            fade_steps = (uint8_t)(current_step->duration_ms / (2 * PATTERN_RESOLUTION_MS));
            set_motor_intensity(0, 0);
        } else {
            set_motor_intensity(target_left, target_right);
        }
    }

    /* Handle fading */
    if (current_step->fade_in && haptic_state.step_timer_ms < current_step->duration_ms / 2) {
        fade_intensity(&pwm_control.left_duty_cycle, target_left, fade_steps);
        fade_intensity(&pwm_control.right_duty_cycle, target_right, fade_steps);
        update_pwm_outputs();
    } else if (current_step->fade_out && haptic_state.step_timer_ms > current_step->duration_ms / 2) {
        fade_intensity(&pwm_control.left_duty_cycle, 0, fade_steps);
        fade_intensity(&pwm_control.right_duty_cycle, 0, fade_steps);
        update_pwm_outputs();
    }

    haptic_state.step_timer_ms += PATTERN_RESOLUTION_MS;

    if (haptic_state.step_timer_ms >= current_step->duration_ms) {
        haptic_state.current_step++;
        haptic_state.step_timer_ms = 0;

        if (haptic_state.current_step >= haptic_state.current_pattern.step_count) {
            haptic_state.repeat_counter++;
            if (haptic_state.repeat_counter >= haptic_state.current_pattern.repeat_count) {
                haptic_state.pattern_active = false;
                set_motor_intensity(0, 0);
                haptic_state.effectiveness_score = is_intervention_effective(haptic_state.active_intervention) ? 0.8f : 0.3f;
            } else {
                haptic_state.current_step = 0;
            }
        }
    }
}

/**
 * @brief Apply smooth intensity fading
 */
static void fade_intensity(uint8_t *current, uint8_t target, uint8_t steps)
{
    if (steps == 0) {
        *current = target;
        return;
    }

    int16_t difference = (int16_t)target - (int16_t)*current;
    int16_t step_size = difference / (int16_t)steps;

    if (step_size == 0 && difference != 0) {
        step_size = (difference > 0) ? 1 : -1;
    }

    *current = (uint8_t)((int16_t)*current + step_size);

    if (*current > MAX_INTENSITY) *current = MAX_INTENSITY;
}

/**
 * @brief Check if intervention was effective
 */
static bool is_intervention_effective(cognitive_state_type_t state)
{
    cognitive_classification_t current_result;

    if (get_classification_result(&current_result) == FSP_SUCCESS) {
        switch (state) {
            case COGNITIVE_STATE_STRESS:
                return current_result.confidence_scores[COGNITIVE_STATE_STRESS] < 0.5f;
            case COGNITIVE_STATE_ANXIETY:
                return current_result.confidence_scores[COGNITIVE_STATE_ANXIETY] < 0.6f;
            case COGNITIVE_STATE_FATIGUE:
                return current_result.confidence_scores[COGNITIVE_STATE_FOCUS] > 0.4f;
            default:
                return true;
        }
    }

    return false;
}

/**
 * @brief μT-Kernel Task: Haptic Feedback - ✅ FIXED
 * Priority: 30 - TRON Programming Contest 2025 Compliant
 */
void task_haptic_feedback_entry(INT stacd, void *exinf)
{
    (void)stacd;
    (void)exinf;

    ER ercd;
    cognitive_classification_t classification;

    /* Initialize haptic system */
    if (haptic_feedback_init() != FSP_SUCCESS) {
        while(1) tk_dly_tsk(1000);
    }

    while(1) {
        /* Wait for intervention trigger */
        ercd = tk_wai_sem(haptic_semaphore, TMO_FEVR);
        if (ercd != E_OK) continue;

        /* Get latest classification */
        if (get_classification_result(&classification) == FSP_SUCCESS) {
            if (!haptic_state.pattern_active && classification.intervention_needed) {
                start_intervention_pattern(classification.dominant_state);
            }
        }

        /* Process active pattern at 20Hz */
        while (haptic_state.pattern_active) {
            process_pattern_step();
            tk_dly_tsk(PATTERN_RESOLUTION_MS);
        }
    }
}

/**
 * @brief Manual trigger for specific haptic pattern
 */
fsp_err_t trigger_haptic_pattern(cognitive_state_type_t state)
{
    if (!haptic_initialized) return FSP_ERR_NOT_INITIALIZED;

    if (haptic_state.pattern_active) {
        haptic_state.pattern_active = false;
        set_motor_intensity(0, 0);
    }

    start_intervention_pattern(state);
    return FSP_SUCCESS;
}

/**
 * @brief Get haptic system statistics
 */
fsp_err_t get_haptic_statistics(uint32_t *total_interventions, float *effectiveness, bool *is_active)
{
    if (total_interventions) *total_interventions = haptic_state.total_interventions;
    if (effectiveness) *effectiveness = haptic_state.effectiveness_score;
    if (is_active) *is_active = haptic_state.pattern_active;

    return FSP_SUCCESS;
}
