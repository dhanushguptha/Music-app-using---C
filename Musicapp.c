#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SONGS 100
#define SONG_NAME_LENGTH 100
#define FILENAME "playlist.txt"

typedef struct {
    char name[SONG_NAME_LENGTH];
} Song;

// Function prototypes
void addSong();
void displayPlaylist();
void playSong();
void loadPlaylist(Song playlist[], int *count);
void savePlaylist(Song playlist[], int count);

int main() {
    Song playlist[MAX_SONGS];
    int songCount = 0;

    loadPlaylist(playlist, &songCount);

    int choice;
    do {
        printf("\n=== Music App ===\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Play Song\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                addSong(playlist, &songCount);
                savePlaylist(playlist, songCount);
                break;
            case 2:
                displayPlaylist(playlist, songCount);
                break;
            case 3:
                playSong(playlist, songCount);
                break;
            case 4:
                printf("Exiting... Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void addSong(Song playlist[], int *count) {
    if (*count >= MAX_SONGS) {
        printf("Playlist is full! Cannot add more songs.\n");
        return;
    }

    printf("Enter the name of the song: ");
    fgets(playlist[*count].name, SONG_NAME_LENGTH, stdin);
    playlist[*count].name[strcspn(playlist[*count].name, "\n")] = 0; // Remove newline

    (*count)++;
    printf("Song added successfully!\n");
}

void displayPlaylist(Song playlist[], int count) {
    if (count == 0) {
        printf("The playlist is empty.\n");
        return;
    }

    printf("\n=== Playlist ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, playlist[i].name);
    }
}

void playSong(Song playlist[], int count) {
    if (count == 0) {
        printf("The playlist is empty. Add some songs first!\n");
        return;
    }

    int songNumber;
    printf("Enter the song number to play (1 to %d): ", count);
    scanf("%d", &songNumber);
    getchar(); // Consume newline

    if (songNumber < 1 || songNumber > count) {
        printf("Invalid song number!\n");
        return;
    }

    printf("Playing: %s\n", playlist[songNumber - 1].name);
}

void loadPlaylist(Song playlist[], int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("No existing playlist found. Starting fresh.\n");
        return;
    }

    *count = 0;
    while (fgets(playlist[*count].name, SONG_NAME_LENGTH, file)) {
        playlist[*count].name[strcspn(playlist[*count].name, "\n")] = 0; // Remove newline
        (*count)++;
    }

    fclose(file);
}

void savePlaylist(Song playlist[], int count) {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        printf("Error saving playlist!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", playlist[i].name);
    }

    fclose(file);
    printf("Playlist saved successfully!\n");
}
