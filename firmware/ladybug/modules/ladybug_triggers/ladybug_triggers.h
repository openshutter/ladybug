
#ifndef LADYBUG_TRIGGERS_H
#define LADYBUG_TRIGGERS_H

#define TRG0_TIP  PIN_D0
#define TRG0_RING PIN_D1

/**
 * Fires a trigger in a typical half-press -> full-press sequence
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_TIP
 * @param preshoot miliseconds to fire TRGn_RING before TRGn_TIP
 */
extern int trigger_sync(int trigger, int duration, int preshoot);

/**
 * Fires just TRGn_RING ("half-press" / preshoot).
 * Caller is responsible for ensuring TRGn_TIP is overlapped with this pulse
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_RING
 */
extern int trigger_ring_sync(int trigger, int duration);

/**
 * Fires just TRGn_TIP ("full-press" / shoot)
 *
 * @param trigger trigger index to fire
 * @param duration miliseconds to fire TRGn_TIP
 */
extern int trigger_tip_sync(int trigger, int duration);

#endif /* LADYBUG_TRIGGERS_H */
