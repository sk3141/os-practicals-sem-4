#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Structure for file entry
typedef struct {
    int start_block; // Starting block of the file
    int block_count; // Number of blocks occupied by the file
} FileEntry;

// Structure for index table entry
typedef struct {
    int block; // Block number
    int file_id; // File ID
} IndexEntry;

FileEntry files[MAX_FILES]; // Array to store file entries
IndexEntry index_table[MAX_BLOCKS]; // Array to store index table entries

int next_free_block = 0; // Next free block on the disk
int next_free_file_id = 0; // Next free file ID

// Function to allocate blocks for a file
int allocate_blocks(int file_id, int block_count) {
    if (next_free_block + block_count > MAX_BLOCKS) {
        printf("Error: Not enough free space.\n");
        return -1;
    }

    files[file_id].start_block = next_free_block;
    files[file_id].block_count = block_count;

    for (int i = 0; i < block_count; i++) {
        index_table[next_free_block + i].block = next_free_block + i;
        index_table[next_free_block + i].file_id = file_id;
    }

    next_free_block += block_count;
    return 0;
}

// Function to display index table
void display_index_table() {
    printf("Index Table:\n");
    printf("Block\tFile ID\n");
    for (int i = 0; i < next_free_block; i++) {
        printf("%d\t%d\n", index_table[i].block, index_table[i].file_id);
    }
}

// Main function
int main() {
  int choice, file_id, block_count;

  while (1) {
        printf("\nIndexed File Allocation Menu:\n");
        printf("1. Allocate blocks for a file\n");
        printf("2. Display index table\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (next_free_file_id >= MAX_FILES) {
                    printf("Error: Maximum number of files reached.\n");
                    break;
                }
                printf("Enter number of blocks for the file: ");
                scanf("%d", &block_count);
                if (allocate_blocks(next_free_file_id, block_count) == 0) {
                    printf("Blocks allocated successfully. File ID: %d\n", next_free_file_id);
                    next_free_file_id++;
                }
                break;
            case 2:
                display_index_table();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}