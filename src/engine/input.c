#include <engine/input.h>
#include <tmx_utils.h>
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const float DEADZONE = 0;

typedef struct {
    float position, lastPosition;
    int numPositionInputs;
    int pressed, down, released;
} ActionState;

void *inputActionMap;
void *actionStates;
void *keyEnum, *padEnum;

void FreeInputAction(void *val, const char *key) {
}

void FreeEnum(unsigned *e, const char *key) {
    free(e);
}

void FreeActionState(ActionState *actionState, const char *key) {
    free(actionState);
}

void CloseInput() {
    if (inputActionMap)
        free_hashtable(inputActionMap, FreeInputAction);
    inputActionMap = NULL;
    if (actionStates)
        free_hashtable(actionStates, (hashtable_entry_deallocator)FreeActionState);
    actionStates = NULL;
    if (keyEnum)
        free_hashtable(keyEnum, (hashtable_entry_deallocator)FreeEnum);
    keyEnum = NULL;
    if (padEnum)
        free_hashtable(padEnum, (hashtable_entry_deallocator)FreeEnum);
    padEnum = NULL;
}

#define addEnum(ht, prefix, e) { \
    unsigned *ep = malloc(sizeof(unsigned)); \
    *ep = prefix##e; \
    hashtable_set(ht, #e, ep, NULL); \
}

