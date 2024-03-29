#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

// Screen dimensions
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 1000

// Constants for array manipulation
#define MAX_ARRAY_SIZE 10
#define MIN_ARRAY_SIZE 1
#define ELEMENT_WIDTH 60
#define ELEMENT_HEIGHT 60
#define ELEMENT_SPACING 30

// Button dimensions
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50

// Enumeration for different program states
enum ProgramState {
    NORMAL,
    ADD_OPTIONS,
    REMOVE_OPTIONS
};

// Function prototypes
void shuffleArray(int array[], int size);
void bubbleSort(int array[], int size);



int main(void) {
     // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Array Example");

    // Initialize array and its size
    int array[MAX_ARRAY_SIZE];
    int arraySize = 5; // Start with 5 elements
    int maxElementIndex = -1; // Index of the maximum element in the array

    // Initialize array elements with random values between 1 and 25
    for (int i = 0; i < arraySize; i++) {
        array[i] = GetRandomValue(1, 25);
    }

     // Button positions
    Rectangle addButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 - 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 250, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle shuffleButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 250, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle removeButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 + 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 250, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle addEndButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 - 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 350, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle addStartButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 + 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 350, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle addMiddleButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 350, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle removeEndButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 - 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 400, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle removeStartButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 + 300, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 400, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle maxElementButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) - 20, 20, BUTTON_WIDTH, BUTTON_HEIGHT};
    Rectangle sortButton = {(float)(SCREEN_WIDTH - BUTTON_WIDTH) / 2 + 600, (float)(SCREEN_HEIGHT - BUTTON_HEIGHT) / 2 + 250, BUTTON_WIDTH, BUTTON_HEIGHT};
    
    // Initial button color
    Color buttonColor = LIGHTGRAY;

    // Program state
    enum ProgramState state = NORMAL;

    // Timer variables
    float colorChangeTimer = 0.0f;
    

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        Vector2 mousePos = GetMousePosition();

        // Check if the mouse is over the buttons
        bool overAddButton = CheckCollisionPointRec(mousePos, addButton);
        bool overShuffleButton = CheckCollisionPointRec(mousePos, shuffleButton);
        bool overRemoveButton = CheckCollisionPointRec(mousePos, removeButton);
        bool overAddEndButton = CheckCollisionPointRec(mousePos, addEndButton);
        bool overAddStartButton = CheckCollisionPointRec(mousePos, addStartButton);
        bool overAddMiddleButton = CheckCollisionPointRec(mousePos, addMiddleButton);
        bool overRemoveEndButton = CheckCollisionPointRec(mousePos, removeEndButton);
        bool overRemoveStartButton = CheckCollisionPointRec(mousePos, removeStartButton);
        bool overMaxElementButton = CheckCollisionPointRec(mousePos, maxElementButton);

        // Check if the buttons are clicked
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            switch (state) {
                case NORMAL:
                    if (overAddButton) {
                        state = ADD_OPTIONS;
                    } else if (overShuffleButton) {
                        shuffleArray(array, arraySize);
                    } else if (overRemoveButton) {
                        state = REMOVE_OPTIONS;
                    } else if (overMaxElementButton) {
                        // Find and display the max element
                        int maxElement = INT_MIN;
                        for (int i = 0; i < arraySize; i++) {
                            if (array[i] > maxElement) {
                                maxElement = array[i];
                                maxElementIndex = i;
                            }
                        }
                        
                        // Reset the timer
                        colorChangeTimer = 0.0f;

                    }else if (CheckCollisionPointRec(mousePos, sortButton)) {
                        // Sort the array using Bubble Sort
                        bubbleSort(array, arraySize);
                    }
                    break;
                case ADD_OPTIONS:
                    if (overAddEndButton) {
                        if (arraySize < MAX_ARRAY_SIZE) {
                            array[arraySize++] = GetRandomValue(1, 25);
                        }
                        state = NORMAL;
                    } else if (overAddStartButton) {
                        if (arraySize < MAX_ARRAY_SIZE) {
                            // Shift elements to the right
                            for (int i = arraySize; i > 0; i--) {
                                array[i] = array[i - 1];
                            }
                            array[0] = GetRandomValue(1, 25);
                            arraySize++;
                        }
                        state = NORMAL;
                    } else if (overAddMiddleButton) {
                        if (arraySize < MAX_ARRAY_SIZE) {
                            // Shift elements to the right
                            for (int i = arraySize; i > arraySize / 2; i--) {
                                array[i] = array[i - 1];
                            }
                            array[arraySize / 2] = GetRandomValue(1, 25);
                            arraySize++;
                        }
                        state = NORMAL;
                    }
                    break;
                case REMOVE_OPTIONS:
                    if (overRemoveEndButton && arraySize > MIN_ARRAY_SIZE) {
                        // Remove the last element from the array
                        arraySize--;
                        state = NORMAL;
                    } else if (overRemoveStartButton && arraySize > MIN_ARRAY_SIZE) {
                        // Shift elements to the left
                        for (int i = 0; i < arraySize - 1; i++) {
                            array[i] = array[i + 1];
                        }
                        arraySize--;
                        state = NORMAL;
                    }
                    break;
            }
        }

        // Update the timer
        colorChangeTimer += GetFrameTime();

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display the array elements and arrows
        float arrayPosX = (float)(SCREEN_WIDTH - (arraySize * (ELEMENT_WIDTH + ELEMENT_SPACING) - ELEMENT_SPACING)) / 2;
        float arrayPosY = (float)SCREEN_HEIGHT / 2 - ELEMENT_HEIGHT / 2;

        for (int i = 0; i < arraySize; i++) {
       // Draw arrows (lines connecting the top and bottom of rectangles)
            if (i < arraySize - 1) {
                Vector2 startTop = {(float)(arrayPosX + (i + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING)), arrayPosY + 10};
                Vector2 endTop = {(float)(arrayPosX + (i + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING), arrayPosY + 10};
                DrawLineEx(startTop, endTop, 2, RED);
                DrawTriangle(endTop, (Vector2){endTop.x - 5, endTop.y - 5}, (Vector2){endTop.x - 5, endTop.y + 5}, RED);

                Vector2 startBottom = {(float)(arrayPosX + (i + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING)), arrayPosY + ELEMENT_HEIGHT - 10};
                Vector2 endBottom = {(float)(arrayPosX + (i + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING), arrayPosY + ELEMENT_HEIGHT - 10};
                DrawLineEx(startBottom, endBottom, 2, BLUE);
                DrawTriangle(startBottom, (Vector2){startBottom.x + 5, startBottom.y + 5}, (Vector2){startBottom.x + 5, startBottom.y - 5}, BLUE);
}
            // Draw rectangles
            if (i == maxElementIndex) {
    
                DrawRectangle(arrayPosX + i * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING, arrayPosY, ELEMENT_WIDTH, ELEMENT_HEIGHT, RED);
                    } else {
                DrawRectangle(arrayPosX + i * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING, arrayPosY, ELEMENT_WIDTH, ELEMENT_HEIGHT, DARKGRAY);
        }

            DrawText(TextFormat("%d", array[i]), arrayPosX + i * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING + 10, arrayPosY + 10, 20, WHITE);
        }

        // Draw buttons based on the state
        switch (state) {
            case NORMAL:
                DrawRectangleRec(addButton, overAddButton ? DARKGRAY : buttonColor);
                DrawText("Add Element", addButton.x + 10, addButton.y + 10, 20, WHITE);

                DrawRectangleRec(removeButton, overRemoveButton ? DARKGRAY : buttonColor);
                DrawText("Remove Element", removeButton.x + 10, removeButton.y + 10, 20, WHITE);
                DrawRectangleRec(sortButton, CheckCollisionPointRec(mousePos, sortButton) ? DARKGRAY : buttonColor);
                DrawText("Sort Array", sortButton.x + 10, sortButton.y + 10, 20, WHITE);
                break;
            case ADD_OPTIONS:
                DrawRectangleRec(addEndButton, overAddEndButton ? DARKGRAY : buttonColor);
                DrawText("Add at End", addEndButton.x + 10, addEndButton.y + 10, 20, WHITE);

                DrawRectangleRec(addStartButton, overAddStartButton ? DARKGRAY : buttonColor);
                DrawText("Add at Start", addStartButton.x + 10, addStartButton.y + 10, 20, WHITE);

                DrawRectangleRec(addMiddleButton, overAddMiddleButton ? DARKGRAY : buttonColor);
                DrawText("Add in Middle", addMiddleButton.x + 10, addMiddleButton.y + 10, 20, WHITE);
                break;
            case REMOVE_OPTIONS:
                DrawRectangleRec(removeEndButton, overRemoveEndButton ? DARKGRAY : buttonColor);
                DrawText("Remove at End", removeEndButton.x + 10, removeEndButton.y + 10, 20, WHITE);

                DrawRectangleRec(removeStartButton, overRemoveStartButton ? DARKGRAY : buttonColor);
                DrawText("Remove at Start", removeStartButton.x + 10, removeStartButton.y + 10, 20, WHITE);
                break;
        }

        // Draw Max Element button
        DrawRectangleRec(maxElementButton, overMaxElementButton ? DARKGRAY : buttonColor);
        DrawText("Max Element", maxElementButton.x + 10, maxElementButton.y + 10, 20, WHITE);

        // Draw Shuffle button
        DrawRectangleRec(shuffleButton, overShuffleButton ? DARKGRAY : buttonColor);
        DrawText("Shuffle Array", shuffleButton.x + 10, shuffleButton.y + 10, 20, WHITE);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}

void shuffleArray(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
// Function to swap two elements in the array
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort algorithm with step-by-step display
void bubbleSort(int array[], int size) {
    float startTime = GetTime();
    float delay = 1.0f;  // Set a larger delay for a slower animation

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                // Swap elements if they are in the wrong order
                swap(&array[j], &array[j + 1]);

                // Display the array after each swap
                BeginDrawing();
                ClearBackground(RAYWHITE);

                // Draw arrows and the array after each swap
                float arrayPosX = (float)(SCREEN_WIDTH - (size * (ELEMENT_WIDTH + ELEMENT_SPACING) - ELEMENT_SPACING)) / 2;
                float arrayPosY = (float)SCREEN_HEIGHT / 2 - ELEMENT_HEIGHT / 2;

                for (int k = 0; k < size; k++) {
                    // Draw arrows (lines connecting the top and bottom of rectangles)
                    if (k < size - 1) {
                        Vector2 startTop = {(float)(arrayPosX + (k + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING)), arrayPosY + 10};
                        Vector2 endTop = {(float)(arrayPosX + (k + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING), arrayPosY + 10};
                        DrawLineEx(startTop, endTop, 2, RED);
                        DrawTriangle(endTop, (Vector2){endTop.x - 5, endTop.y - 5}, (Vector2){endTop.x - 5, endTop.y + 5}, RED);

                        Vector2 startBottom = {(float)(arrayPosX + (k + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING)), arrayPosY + ELEMENT_HEIGHT - 10};
                        Vector2 endBottom = {(float)(arrayPosX + (k + 1) * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING), arrayPosY + ELEMENT_HEIGHT - 10};
                        DrawLineEx(startBottom, endBottom, 2, BLUE);
                        DrawTriangle(startBottom, (Vector2){startBottom.x + 5, startBottom.y + 5}, (Vector2){startBottom.x + 5, startBottom.y - 5}, BLUE);
                    }

                    // Draw rectangles
                    if (k == j || k == j + 1) {
                        // Flash swapped elements with a different color
                        DrawRectangle(arrayPosX + k * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING, arrayPosY, ELEMENT_WIDTH, ELEMENT_HEIGHT, ORANGE);
                    } else {
                        DrawRectangle(arrayPosX + k * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING, arrayPosY, ELEMENT_WIDTH, ELEMENT_HEIGHT, DARKGRAY);
                    }
                    DrawText(TextFormat("%d", array[k]), arrayPosX + k * (ELEMENT_WIDTH + ELEMENT_SPACING) + ELEMENT_SPACING + 10, arrayPosY + 10, 20, WHITE);
                }

                EndDrawing();

                // Wait until the specified delay has passed
                while (GetTime() - startTime < delay) { /* Do nothing */ }

                // Reset the timer for the next delay
                startTime = GetTime();
            }
        }
    }
}