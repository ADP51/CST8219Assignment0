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
		scanf(" %c", &response);

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
	rg->animationName = (char*)malloc(64 * sizeof(char));
	printf("Enter the name of the Animation:");
	scanf(" %s", rg->animationName);

	rg->frames = NULL;
}

void InsertFrame(Animation* rg)
{
	struct Frame* newFrame = (struct Frame*)malloc(sizeof(struct Frame));
	newFrame->frameName = (char*)malloc(64 * sizeof(char));
	printf("Insert a Frame in the Animation\n");
	printf("Please enter the Frame frameName: \n");
	scanf(" %s", newFrame->frameName);

	if (rg->frames == NULL) {
		newFrame->pNext = NULL;
		rg->frames = newFrame;
	}
	else {
		newFrame->pNext = rg->frames;
		rg->frames = newFrame;
	}
}

void DeleteFrame(Animation* rg)
{
	printf("Deleting the last frame in the Animation.\n");

	struct Frame* current = rg->frames;
	struct Frame* next = rg->frames->pNext;


	if (current == NULL) {
		printf("List is empty.");
	}
	else if (rg->frames->pNext == NULL) {
		free(rg->frames);
	}

	if (current != NULL) {
		while (next->pNext != NULL) {
			current = next;
			next = next->pNext;
		}
		current->pNext = NULL;
		free(next);
	}
}

void EditFrame(Animation* rg)
{
	struct Frame* current = rg->frames;
	printf("Edit a Frame in the Animation\n");

	int counter = 0;
	int index = 0;

	if (current != NULL) {
		counter++;
		while (current->pNext != NULL) {
			current = current->pNext;
			counter++;
		}
	}

	printf("There are %d Frame(s) in the list. Please specify the index (<= %d) to edit at : ", counter, (counter - 1));
	scanf(" %d", &index);

	if (index < counter) {
		struct Frame* head = rg->frames;
		for (int i = 0; i < index; i++) {
			head = head->pNext;
		}
		char* newName = (char*)malloc(64);
		printf("The name of this Frame is %s. What do you wish to replace it with?\n", head->frameName);
		scanf(" %s", newName);
		head->frameName = newName;
	}
}

void ReportAnimation(Animation* rg)
{
	int counter = 0;
	struct Frame* head = rg->frames;
	printf("Animation name is: %s\n", rg->animationName);
	while (head != NULL) {
		printf("Image #%d, file name = %s\n", counter, head->frameName);
		head = head->pNext;
		counter++;
	}
}

void CleanUp(Animation* rg)
{
	struct Frame* head = rg->frames;
	struct Frame* temp;

	while (head != NULL) {
		printf("Cleaning.");
		temp = head;
		head = head->pNext;
		free(temp->frameName);
		free(temp);
	}
	free(rg->animationName);
}