void InitInput() {
    if (inputActionMap || actionStates)
        CloseInput();
    inputActionMap = mk_hashtable(64);
    actionStates = mk_hashtable(64);
    if (!keyEnum) {
        keyEnum = mk_hashtable(128);
        addEnum(keyEnum, , KEY_APOSTROPHE      ); // Key: '
        addEnum(keyEnum, , KEY_COMMA           ); // Key: ,
        addEnum(keyEnum, , KEY_MINUS           ); // Key: -
        addEnum(keyEnum, , KEY_PERIOD          ); // Key: .
        addEnum(keyEnum, , KEY_SLASH           ); // Key: /
        addEnum(keyEnum, , KEY_ZERO            ); // Key: 0
        addEnum(keyEnum, , KEY_ONE             ); // Key: 1
        addEnum(keyEnum, , KEY_TWO             ); // Key: 2
        addEnum(keyEnum, , KEY_THREE           ); // Key: 3
        addEnum(keyEnum, , KEY_FOUR            ); // Key: 4
        addEnum(keyEnum, , KEY_FIVE            ); // Key: 5
        addEnum(keyEnum, , KEY_SIX             ); // Key: 6
        addEnum(keyEnum, , KEY_SEVEN           ); // Key: 7
        addEnum(keyEnum, , KEY_EIGHT           ); // Key: 8
        addEnum(keyEnum, , KEY_NINE            ); // Key: 9
        addEnum(keyEnum, , KEY_SEMICOLON       ); // Key: ;
        addEnum(keyEnum, , KEY_EQUAL           ); // Key: =
        addEnum(keyEnum, , KEY_A               ); // Key: A | a
        addEnum(keyEnum, , KEY_B               ); // Key: B | b
        addEnum(keyEnum, , KEY_C               ); // Key: C | c
        addEnum(keyEnum, , KEY_D               ); // Key: D | d
        addEnum(keyEnum, , KEY_E               ); // Key: E | e
        addEnum(keyEnum, , KEY_F               ); // Key: F | f
        addEnum(keyEnum, , KEY_G               ); // Key: G | g
        addEnum(keyEnum, , KEY_H               ); // Key: H | h
        addEnum(keyEnum, , KEY_I               ); // Key: I | i
        addEnum(keyEnum, , KEY_J               ); // Key: J | j
        addEnum(keyEnum, , KEY_K               ); // Key: K | k
        addEnum(keyEnum, , KEY_L               ); // Key: L | l
        addEnum(keyEnum, , KEY_M               ); // Key: M | m
        addEnum(keyEnum, , KEY_N               ); // Key: N | n
        addEnum(keyEnum, , KEY_O               ); // Key: O | o
        addEnum(keyEnum, , KEY_P               ); // Key: P | p
        addEnum(keyEnum, , KEY_Q               ); // Key: Q | q
        addEnum(keyEnum, , KEY_R               ); // Key: R | r
        addEnum(keyEnum, , KEY_S               ); // Key: S | s
        addEnum(keyEnum, , KEY_T               ); // Key: T | t
        addEnum(keyEnum, , KEY_U               ); // Key: U | u
        addEnum(keyEnum, , KEY_V               ); // Key: V | v
        addEnum(keyEnum, , KEY_W               ); // Key: W | w
        addEnum(keyEnum, , KEY_X               ); // Key: X | x
        addEnum(keyEnum, , KEY_Y               ); // Key: Y | y
        addEnum(keyEnum, , KEY_Z               ); // Key: Z | z
        addEnum(keyEnum, , KEY_LEFT_BRACKET    ); // Key: [
        addEnum(keyEnum, , KEY_BACKSLASH       ); // Key: '\'
        addEnum(keyEnum, , KEY_RIGHT_BRACKET   ); // Key: ]
        addEnum(keyEnum, , KEY_GRAVE           ); // Key: `
        addEnum(keyEnum, , KEY_SPACE           ); // Key: Space
        addEnum(keyEnum, , KEY_ESCAPE          ); // Key: Esc
        addEnum(keyEnum, , KEY_ENTER           ); // Key: Enter
        addEnum(keyEnum, , KEY_TAB             ); // Key: Tab
        addEnum(keyEnum, , KEY_BACKSPACE       ); // Key: Backspace
        addEnum(keyEnum, , KEY_INSERT          ); // Key: Ins
        addEnum(keyEnum, , KEY_DELETE          ); // Key: Del
        addEnum(keyEnum, , KEY_RIGHT           ); // Key: Cursor right
        addEnum(keyEnum, , KEY_LEFT            ); // Key: Cursor left
        addEnum(keyEnum, , KEY_DOWN            ); // Key: Cursor down
        addEnum(keyEnum, , KEY_UP              ); // Key: Cursor up
        addEnum(keyEnum, , KEY_PAGE_UP         ); // Key: Page up
        addEnum(keyEnum, , KEY_PAGE_DOWN       ); // Key: Page down
        addEnum(keyEnum, , KEY_HOME            ); // Key: Home
        addEnum(keyEnum, , KEY_END             ); // Key: End
        addEnum(keyEnum, , KEY_CAPS_LOCK       ); // Key: Caps lock
        addEnum(keyEnum, , KEY_SCROLL_LOCK     ); // Key: Scroll down
        addEnum(keyEnum, , KEY_NUM_LOCK        ); // Key: Num lock
        addEnum(keyEnum, , KEY_PRINT_SCREEN    ); // Key: Print screen
        addEnum(keyEnum, , KEY_PAUSE           ); // Key: Pause
        addEnum(keyEnum, , KEY_F1              ); // Key: F1
        addEnum(keyEnum, , KEY_F2              ); // Key: F2
        addEnum(keyEnum, , KEY_F3              ); // Key: F3
        addEnum(keyEnum, , KEY_F4              ); // Key: F4
        addEnum(keyEnum, , KEY_F5              ); // Key: F5
        addEnum(keyEnum, , KEY_F6              ); // Key: F6
        addEnum(keyEnum, , KEY_F7              ); // Key: F7
        addEnum(keyEnum, , KEY_F8              ); // Key: F8
        addEnum(keyEnum, , KEY_F9              ); // Key: F9
        addEnum(keyEnum, , KEY_F10             ); // Key: F10
        addEnum(keyEnum, , KEY_F11             ); // Key: F11
        addEnum(keyEnum, , KEY_F12             ); // Key: F12
        addEnum(keyEnum, , KEY_LEFT_SHIFT      ); // Key: Shift left
        addEnum(keyEnum, , KEY_LEFT_CONTROL    ); // Key: Control left
        addEnum(keyEnum, , KEY_LEFT_ALT        ); // Key: Alt left
        addEnum(keyEnum, , KEY_LEFT_SUPER      ); // Key: Super left
        addEnum(keyEnum, , KEY_RIGHT_SHIFT     ); // Key: Shift right
        addEnum(keyEnum, , KEY_RIGHT_CONTROL   ); // Key: Control right
        addEnum(keyEnum, , KEY_RIGHT_ALT       ); // Key: Alt right
        addEnum(keyEnum, , KEY_RIGHT_SUPER     ); // Key: Super right
        addEnum(keyEnum, , KEY_KB_MENU         ); // Key: KB menu
        addEnum(keyEnum, , KEY_KP_0            ); // Key: Keypad 0
        addEnum(keyEnum, , KEY_KP_1            ); // Key: Keypad 1
        addEnum(keyEnum, , KEY_KP_2            ); // Key: Keypad 2
        addEnum(keyEnum, , KEY_KP_3            ); // Key: Keypad 3
        addEnum(keyEnum, , KEY_KP_4            ); // Key: Keypad 4
        addEnum(keyEnum, , KEY_KP_5            ); // Key: Keypad 5
        addEnum(keyEnum, , KEY_KP_6            ); // Key: Keypad 6
        addEnum(keyEnum, , KEY_KP_7            ); // Key: Keypad 7
        addEnum(keyEnum, , KEY_KP_8            ); // Key: Keypad 8
        addEnum(keyEnum, , KEY_KP_9            ); // Key: Keypad 9
        addEnum(keyEnum, , KEY_KP_DECIMAL      ); // Key: Keypad .
        addEnum(keyEnum, , KEY_KP_DIVIDE       ); // Key: Keypad /
        addEnum(keyEnum, , KEY_KP_MULTIPLY     ); // Key: Keypad *
        addEnum(keyEnum, , KEY_KP_SUBTRACT     ); // Key: Keypad -
        addEnum(keyEnum, , KEY_KP_ADD          ); // Key: Keypad +
        addEnum(keyEnum, , KEY_KP_ENTER        ); // Key: Keypad Enter
        addEnum(keyEnum, , KEY_KP_EQUAL        ); // Key: Keypad =
        addEnum(keyEnum, , KEY_BACK            ); // Key: Android back button
        addEnum(keyEnum, , KEY_MENU            ); // Key: Android menu button
        addEnum(keyEnum, , KEY_VOLUME_UP       ); // Key: Android volume up button
        addEnum(keyEnum, , KEY_VOLUME_DOWN     ); // Key: Android volume down button
    }
    if (!padEnum) {
        padEnum = mk_hashtable(32);

        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_FACE_UP       );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_FACE_RIGHT    );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_FACE_DOWN     );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_FACE_LEFT     );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_FACE_UP      );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_FACE_RIGHT   );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_FACE_DOWN    );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_FACE_LEFT    );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_TRIGGER_1     );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_TRIGGER_2     );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_TRIGGER_1    );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_TRIGGER_2    );
        addEnum(padEnum, GAMEPAD_, BUTTON_MIDDLE_LEFT        );
        addEnum(padEnum, GAMEPAD_, BUTTON_MIDDLE             );
        addEnum(padEnum, GAMEPAD_, BUTTON_MIDDLE_RIGHT       );
        addEnum(padEnum, GAMEPAD_, BUTTON_LEFT_THUMB         );
        addEnum(padEnum, GAMEPAD_, BUTTON_RIGHT_THUMB        );

        addEnum(padEnum, GAMEPAD_, AXIS_LEFT_X       );
        addEnum(padEnum, GAMEPAD_, AXIS_LEFT_Y       );
        addEnum(padEnum, GAMEPAD_, AXIS_RIGHT_X      );
        addEnum(padEnum, GAMEPAD_, AXIS_RIGHT_Y      );
        addEnum(padEnum, GAMEPAD_, AXIS_LEFT_TRIGGER );
        addEnum(padEnum, GAMEPAD_, AXIS_RIGHT_TRIGGER);
    }
}

