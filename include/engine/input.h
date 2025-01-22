#ifndef BBC0DE3D_44BF_4F09_9B2A_797A6321B577
#define BBC0DE3D_44BF_4F09_9B2A_797A6321B577

void InitInput();
void CloseInput();
void UpdateInput();

void MapInputToAction(const char *input, const char *action);
void MapInputsToActions_ht(void *newInputActions);

int IsActionPressed(const char *action);
int IsActionDown(const char *action);
int IsActionReleased(const char *action);
float GetActionPosition(const char *action);

#endif /* BBC0DE3D_44BF_4F09_9B2A_797A6321B577 */
