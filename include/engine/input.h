#ifndef BBC0DE3D_44BF_4F09_9B2A_797A6321B577
#define BBC0DE3D_44BF_4F09_9B2A_797A6321B577

typedef struct {
    float position, lastPosition;
    int pressed, down, released;
} ActionState;

void InitInput();
void CloseInput();
void UpdateInput();

void MapInputToAction(const char *input, const char *action);
ActionState* GetActionState(const char *action);

#endif /* BBC0DE3D_44BF_4F09_9B2A_797A6321B577 */