ActionState* GetOrMakeActionState(const char *action) {
    ActionState *actionState = hashtable_get(actionStates, action);
    if (!actionState) {
        actionState = malloc(sizeof(ActionState));
        *actionState = (ActionState){0};
        hashtable_set(actionStates, action, actionState, (hashtable_entry_deallocator)FreeActionState);
    }
    return actionState;
}

void MapInputToAction(const char *input, const char *action) {
    ActionState *actionState = GetOrMakeActionState(action);
    hashtable_set(inputActionMap, input, actionState, FreeInputAction);
}

void MapEachInputToAction(const char *action, void *_, const char *input) {
    MapInputToAction(input, action);
}

void MapInputsToActions_ht(void *newInputActions) {
    hashtable_foreach(newInputActions, (hashtable_foreach_functor)MapEachInputToAction, NULL);
}

bool IsPositionDown(float position) {
    return fabs(position) > DEADZONE;
}

void ActionStatePreUpdate(ActionState *state, void *_, const char *action) {
    state->lastPosition = state->position;
    state->position = 0;
    state->numPositionInputs = 0;
}

void ActionStateUpdate(ActionState *state, float inputPosition) {
    if (IsPositionDown(inputPosition)) {
        state->position += inputPosition;
        ++state->numPositionInputs;
    }
}

