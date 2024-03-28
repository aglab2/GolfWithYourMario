// lll_rotating_hex_flame.inc.c

void bhv_lll_rotating_hex_flame_loop(void) {
    cur_obj_set_pos_relative(o->parentObj, o->oLllRotatingHexFlameRelativePosX, o->oLllRotatingHexFlameRelativePosY, o->oLllRotatingHexFlameRelativePosZ);

    if (o->parentObj->oAction == LLL_FIRE_BAR_ACT_REMOVE_FLAMES) {
        obj_mark_for_deletion(o);
    }
}

void fire_bar_spawn_flames(s16 yaw) {
    struct Object *flameObj;
    s32 i;
    f32 xOffset = sins(yaw) * 200.0f;
    f32 zOffset = coss(yaw) * 200.0f;
    s32 amt = 3;
    for (i = 0; i < amt; i++) {
        flameObj = spawn_object(o, MODEL_RED_FLAME, bhvLllRotatingHexFlame);
        flameObj->oLllRotatingHexFlameRelativePosX += xOffset;
        flameObj->oLllRotatingHexFlameRelativePosY = 30.f + i * 50.f;
        flameObj->oLllRotatingHexFlameRelativePosZ += zOffset;
        obj_scale(flameObj, 6.0f);
        xOffset += sins(yaw) * 150.0f;
        zOffset += coss(yaw) * 150.0f;
    }
}

void fire_bar_act_inactive(void) {
    if (o->oDistanceToMario < o->oDrawingDistance) {
        o->oAction = LLL_FIRE_BAR_ACT_SPAWN_FLAMES;
    }
}

void fire_bar_act_spawn_flames(void) {
    fire_bar_spawn_flames(0 + 0x10000 / 3 * o->oBehParams2ndByte);
    fire_bar_spawn_flames(-0x8000 + 0x10000 / 3 * o->oBehParams2ndByte);
    o->oAngleVelYaw = 0;
    o->oMoveAngleYaw = 0;
    o->oAction = LLL_FIRE_BAR_ACT_ACTIVE;
}

void fire_bar_act_active(void) {
    o->oAngleVelYaw = -0x100;
    o->oMoveAngleYaw += o->oAngleVelYaw;
    if (o->oDistanceToMario > o->oDrawingDistance + 200.0f) {
        o->oAction = LLL_FIRE_BAR_ACT_REMOVE_FLAMES;
    }
}

void fire_bar_act_remove_flames(void) {
    o->oAction = LLL_FIRE_BAR_ACT_INACTIVE;
}

ObjActionFunc sRotatingCwFireBarsActions[] = {
    fire_bar_act_inactive,
    fire_bar_act_spawn_flames,
    fire_bar_act_active,
    fire_bar_act_remove_flames,
};

void bhv_lll_rotating_block_fire_bars_loop(void) {
    cur_obj_call_action_function(sRotatingCwFireBarsActions);
    load_object_collision_model();
}
