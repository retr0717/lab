#include <stdio.h>
#include <limits.h>

#define MAX_PARTITIONS 100

struct MemoryPartition{
    int size;
    int allocated;
};

void firstFit(struct MemoryPartition memory[], int num_partitions, int process_size) {
    // Iterate through memory partitions
    for (int i = 0; i < num_partitions; i++) {
        // Check if partition is free and has enough space
        if (memory[i].allocated == 0 && memory[i].size >= process_size) {
            // Allocate the process to this partition
            memory[i].allocated = 1;
            printf("Process allocated to partition %d using First Fit\n", i);
            return; // Exit loop after allocation
        }
    }
    // If no suitable partition is found, create a new one
    printf("No suitable partition found\n");
    return;
    // Create new partition
    // memory[num_partitions].size = process_size;
    // memory[num_partitions].allocated = 1;
    // printf("Process allocated to new partition %d using First Fit\n", num_partitions);
}

void bestFit(struct MemoryPartition memory[], int num_partitions, int process_size) {
    int best_partition = -1;
    int min_size = INT_MAX;

    // Find the smallest suitable partition
    for (int i = 0; i < num_partitions; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= process_size && memory[i].size < min_size) {
            best_partition = i;
            min_size = memory[i].size;
        }
    }

    if (best_partition != -1) {
        // Allocate the process to the best partition
        memory[best_partition].allocated = 1;
        printf("Process allocated to partition %d using Best Fit\n", best_partition);
    } else {
        // If no suitable partition is found, create a new one
        printf("No suitable partition found, creating a new one using Best Fit\n");
        // Create new partition
        memory[num_partitions].size = process_size;
        memory[num_partitions].allocated = 1;
        printf("Process allocated to new partition %d using Best Fit\n", num_partitions);
    }
}

void worstFit(struct MemoryPartition memory[], int num_partitions, int process_size) {
    int worst_partition = -1;
    int max_size = 0;

    // Find the largest suitable partition
    for (int i = 0; i < num_partitions; i++) {
        if (memory[i].allocated == 0 && memory[i].size >= process_size && memory[i].size > max_size) {
            worst_partition = i;
            max_size = memory[i].size;
        }
    }

    if (worst_partition != -1) {
        // Allocate the process to the worst partition
        memory[worst_partition].allocated = 1;
        printf("Process allocated to partition %d using Worst Fit\n", worst_partition);
    } else {
        // If no suitable partition is found, create a new one
        printf("No suitable partition found, creating a new one using Worst Fit\n");
        // Create new partition
        memory[num_partitions].size = process_size;
        memory[num_partitions].allocated = 1;
        printf("Process allocated to new partition %d using Worst Fit\n", num_partitions);
    }
}

void displayMemoryStatus(struct MemoryPartition memory[], int num_partitions) {
    printf("Memory Partition\tSize\tStatus\n");
    printf("------------------------------------\n");
    for (int i = 0; i < num_partitions; i++) {
        printf("Partition %d\t\t%d\t%s\n", i, memory[i].size, memory[i].allocated ? "Allocated" : "Free");
    }
    printf("------------------------------------\n");
}

int main()
{
    struct MemoryPartition memory[MAX_PARTITIONS];
    int num_partitions;
    printf("Enter the no paritions : ");
    scanf("%d", &num_partitions);
    printf("Enter the size of each partition:\n");
    for(int i = 0 ; i < num_partitions ; i++)
    {
        printf("Partition %d: ", i);
        scanf("%d", &memory[i].size);
        memory[i].allocated = 0;
    }

    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    for (int i = 0; i < num_processes; i++) {
        int process_size, choice;
        printf("Enter the memory requirement of process %d: ", i);
        scanf("%d", &process_size);

        // Select memory allocation strategy
        printf("Choose memory allocation strategy:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Perform memory allocation based on user choice
        switch (choice) {
            case 1:
                firstFit(memory, num_partitions, process_size);
                break;
            case 2:
                bestFit(memory, num_partitions, process_size);
                break;
            case 3:
                worstFit(memory, num_partitions, process_size);
                break;
            default:
                printf("Invalid choice, process not allocated\n");
        }

        // Display memory status after each allocation
        displayMemoryStatus(memory, num_partitions);
    }

    return 0;
}