void ActionStatePostUpdate(ActionState *state, void *_, const char *action) {
    if (state->numPositionInputs > 1)
        state->position /= state->numPositionInputs;

    if (IsPositionDown(state->position)) {
        state->down = true;
        state->pressed = !IsPositionDown(state->lastPosition);
        state->released = false;
    } else {
        state->down = false;
        state->pressed = false;
        state->released = IsPositionDown(state->lastPosition);
    }
}

void UpdateInputActionState(ActionState *state, void *userdata, const char *inString) {
    char inType = *inString;
    switch (inType) {
        case 'K': {
            char negKey[32] = "KEY_", posKey[32] = "KEY_";
            int nTokens = sscanf(inString, "KAXIS_-%27[^+]+%27s", negKey + 4, posKey + 4);
            if (nTokens == 2) {
                unsigned *nk = (unsigned*)hashtable_get(keyEnum, negKey);
                unsigned *pk = (unsigned*)hashtable_get(keyEnum, posKey);
                if (nk && pk)
                    ActionStateUpdate(state, IsKeyDown(*pk) - IsKeyDown(*nk));
            } else {
                unsigned *k = (unsigned*)hashtable_get(keyEnum, inString);
                if (k)
                    ActionStateUpdate(state, IsKeyDown(*k));
            }
        } break;
        case 'P': {
            int padIndex;
            char padInput[64];
            int nTokens = sscanf(inString, "P%d_%63s", &padIndex, padInput);
            if (nTokens < 2 || !IsGamepadAvailable(padIndex))
                break;

            switch (*padInput) {
                case 'A': {
                    unsigned* axis = (unsigned*)hashtable_get(padEnum, padInput);
                    if (axis)
                        ActionStateUpdate(state, GetGamepadAxisMovement(padIndex, *axis));
                } break;
                case 'B': {
                    char negKey[32] = "BUTTON_", posKey[32] = "BUTTON_";
                    int nTokens = sscanf(padInput, "BAXIS_-%24[^+]+%24s", negKey + 7, posKey + 7);
                    if (nTokens == 2) {
                        unsigned *nk = (unsigned*)hashtable_get(padEnum, negKey);
                        unsigned *pk = (unsigned*)hashtable_get(padEnum, posKey);
                        if (nk && pk)
                            ActionStateUpdate(state,
                                IsGamepadButtonDown(padIndex, *pk)
                                - IsGamepadButtonDown(padIndex, *nk));
                    } else {
                        unsigned *button = (unsigned*)hashtable_get(padEnum, padInput);
                        if (button)
                            ActionStateUpdate(state, IsGamepadButtonDown(padIndex, *button));
                    }
                } break;
            }

        } break;

        // TODO as needed
        // case 'M': {
        // } break;
        // case 'T': {
        // } break;
    }
}

void UpdateInput() {
    hashtable_foreach(actionStates, (hashtable_foreach_functor)ActionStatePreUpdate, NULL);
    hashtable_foreach(inputActionMap, (hashtable_foreach_functor)UpdateInputActionState, NULL);
    hashtable_foreach(actionStates, (hashtable_foreach_functor)ActionStatePostUpdate, NULL);
}

ActionState *GetActionState(const char *action) {
    return hashtable_get(actionStates, action);
}

int IsActionPressed(const char *action) {
    ActionState *state = GetActionState(action);
    return state ? state->pressed : 0;
}

int IsActionDown(const char *action) {
    ActionState *state = GetActionState(action);
    return state ? state->down : 0;
}

int IsActionReleased(const char *action) {
    ActionState *state = GetActionState(action);
    return state ? state->released : 0;
}

float GetActionPosition(const char *action) {
    ActionState *state = GetActionState(action);
    return state ? state->position : 0;
}