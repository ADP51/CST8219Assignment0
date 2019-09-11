// ass0.c
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC // need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
typedef enum { FALSE = 0, TRUE } BOOL;
struct Frame {
	char* frameName;
	struct Frame* pNext;
};
typedef struct {
	char* animationName;
	struct Frame* frames;
}Animation;
// Forward declarations
void InitAnimation(Animation*);
void InsertFrame(Animation*);
void DeleteFrame(Animation*);
void EditFrame(Animation*);
void ReportAnimation(Animation*);
void CleanUp(Animation*);
int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	Animation RG;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	InitAnimation(&RG);
	while (RUNNING)
	{
		printf("MENU\n 1. Insert a Frame at the front\n 2. Delete last Frame\n 3. Edit a Frame\n 4. Report the Animation\n 5. Quit\n");
		scanf("%c", &response);

		switch (response)
		{
		case '1':InsertFrame(&RG); break;
		case '2':DeleteFrame(&RG); break;
		case '3':EditFrame(&RG); break;
		case '4':ReportAnimation(&RG); break;
		case '5':RUNNING = FALSE; CleanUp(&RG); break;
		default:printf("Please enter a valid option\n");
		}
	}
	return 0;
}

void InitAnimation(Animation* rg)
{
	struct Frame* head = NULL;
	head = (struct Frame*)malloc(sizeof(struct Frame));

	head->frameName = "Initializing Frames.";
	head->pNext = NULL;

	rg->animationName = "This Animation of Mine.";
	rg->frames = head;
}

void InsertFrame(Animation* rg)
{	
	char* frameName = (char *)malloc(50);
	printf("Enter name of the frame you would like to add: \n");
	scanf("%s", frameName);
	struct Frame* newFrame = NULL;
	newFrame = malloc(sizeof(struct Frame));

	newFrame->pNext = rg->frames;
	newFrame->frameName = frameName;
	rg->frames = newFrame;
}

void DeleteFrame(Animation* rg)
{
	printf("Deleting the last frame in the Animation.\n");
	
	struct Frame * current = NULL;
	struct Frame * next = NULL;
	
	current = rg->frames;
	next = rg->frames->pNext;

	if (rg->frames->pNext == NULL) {
		free(rg->frames);
	}

	while (next->pNext != NULL) {
		current = next;
		next = next->pNext;
	}

	free(next);
	current->pNext = NULL;
}

void EditFrame(Animation* rg)
{
	struct Frame* current = rg->frames->frameName;
	char* frameName = (char *)malloc(50);
	printf("Enter the name of the Frame that you want to Edit.\n");
	scanf("%s", frameName);

	while (current->frameName != frameName) {
		current = current->pNext;
		if (current->pNext == NULL) {
			printf("Frame with the name: %s not found.", frameName);
			break;
		}
	}

	char* newName = (char*)malloc(50);
	printf("Please enter the new name you would like this frame to have: \n");
	scanf("%s", newName);

	current->frameName = newName;

	printf("Frame name is now: %s\n", current->frameName);
}

void ReportAnimation(Animation* rg)
{
	struct Frame* head = rg->frames;

	while (head != NULL) {
		printf("Frame Name: %s\n", head->frameName);
		head = head->pNext;
	}
}

void CleanUp(Animation* rg)
{

}