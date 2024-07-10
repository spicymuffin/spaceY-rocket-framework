#ifndef ROCKETSTATE_H
#define ROCKETSTATE_H

enum RocketState
{
    DOCKED,
    PRIMED,
    LAUNCH_COUNTDOWN,
    FIRST_STAGE_BURN,
    DECOUPLING,
    SECOND_STAGE_BURN,
    FREEFALL,
    PARACHUTE_DEPLOYED,
    LANDED,
};

extern bool flag_freefall;
extern uint32_t freefall_start_ts;

#endif